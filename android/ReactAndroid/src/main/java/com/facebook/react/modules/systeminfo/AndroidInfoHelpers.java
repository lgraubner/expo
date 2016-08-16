package com.facebook.react.modules.systeminfo;

import android.os.Build;

public class AndroidInfoHelpers {

    public static String EMULATOR_LOCALHOST = "10.0.2.2:8081";

    public static String GENYMOTION_LOCALHOST = "10.0.3.2:8081";

    public static String DEVICE_LOCALHOST = "localhost:8081";

    private static boolean isRunningOnGenymotion() {
        return Build.FINGERPRINT.contains("vbox");
    }

    private static boolean isRunningOnStockEmulator() {
        return Build.FINGERPRINT.contains("generic");
    }

    public static String getServerHost() {
        if (isRunningOnGenymotion()) {
            return GENYMOTION_LOCALHOST;
        }
        if (isRunningOnStockEmulator()) {
            return EMULATOR_LOCALHOST;
        }
        return DEVICE_LOCALHOST;
    }
}
