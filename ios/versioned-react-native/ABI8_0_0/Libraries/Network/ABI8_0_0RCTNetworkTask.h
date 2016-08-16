/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Foundation/Foundation.h>

#import "ABI8_0_0RCTURLRequestDelegate.h"
#import "ABI8_0_0RCTURLRequestHandler.h"

typedef void (^ABI8_0_0RCTURLRequestCompletionBlock)(NSURLResponse *response, NSData *data, NSError *error);
typedef void (^ABI8_0_0RCTURLRequestCancellationBlock)(void);
typedef void (^ABI8_0_0RCTURLRequestIncrementalDataBlock)(NSData *data, int64_t progress, int64_t total);
typedef void (^ABI8_0_0RCTURLRequestProgressBlock)(int64_t progress, int64_t total);
typedef void (^ABI8_0_0RCTURLRequestResponseBlock)(NSURLResponse *response);

typedef NS_ENUM(NSInteger, ABI8_0_0RCTNetworkTaskStatus) {
  ABI8_0_0RCTNetworkTaskPending = 0,
  ABI8_0_0RCTNetworkTaskInProgress,
  ABI8_0_0RCTNetworkTaskFinished,
};

@interface ABI8_0_0RCTNetworkTask : NSObject <ABI8_0_0RCTURLRequestDelegate>

@property (nonatomic, readonly) NSURLRequest *request;
@property (nonatomic, readonly) NSNumber *requestID;
@property (nonatomic, readonly, weak) id requestToken;
@property (nonatomic, readonly) NSURLResponse *response;
@property (nonatomic, readonly) ABI8_0_0RCTURLRequestCompletionBlock completionBlock;

@property (nonatomic, copy) ABI8_0_0RCTURLRequestProgressBlock downloadProgressBlock;
@property (nonatomic, copy) ABI8_0_0RCTURLRequestIncrementalDataBlock incrementalDataBlock;
@property (nonatomic, copy) ABI8_0_0RCTURLRequestResponseBlock responseBlock;
@property (nonatomic, copy) ABI8_0_0RCTURLRequestProgressBlock uploadProgressBlock;

@property (nonatomic, readonly) ABI8_0_0RCTNetworkTaskStatus status;

- (instancetype)initWithRequest:(NSURLRequest *)request
                        handler:(id<ABI8_0_0RCTURLRequestHandler>)handler
                completionBlock:(ABI8_0_0RCTURLRequestCompletionBlock)completionBlock NS_DESIGNATED_INITIALIZER;

- (void)start;
- (void)cancel;

@end
