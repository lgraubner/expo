'use strict';

import 'instapromise';

import crayon from '@ccheever/crayon';
import child_process from 'child_process';
import fs from 'fs';
import JsonFile from '@exponent/json-file';
import shell from 'shelljs';
import { getManifestAsync, saveUrlToPathAsync } from './shell-app-utils';

// TODO: Fix all the injection attacks here before moving this into an automated process
export async function createAndroidShellApp(args) {
  let {
    url,
    sdkVersion,
    androidPackage,
    privateConfigFile,
    keystore,
    alias,
    keystorePassword,
    keyPassword,
  } = args;

  let manifest = await getManifestAsync(url, {
    'Exponent-SDK-Version': sdkVersion,
    'Exponent-Platform': 'android',
  });

  if (!privateConfigFile) {
    crayon.yellow.warn('Warning: No config file specified.');
  }

  let fullManifestUrl = `${url.replace('exp://', 'https://')}/index.exp`;

  let javaPackage;
  if (!manifest.android) {
    javaPackage = androidPackage;
  } else {
    javaPackage = manifest.android.package || androidPackage;
  }

  if (!javaPackage) {
    throw new Error('Must specify javaPackage option (either from manifest or on command line).');
  }

  let name = manifest.name;
  let iconUrl = manifest.iconUrl;
  let scheme = manifest.scheme;
  let bundleUrl = manifest.bundleUrl;
  let notificationIconUrl = manifest.notification ? manifest.notification.iconUrl : null;

  let shellPath = '../android-shell-app/';
  shell.exec(`rm -rf ${shellPath}`);
  shell.exec(`mkdir ${shellPath}`);
  shell.exec(`cp -r ../android/ReactCommon ${shellPath}/ReactCommon`);
  shell.exec(`cp -r ../android/ReactAndroid ${shellPath}/ReactAndroid`);
  shell.exec(`cp -r ../android/Android-Image-Cropper ${shellPath}/Android-Image-Cropper`);
  shell.exec(`cp ../android/android.iml ${shellPath}/`);
  shell.exec(`cp -r ../android/app ${shellPath}/app`);
  shell.exec(`cp ../android/build.gradle ${shellPath}/`);
  shell.exec(`cp -r ../android/gradle ${shellPath}/gradle`);
  shell.exec(`cp ../android/gradle.properties ${shellPath}/`);
  shell.exec(`cp ../android/gradlew ${shellPath}/`);
  shell.exec(`cp ../android/local.properties ${shellPath}/`);
  shell.exec(`cp ../android/settings.gradle ${shellPath}/`);

  // Clean build directories
  shell.exec(`rm -rf ${shellPath}app/build/`);

  // Package
  shell.sed('-i', `applicationId 'host.exp.exponent'`, `applicationId '${javaPackage}'`, `${shellPath}app/build.gradle`);
  shell.exec(`sed -i'' -e 's/android:name="host.exp.exponent"/android:name="${javaPackage}"/g' ${shellPath}app/src/main/AndroidManifest.xml`);

  // Remove Exponent build script
  shell.sed('-i', `preBuild.dependsOn generateDynamicMacros`, ``, `${shellPath}app/build.gradle`);

  // change javaMaxHeapSize
  shell.sed('-i', `javaMaxHeapSize "8g"`, `javaMaxHeapSize "6g"`, `${shellPath}app/build.gradle`);

  // Push notifications
  shell.sed('-i', '"package_name": "host.exp.exponent"', `"package_name": "${javaPackage}"`, `${shellPath}app/google-services.json`); // TODO: actually use the correct file
  shell.exec(`sed -i'' -e 's/host.exp.exponent.permission.C2D_MESSAGE/${javaPackage}.permission.C2D_MESSAGE/g' ${shellPath}app/src/main/AndroidManifest.xml`);

  // Set INITIAL_URL and SHELL_APP_SCHEME
  shell.sed('-i', 'INITIAL_URL = null', `INITIAL_URL = "${url}"`, `${shellPath}app/src/main/java/host/exp/exponent/Constants.java`);
  shell.sed('-i', 'SHELL_APP_SCHEME = null', `SHELL_APP_SCHEME = "${scheme}"`, `${shellPath}app/src/main/java/host/exp/exponent/Constants.java`);

  // App name
  shell.sed('-i', '"app_name">Exponent', `"app_name">${name}`, `${shellPath}app/src/main/res/values/strings.xml`);

  // Remove exp:// scheme
  shell.exec(`sed -i'' -e '/DELETE\ AFTER/,/DELETE\ BEFORE/d' ${shellPath}app/src/main/AndroidManifest.xml`);

  // Add shell app scheme
  if (scheme) {
    shell.sed('-i', '<!-- ADD SHELL SCHEME HERE -->', `<intent-filter>
        <data android:scheme="${scheme}"/>

        <action android:name="android.intent.action.VIEW"/>

        <category android:name="android.intent.category.DEFAULT"/>
        <category android:name="android.intent.category.BROWSABLE"/>
      </intent-filter>`, `${shellPath}app/src/main/AndroidManifest.xml`);
  }

  // Embed manifest and bundle
  await fs.promise.writeFile(`${shellPath}app/src/main/assets/shell-app-manifest.json`, JSON.stringify(manifest));
  await saveUrlToPathAsync(bundleUrl, `${shellPath}app/src/main/assets/shell-app.bundle`);

  shell.sed('-i', '// ADD EMBEDDED RESPONSES HERE', `
    embeddedResponses.add(new EmbeddedResponse("${fullManifestUrl}", "assets://shell-app-manifest.json", "application/json"));
    embeddedResponses.add(new EmbeddedResponse("${bundleUrl}", "assets://shell-app.bundle", "application/javascript"));`,
    `${shellPath}app/src/main/java/host/exp/exponent/Constants.java`);

  // Icon
  if (iconUrl) {
    shell.exec(`find ${shellPath}app/src/main/res -iname ic_launcher.png -delete`);
    await saveUrlToPathAsync(iconUrl, `${shellPath}app/src/main/res/mipmap-hdpi/ic_launcher.png`);
  }

  if (notificationIconUrl) {
    shell.exec(`find ${shellPath}app/src/main/res -iname shell_notification_icon.png -delete`);
    await saveUrlToPathAsync(notificationIconUrl, `${shellPath}app/src/main/res/drawable-hdpi/shell_notification_icon.png`);
  }

  if (privateConfigFile) {
    let configJsonFile = new JsonFile(privateConfigFile);
    let fabric = await configJsonFile.getAsync('fabric', null);

    // Fabric
    if (fabric) {
      await fs.promise.unlink(`${shellPath}app/fabric.properties`);
      await fs.promise.writeFile(`${shellPath}app/fabric.properties`, `apiSecret=${fabric.buildSecret}\n`);

      shell.exec(`sed -i'' -e '/BEGIN\ FABRIC\ CONFIG/,/END\ FABRIC\ CONFIG/d' ${shellPath}app/src/main/AndroidManifest.xml`);
      shell.sed('-i', '<!-- ADD FABRIC CONFIG HERE -->', `<meta-data
      android:name="io.fabric.ApiKey"
      android:value="${fabric.apiKey}"/>`, `${shellPath}app/src/main/AndroidManifest.xml`);
    }
  }

  if (keystore && alias && keystorePassword && keyPassword) {
    shell.exec(`rm shell-unaligned.apk`);
    shell.exec(`rm shell.apk`);
    shell.config.fatal = true;
    shell.exec(`cd ${shellPath} && gradle assembleProdRelease`);
    shell.config.fatal = false;
    shell.exec(`cp ${shellPath}app/build/outputs/apk/app-prod-release-unsigned.apk shell-unaligned.apk`);
    // We use a newline here and shelljs doesn't like \n https://github.com/shelljs/shelljs/issues/175
    child_process.execSync(`printf '${keystorePassword}\n${keyPassword}' | jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore ${keystore} shell-unaligned.apk "${alias}"`);
    shell.exec(`zipalign -v 4 shell-unaligned.apk shell.apk`);
    shell.exec(`rm shell-unaligned.apk`);
    shell.exec(`jarsigner -verify -verbose -certs -keystore ${keystore} shell.apk`);
    shell.exec(`cp shell.apk /tmp/shell-signed.apk`);
  } else {
    shell.exec(`rm shell-unaligned.apk`);
    shell.exec(`rm shell.apk`);
    shell.config.fatal = true;
    shell.exec(`cd ${shellPath} && gradle assembleProdRelease`);
    shell.config.fatal = false;
    shell.exec(`cp ${shellPath}app/build/outputs/apk/app-prod-release-unsigned.apk /tmp/shell-unaligned.apk`);
  }
}
