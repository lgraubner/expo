/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <UIKit/UIKit.h>

#import "ABI8_0_0RCTBridge.h"

typedef NS_ENUM(NSInteger, ABI8_0_0RCTTextEventType)
{
  ABI8_0_0RCTTextEventTypeFocus,
  ABI8_0_0RCTTextEventTypeBlur,
  ABI8_0_0RCTTextEventTypeChange,
  ABI8_0_0RCTTextEventTypeSubmit,
  ABI8_0_0RCTTextEventTypeEnd,
  ABI8_0_0RCTTextEventTypeKeyPress
};

/**
 * The threshold at which text inputs will start warning that the JS thread
 * has fallen behind (resulting in poor input performance, missed keys, etc.)
 */
ABI8_0_0RCT_EXTERN const NSInteger ABI8_0_0RCTTextUpdateLagWarningThreshold;

/**
 * Takes an input event name and normalizes it to the form that is required
 * by the events system (currently that means starting with the "top" prefix,
 * but that's an implementation detail that may change in future).
 */
ABI8_0_0RCT_EXTERN NSString *ABI8_0_0RCTNormalizeInputEventName(NSString *eventName);

@protocol ABI8_0_0RCTEvent <NSObject>
@required

@property (nonatomic, strong, readonly) NSNumber *viewTag;
@property (nonatomic, copy, readonly) NSString *eventName;
@property (nonatomic, assign, readonly) uint16_t coalescingKey;

- (BOOL)canCoalesce;
- (id<ABI8_0_0RCTEvent>)coalesceWithEvent:(id<ABI8_0_0RCTEvent>)newEvent;

// used directly for doing a JS call
+ (NSString *)moduleDotMethod;
// must contain only JSON compatible values
- (NSArray *)arguments;

@end


/**
 * This class wraps the -[ABI8_0_0RCTBridge enqueueJSCall:args:] method, and
 * provides some convenience methods for generating event calls.
 */
@interface ABI8_0_0RCTEventDispatcher : NSObject <ABI8_0_0RCTBridgeModule>

/**
 * Deprecated, do not use.
 */
- (void)sendAppEventWithName:(NSString *)name body:(id)body
__deprecated_msg("Subclass ABI8_0_0RCTEventEmitter instead");

/**
 * Deprecated, do not use.
 */
- (void)sendDeviceEventWithName:(NSString *)name body:(id)body
__deprecated_msg("Subclass ABI8_0_0RCTEventEmitter instead");

/**
 * Deprecated, do not use.
 */
- (void)sendInputEventWithName:(NSString *)name body:(NSDictionary *)body
__deprecated_msg("Use ABI8_0_0RCTDirectEventBlock or ABI8_0_0RCTBubblingEventBlock instead");

/**
 * Send a text input/focus event. For internal use only.
 */
- (void)sendTextEventWithType:(ABI8_0_0RCTTextEventType)type
                     ReactABI8_0_0Tag:(NSNumber *)ReactABI8_0_0Tag
                         text:(NSString *)text
                          key:(NSString *)key
                   eventCount:(NSInteger)eventCount;

/**
 * Send a pre-prepared event object.
 *
 * Events are sent to JS as soon as the thread is free to process them.
 * If an event can be coalesced and there is another compatible event waiting, the coalescing will happen immediately.
 */
- (void)sendEvent:(id<ABI8_0_0RCTEvent>)event;

@end

@interface ABI8_0_0RCTBridge (ABI8_0_0RCTEventDispatcher)

- (ABI8_0_0RCTEventDispatcher *)eventDispatcher;

@end
