#import <EXAdsFacebook/EXAdIconViewManager.h>

@implementation EXAdIconViewManager

UM_EXPORT_MODULE(AdIconViewManager)

- (NSString *)viewName
{
  return @"AdIconView";
}

- (UIView *)view
{
  return [[FBMediaView alloc] init];
}

@end
