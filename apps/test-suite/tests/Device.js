'use strict';

import * as Device from 'expo-device';
import { Platform } from 'react-native';

export const name = 'Device';
export async function test(t) {
  t.describe(`Device.getDeviceType()`, () => {
    t.it(`returns enum values`, async () => {
      let deviceType = await Device.getDeviceTypeAsync();
      t.expect(Object.values(Device.DeviceType).includes(deviceType)).toBeTruthy();
    });
  });

  t.describe(`Device.getUptimeAsync()`, () => {
    t.it(`calls getUptimeAsync() and returns number`, async () => {
      let uptime = await Device.getUptimeAsync();
      t.expect(uptime).toBeDefined();
      t.expect(typeof uptime).toEqual('number');
    });
  });

  if (Platform.OS === 'ios') {
    t.describe(`Device on iOS`, () => {
      t.it(`gets most constants and correct types`, async () => {
        let brand = Device.brand;
        let manufacturer = Device.manufacturer;
        let modelName = Device.modelName;
        let osName = Device.osName;
        let totalMemory = Device.totalMemory;
        let isDevice = Device.isDevice;
        let osBuildId = Device.osBuildId;
        let osInternalBuildId = Device.osInternalBuildId;
        let osVersion = Device.osVersion;
        let deviceName = Device.deviceName;
        let deviceYearClass = Device.deviceYearClass;
        t.expect(brand).toBeDefined();
        t.expect(typeof brand).toEqual('string');
        t.expect(manufacturer).toBeDefined();
        t.expect(typeof manufacturer).toEqual('string');
        t.expect(modelName).toBeDefined();
        t.expect(typeof modelName).toEqual('string');
        t.expect(osName).toBeDefined();
        t.expect(typeof osName).toEqual('string');
        t.expect(totalMemory).toBeDefined();
        t.expect(typeof totalMemory).toEqual('number');
        t.expect(isDevice).toBeDefined();
        t.expect(typeof isDevice).toEqual('boolean');
        t.expect(osBuildId).toBeDefined();
        t.expect(typeof osBuildId).toEqual('string');
        t.expect(osInternalBuildId).toBeDefined();
        t.expect(typeof osInternalBuildId).toEqual('string');
        t.expect(osVersion).toBeDefined();
        t.expect(typeof osVersion).toEqual('string');
        t.expect(deviceYearClass).toBeDefined();
        t.expect(typeof deviceYearClass).toEqual('number');
        t.expect(deviceName).toBeDefined();
        t.expect(typeof deviceName).toEqual('string');
      });

      t.it(`doesn't get Android-only constants`, async () => {
        let osBuildFingerprint = Device.osBuildFingerprint;
        let designName = Device.designName;
        let productName = Device.productName;
        let platformApiLevel = Device.platformApiLevel;
        t.expect(designName).toBeNull();
        t.expect(productName).toBeNull();
        t.expect(platformApiLevel).toBeNull();
        t.expect(osBuildFingerprint).toBeNull();
      });

      t.it(`doesn't call getPlatformFeaturesAsync()`, async () => {
        let error;
        let allFeatures;
        try {
          allFeatures = await Device.getPlatformFeaturesAsync();
        } catch (e) {
          error = e;
        }
        t.expect(error).toBeDefined();
        t.expect(typeof allFeatures).toEqual('undefined');
      });

      t.it(`doesn't call hasPlatformFeatureAsync()`, async () => {
        let error;
        let hasFeature;
        try {
          hasFeature = await Device.hasPlatformFeatureAsync('amazon_fire_tv');
        } catch (e) {
          error = e;
        }
        t.expect(error).toBeDefined();
        t.expect(typeof hasFeature).toEqual('undefined');
      });

      t.it(`doesn't call getMaxMemoryAsync()`, async () => {
        let error;
        let maxMemory;
        try {
          maxMemory = await Device.getMaxMemoryAsync();
        } catch (e) {
          error = e;
        }
        t.expect(error).toBeDefined();
        t.expect(typeof maxMemory).toEqual('undefined');
      });

      t.it(`doesn't call sideLoadingAsync()`, async () => {
        let error;
        let isSideLoading;
        try {
          isSideLoading = await Device.isSideLoadingEnabledAsync();
        } catch (e) {
          error = e;
        }
        t.expect(error).toBeDefined();
        t.expect(typeof isSideLoading).toEqual('undefined');
      });

      t.it(`gets osBuildId same as osInternalBuildId`, async () => {
        let osBuildId = await Device.osBuildId;
        let osInternalBuildId = await Device.osInternalBuildId;
        t.expect(Device.osBuildId).toBeTruthy();
        t.expect(Device.osInternalBuildId).toBeTruthy();
        t.expect(osBuildId).toEqual(osInternalBuildId);
      });
    });
  } else if (Platform.OS === 'android') {
    t.describe(`Device on Android`, () => {
      t.it(`gets constants and correct types`, async () => {
        let designName = await Device.designName;
        let productName = await Device.productName;
        let brand = await Device.brand;
        let manufacturer = await Device.manufacturer;
        let modelName = await Device.modelName;
        let osName = await Device.osName;
        let totalMemory = await Device.totalMemory;
        let isDevice = await Device.isDevice;
        let osBuildId = await Device.osBuildId;
        let osBuildFingerprint = await Device.osBuildFingerprint;
        let osInternalBuildId = await Device.osInternalBuildId;
        let platformApiLevel = await Device.platformApiLevel;
        let osVersion = await Device.osVersion;
        let deviceName = await Device.deviceName;
        let deviceYearClass = await Device.deviceYearClass;
        t.expect(designName).toBeDefined();
        t.expect(typeof designName).toEqual('string');
        t.expect(productName).toBeDefined();
        t.expect(typeof productName).toEqual('string');
        t.expect(brand).toBeDefined();
        t.expect(typeof brand).toEqual('string');
        t.expect(manufacturer).toBeDefined();
        t.expect(typeof manufacturer).toEqual('string');
        t.expect(modelName).toBeDefined();
        t.expect(typeof modelName).toEqual('string');
        t.expect(osName).toBeDefined();
        t.expect(typeof osName).toEqual('string');
        t.expect(totalMemory).toBeDefined();
        t.expect(typeof totalMemory).toEqual('number');
        t.expect(isDevice).toBeDefined();
        t.expect(typeof isDevice).toEqual('boolean');
        t.expect(osBuildId).toBeDefined();
        t.expect(typeof osBuildId).toEqual('string');
        t.expect(osBuildFingerprint).toBeDefined();
        t.expect(typeof osBuildFingerprint).toEqual('string');
        t.expect(osInternalBuildId).toBeDefined();
        t.expect(typeof osInternalBuildId).toEqual('string');
        t.expect(platformApiLevel).toBeDefined();
        t.expect(typeof platformApiLevel).toEqual('number');
        t.expect(osVersion).toBeDefined();
        t.expect(typeof osVersion).toEqual('string');
        t.expect(deviceYearClass).toBeDefined();
        t.expect(typeof deviceYearClass).toEqual('number');
        if (isDevice) {
          t.expect(deviceName).toBeDefined();
          t.expect(typeof deviceName).toEqual('string');
        } else {
          t.expect(deviceName).toBeNull();
        }
      });

      t.it(`doesn't get modelId`, async () => {
        await Device.modelId;
        t.expect(Device.modelId).toBeNull();
      });

      t.it(`calls hasPlatformFeatureAsync() with valid string and returns boolean`, async () => {
        let error;
        let hasFeature;
        try {
          hasFeature = await Device.hasPlatformFeatureAsync('amazon_fire_tv');
        } catch (e) {
          error = e;
        }
        t.expect(hasFeature).toEqual(t.jasmine.any(Boolean));
      });

      t.it(
        `calls hasPlatformFeatureAsync() with invalid string format and returns false`,
        async () => {
          let error;
          let hasFeature;
          try {
            hasFeature = await Device.hasPlatformFeatureAsync('camera');
          } catch (e) {
            error = e;
          }
          t.expect(hasFeature).toEqual(t.jasmine.any(Boolean));
          t.expect(hasFeature).toEqual(false);
        }
      );

      t.it(`calls getMaxMemoryAsync() and returns a number under integer limit`, async () => {
        let maxMemory = await Device.getMaxMemoryAsync();
        t.expect(maxMemory).toBeLessThanOrEqual(Number.MAX_SAFE_INTEGER);
      });

      t.it(`calls getPlatformFeaturesAsync()`, async () => {
        let allFeatures = await Device.getPlatformFeaturesAsync();
        t.expect(allFeatures).toBeDefined();
      });
    });
  }
}
