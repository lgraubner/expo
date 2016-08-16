/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <UIKit/UIKit.h>

#import "ABI5_0_0RCTBridge.h"
#import "ABI5_0_0RCTBridgeModule.h"
#import "ABI5_0_0RCTInvalidating.h"
#import "ABI5_0_0RCTViewManager.h"

/**
 * Posted right before re-render happens. This is a chance for views to invalidate their state so
 * next render cycle will pick up updated views and layout appropriately.
 */
ABI5_0_0RCT_EXTERN NSString *const ABI5_0_0RCTUIManagerWillUpdateViewsDueToContentSizeMultiplierChangeNotification;

/**
 * Posted whenever a new root view is registered with ABI5_0_0RCTUIManager. The userInfo property
 * will contain a ABI5_0_0RCTUIManagerRootViewKey with the registered root view.
 */
ABI5_0_0RCT_EXTERN NSString *const ABI5_0_0RCTUIManagerDidRegisterRootViewNotification;

/**
 * Posted whenever a root view is removed from the ABI5_0_0RCTUIManager. The userInfo property
 * will contain a ABI5_0_0RCTUIManagerRootViewKey with the removed root view.
 */
ABI5_0_0RCT_EXTERN NSString *const ABI5_0_0RCTUIManagerDidRemoveRootViewNotification;

/**
 * Key for the root view property in the above notifications
 */
ABI5_0_0RCT_EXTERN NSString *const ABI5_0_0RCTUIManagerRootViewKey;

@protocol ABI5_0_0RCTScrollableProtocol;

/**
 * The ABI5_0_0RCTUIManager is the module responsible for updating the view hierarchy.
 */
@interface ABI5_0_0RCTUIManager : NSObject <ABI5_0_0RCTBridgeModule, ABI5_0_0RCTInvalidating>

/**
 * Register a root view with the ABI5_0_0RCTUIManager.
 */
- (void)registerRootView:(UIView *)rootView;

/**
 * Gets the view associated with a ReactABI5_0_0Tag.
 */
- (UIView *)viewForReactABI5_0_0Tag:(NSNumber *)ReactABI5_0_0Tag;

/**
 * Update the frame of a view. This might be in response to a screen rotation
 * or some other layout event outside of the ReactABI5_0_0-managed view hierarchy.
 */
- (void)setFrame:(CGRect)frame forView:(UIView *)view;

/**
 * Set the natural size of a view, which is used when no explicit size is set.
 * Use UIViewNoIntrinsicMetric to ignore a dimension.
 */
- (void)setIntrinsicContentSize:(CGSize)size forView:(UIView *)view;

/**
 * Update the background color of a view. The source of truth for
 * backgroundColor is the shadow view, so if to update backgroundColor from
 * native code you will need to call this method.
 */
- (void)setBackgroundColor:(UIColor *)color forView:(UIView *)view;

/**
 * Schedule a block to be executed on the UI thread. Useful if you need to execute
 * view logic after all currently queued view updates have completed.
 */
- (void)addUIBlock:(ABI5_0_0RCTViewManagerUIBlock)block;

/**
 * The view that is currently first responder, according to the JS context.
 */
+ (UIView *)JSResponder;

/**
 * Normally, UI changes are not applied until the complete batch of method
 * invocations from JavaScript to native has completed.
 *
 * Setting this to YES will flush UI changes sooner, which could potentially
 * result in inconsistent UI updates.
 *
 * The default is NO (recommended).
 */
@property (atomic, assign) BOOL unsafeFlushUIChangesBeforeBatchEnds;

/**
 * In some cases we might want to trigger layout from native side.
 * ReactABI5_0_0 won't be aware of this, so we need to make sure it happens.
 */
- (void)setNeedsLayout;

@end

/**
 * This category makes the current ABI5_0_0RCTUIManager instance available via the
 * ABI5_0_0RCTBridge, which is useful for ABI5_0_0RCTBridgeModules or ABI5_0_0RCTViewManagers that
 * need to access the ABI5_0_0RCTUIManager.
 */
@interface ABI5_0_0RCTBridge (ABI5_0_0RCTUIManager)

@property (nonatomic, readonly) ABI5_0_0RCTUIManager *uiManager;

@end
