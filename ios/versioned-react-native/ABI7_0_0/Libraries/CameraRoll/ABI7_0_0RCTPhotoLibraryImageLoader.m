/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import "ABI7_0_0RCTPhotoLibraryImageLoader.h"

#import <Photos/Photos.h>

#import "ABI7_0_0RCTImageUtils.h"
#import "ABI7_0_0RCTUtils.h"

@implementation ABI7_0_0RCTPhotoLibraryImageLoader

ABI7_0_0RCT_EXPORT_MODULE()

@synthesize bridge = _bridge;

#pragma mark - ABI7_0_0RCTImageLoader

- (BOOL)canLoadImageURL:(NSURL *)requestURL
{
  return [requestURL.scheme caseInsensitiveCompare:@"ph"] == NSOrderedSame;
}

- (ABI7_0_0RCTImageLoaderCancellationBlock)loadImageForURL:(NSURL *)imageURL
                                              size:(CGSize)size
                                             scale:(CGFloat)scale
                                        resizeMode:(ABI7_0_0RCTResizeMode)resizeMode
                                   progressHandler:(ABI7_0_0RCTImageLoaderProgressBlock)progressHandler
                                 completionHandler:(ABI7_0_0RCTImageLoaderCompletionBlock)completionHandler
{
  // Using PhotoKit for iOS 8+
  // The 'ph://' prefix is used by FBMediaKit to differentiate between
  // assets-library. It is prepended to the local ID so that it is in the
  // form of an, NSURL which is what assets-library uses.
  NSString *phAssetID = [imageURL.absoluteString substringFromIndex:@"ph://".length];
  PHFetchResult *results = [PHAsset fetchAssetsWithLocalIdentifiers:@[phAssetID] options:nil];
  if (results.count == 0) {
    NSString *errorText = [NSString stringWithFormat:@"Failed to fetch PHAsset with local identifier %@ with no error message.", phAssetID];
    completionHandler(ABI7_0_0RCTErrorWithMessage(errorText), nil);
    return ^{};
  }

  PHAsset *asset = [results firstObject];
  PHImageRequestOptions *imageOptions = [PHImageRequestOptions new];

  if (progressHandler) {
    imageOptions.progressHandler = ^(double progress, NSError *error, BOOL *stop, NSDictionary<NSString *, id> *info) {
      static const double multiplier = 1e6;
      progressHandler(progress * multiplier, multiplier);
    };
  }

  // Note: PhotoKit defaults to a deliveryMode of PHImageRequestOptionsDeliveryModeOpportunistic
  // which means it may call back multiple times - we probably don't want that
  imageOptions.deliveryMode = PHImageRequestOptionsDeliveryModeHighQualityFormat;

  BOOL useMaximumSize = CGSizeEqualToSize(size, CGSizeZero);
  CGSize targetSize;
  if (useMaximumSize) {
    targetSize = PHImageManagerMaximumSize;
    imageOptions.resizeMode = PHImageRequestOptionsResizeModeNone;
  } else {
    targetSize = size;
    imageOptions.resizeMode = PHImageRequestOptionsResizeModeFast;
  }

  PHImageContentMode contentMode = PHImageContentModeAspectFill;
  if (resizeMode == ABI7_0_0RCTResizeModeContain) {
    contentMode = PHImageContentModeAspectFit;
  }

  PHImageRequestID requestID =
  [[PHImageManager defaultManager] requestImageForAsset:asset
                                             targetSize:targetSize
                                            contentMode:contentMode
                                                options:imageOptions
                                          resultHandler:^(UIImage *result, NSDictionary<NSString *, id> *info) {
    if (result) {
      completionHandler(nil, result);
    } else {
      completionHandler(info[PHImageErrorKey], nil);
    }
  }];

  return ^{
    [[PHImageManager defaultManager] cancelImageRequest:requestID];
  };
}

@end
