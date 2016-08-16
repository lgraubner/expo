// Copyright 2015-present 650 Industries. All rights reserved.

#import <UIKit/UIKit.h>

#import "ABI7_0_0RCTBridgeModule.h"

@interface ABI7_0_0EXLinkingManager : NSObject <ABI7_0_0RCTBridgeModule>

- (instancetype)initWithInitialUrl: (NSURL *)initialUrl;
- (void)dispatchOpenUrlEvent: (NSURL *)url;

@end
