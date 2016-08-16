/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <tgmath.h>

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "ABI7_0_0RCTAssert.h"
#import "ABI7_0_0RCTDefines.h"

NS_ASSUME_NONNULL_BEGIN

// JSON serialization/deserialization
ABI7_0_0RCT_EXTERN NSString *__nullable ABI7_0_0RCTJSONStringify(id __nullable jsonObject, NSError **error);
ABI7_0_0RCT_EXTERN id __nullable ABI7_0_0RCTJSONParse(NSString *__nullable jsonString, NSError **error);
ABI7_0_0RCT_EXTERN id __nullable ABI7_0_0RCTJSONParseMutable(NSString *__nullable jsonString, NSError **error);

// Sanitize a JSON object by stripping invalid types and/or NaN values
ABI7_0_0RCT_EXTERN id ABI7_0_0RCTJSONClean(id object);

// Get MD5 hash of a string
ABI7_0_0RCT_EXTERN NSString *ABI7_0_0RCTMD5Hash(NSString *string);

// Execute the specified block on the main thread. Unlike dispatch_sync/async
// this will not context-switch if we're already running on the main thread.
ABI7_0_0RCT_EXTERN void ABI7_0_0RCTExecuteOnMainThread(dispatch_block_t block, BOOL sync);

// Get screen metrics in a thread-safe way
ABI7_0_0RCT_EXTERN CGFloat ABI7_0_0RCTScreenScale(void);
ABI7_0_0RCT_EXTERN CGSize ABI7_0_0RCTScreenSize(void);

// Round float coordinates to nearest whole screen pixel (not point)
ABI7_0_0RCT_EXTERN CGFloat ABI7_0_0RCTRoundPixelValue(CGFloat value);
ABI7_0_0RCT_EXTERN CGFloat ABI7_0_0RCTCeilPixelValue(CGFloat value);
ABI7_0_0RCT_EXTERN CGFloat ABI7_0_0RCTFloorPixelValue(CGFloat value);

// Convert a size in points to pixels, rounded up to the nearest integral size
ABI7_0_0RCT_EXTERN CGSize ABI7_0_0RCTSizeInPixels(CGSize pointSize, CGFloat scale);

// Method swizzling
ABI7_0_0RCT_EXTERN void ABI7_0_0RCTSwapClassMethods(Class cls, SEL original, SEL replacement);
ABI7_0_0RCT_EXTERN void ABI7_0_0RCTSwapInstanceMethods(Class cls, SEL original, SEL replacement);

// Module subclass support
ABI7_0_0RCT_EXTERN BOOL ABI7_0_0RCTClassOverridesClassMethod(Class cls, SEL selector);
ABI7_0_0RCT_EXTERN BOOL ABI7_0_0RCTClassOverridesInstanceMethod(Class cls, SEL selector);

// Creates a standardized error object to return in callbacks
ABI7_0_0RCT_EXTERN NSDictionary<NSString *, id> *ABI7_0_0RCTMakeError(NSString *message, id __nullable toStringify, NSDictionary<NSString *, id> *__nullable extraData);
ABI7_0_0RCT_EXTERN NSDictionary<NSString *, id> *ABI7_0_0RCTMakeAndLogError(NSString *message, id __nullable toStringify, NSDictionary<NSString *, id> *__nullable extraData);
ABI7_0_0RCT_EXTERN NSDictionary<NSString *, id> *ABI7_0_0RCTJSErrorFromNSError(NSError *error);
ABI7_0_0RCT_EXTERN NSDictionary<NSString *, id> *ABI7_0_0RCTJSErrorFromCodeMessageAndNSError(NSString *code, NSString *message, NSError *__nullable error);

// The default error code to use as the `code` property for callback error objects
ABI7_0_0RCT_EXTERN NSString *const ABI7_0_0RCTErrorUnspecified;

// Returns YES if ReactABI7_0_0 is running in a test environment
ABI7_0_0RCT_EXTERN BOOL ABI7_0_0RCTRunningInTestEnvironment(void);

// Returns YES if ReactABI7_0_0 is running in an iOS App Extension
ABI7_0_0RCT_EXTERN BOOL ABI7_0_0RCTRunningInAppExtension(void);

// Returns the shared UIApplication instance, or nil if running in an App Extension
ABI7_0_0RCT_EXTERN UIApplication *__nullable ABI7_0_0RCTSharedApplication(void);

// Returns the current main window, useful if you need to access the root view
// or view controller, e.g. to present a modal view controller or alert.
ABI7_0_0RCT_EXTERN UIWindow *__nullable ABI7_0_0RCTKeyWindow(void);

// Does this device support force touch (aka 3D Touch)?
ABI7_0_0RCT_EXTERN BOOL ABI7_0_0RCTForceTouchAvailable(void);

// Return a UIAlertView initialized with the given values
// or nil if running in an app extension
ABI7_0_0RCT_EXTERN UIAlertView *__nullable ABI7_0_0RCTAlertView(NSString *title,
                                                NSString *__nullable message,
                                                id __nullable delegate,
                                                NSString *__nullable cancelButtonTitle,
                                                NSArray<NSString *> *__nullable otherButtonTitles);

// Create an NSError in the ABI7_0_0RCTErrorDomain
ABI7_0_0RCT_EXTERN NSError *ABI7_0_0RCTErrorWithMessage(NSString *message);

// Convert nil values to NSNull, and vice-versa
ABI7_0_0RCT_EXTERN id __nullable ABI7_0_0RCTNilIfNull(id __nullable value);
ABI7_0_0RCT_EXTERN id ABI7_0_0RCTNullIfNil(id __nullable value);

// Convert NaN or infinite values to zero, as these aren't JSON-safe
ABI7_0_0RCT_EXTERN double ABI7_0_0RCTZeroIfNaN(double value);

// Convert data to a Base64-encoded data URL
ABI7_0_0RCT_EXTERN NSURL *ABI7_0_0RCTDataURL(NSString *mimeType, NSData *data);

// Gzip functionality - compression level in range 0 - 1 (-1 for default)
ABI7_0_0RCT_EXTERN NSData *__nullable ABI7_0_0RCTGzipData(NSData *__nullable data, float level);

// Returns the relative path within the main bundle for an absolute URL
// (or nil, if the URL does not specify a path within the main bundle)
ABI7_0_0RCT_EXTERN NSString *__nullable ABI7_0_0RCTBundlePathForURL(NSURL *__nullable URL);

// Determines if a given image URL actually refers to an XCAsset
ABI7_0_0RCT_EXTERN BOOL ABI7_0_0RCTIsXCAssetURL(NSURL *__nullable imageURL);

// Creates a new, unique temporary file path with the specified extension
ABI7_0_0RCT_EXTERN NSString *__nullable ABI7_0_0RCTTempFilePath(NSString *__nullable extension, NSError **error);

// Converts a CGColor to a hex string
ABI7_0_0RCT_EXTERN NSString *ABI7_0_0RCTColorToHexString(CGColorRef color);

// Get standard localized string (if it exists)
ABI7_0_0RCT_EXTERN NSString *ABI7_0_0RCTUIKitLocalizedString(NSString *string);

// URL manipulation
ABI7_0_0RCT_EXTERN NSString *__nullable ABI7_0_0RCTGetURLQueryParam(NSURL *__nullable URL, NSString *param);
ABI7_0_0RCT_EXTERN NSURL *__nullable ABI7_0_0RCTURLByReplacingQueryParam(NSURL *__nullable URL, NSString *param, NSString *__nullable value);

NS_ASSUME_NONNULL_END
