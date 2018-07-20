#import "BleManager.h"
#import "React/RCTBridge.h"
#import "React/RCTConvert.h"
#import "React/RCTEventDispatcher.h"
#import <WalkbaseEngageSDK/WalkbaseEngageSDK.h>

@implementation BleManager

RCT_EXPORT_MODULE();

bool hasListeners;

- (instancetype)init
{
    
    if (self = [super init]) {
        [WBEngageManager sharedInstance].delegate = self;
        hasListeners = YES;
    }
    
    return self;
}

- (NSArray<NSString *> *)supportedEvents
{
    return @[@"WBEngageManagerStateNotDetermined", @"WBEngageManagerStateInitializing", @"WBEngageManagerStatePaused", @"WBEngageManagerStateScanning", @"WBEngageManagerStateFailed", @"WBEngageManagerReceivedAdvertisement", @"WBEngageManagerOff"];
}

- (void) engageEngine:(id)engageEngine didDetermineState:(WBEngageManagerState)state
{
    switch (state) {
        case WBEngageManagerStateNotDetermined:
            NSLog(@"State: not initialized");
            if (hasListeners) {
                [self sendEventWithName:@"WBEngageManagerStateNotDetermined" body:@{@"state" : @"not initialized"}];
            }
            break;
        case WBEngageManagerStateInitializing:
            NSLog(@"State: initializing");
            if (hasListeners) {
                [self sendEventWithName:@"WBEngageManagerStateInitializing" body:@{@"state" : @"initializing"}];
            }
            break;
        case WBEngageManagerStatePaused:
            NSLog(@"State: paused");
            if (hasListeners) {
                [self sendEventWithName:@"WBEngageManagerStatePaused" body:@{@"state" : @"paused"}];
            }
            break;
        case WBEngageManagerStateScanning:
            NSLog(@"State: active");
            if (hasListeners) {
                [self sendEventWithName:@"WBEngageManagerStateScanning" body:@{@"state" : @"active"}];
            }
            break;
        case WBEngageManagerStateFailed:
            NSLog(@"State: received an error");
            if (hasListeners) {
                [self sendEventWithName:@"WBEngageManagerStateFailed" body:@{@"state" : @"received an error"}];
            }
            break;
    }
}

- (void)engageEngine:(id)engageEngine didFailWithError:(NSError *)error
{
    NSLog(@"didFailWithError: %@", error);
    if ([error.domain isEqualToString:WBErrorDomain]) {
        // self.error = error.code;
        switch (error.code) {
            case WBErrorBackgroundRefreshDenied:
                if (hasListeners) {
                    [self sendEventWithName:@"WBEngageManagerOff" body:@{@"state" : @"WBErrorBackgroundRefreshDenied"}];
                }
                break;
            case WBErrorBackgroundRefreshRestricted:
                if (hasListeners) {
                    [self sendEventWithName:@"WBEngageManagerOff" body:@{@"state" : @"WBErrorBackgroundRefreshRestricted"}];
                }
                break;
            case WBErrorBluetoothUnauthorized:
                if (hasListeners) {
                    [self sendEventWithName:@"WBEngageManagerOff" body:@{@"state" : @"WBErrorBluetoothUnauthorized"}];
                }
                break;
            case WBErrorBluetoothOff:
                if (hasListeners) {
                    [self sendEventWithName:@"WBEngageManagerOff" body:@{@"state" : @"WBErrorBluetoothOff"}];
                }
                break;
            case WBErrorBluetoothUnsupported:
                if (hasListeners) {
                    [self sendEventWithName:@"WBEngageManagerOff" body:@{@"state" : @"WBErrorBluetoothUnsupported"}];
                }
                break;
            case WBErrorInvalidAPIKey:
                if (hasListeners) {
                    [self sendEventWithName:@"WBEngageManagerOff" body:@{@"state" : @"WBErrorInvalidAPIKey"}];
                }
                break;
            case WBErrorLocationServicesDisabled:
                if (hasListeners) {
                    [self sendEventWithName:@"WBEngageManagerOff" body:@{@"state" : @"WBErrorLocationServicesDisabled"}];
                }
                break;
            case WBErrorLocationServicesUnauthorized:
                if (hasListeners) {
                    [self sendEventWithName:@"WBEngageManagerOff" body:@{@"state" : @"WBErrorLocationServicesUnauthorized"}];
                }
                break;
            case WBErrorUnknown:
                if (hasListeners) {
                    [self sendEventWithName:@"WBEngageManagerOff" body:@{@"state" : @"WBErrorUnknown"}];
                }
                break;
        }
    } else {
        // self.error = -1;
        if (hasListeners) {
            [self sendEventWithName:@"WBEngageManagerOff" body:@{@"state" : @"Not error code"}];
        }
    }
}

- (void)engageEngine:(id)engageEngine shouldPresentAdvertisement:(WBEngageAdvertisement *)advertisement
{
    NSLog(@"Received an advertisement: %@", advertisement);
    if (hasListeners) {
        [self sendEventWithName:@"WBEngageManagerReceivedAdvertisement" body:@{@"data" : advertisement}];
    }
    [advertisement markOpened];
    [advertisement performSelector:@selector(markClaimed) withObject:nil afterDelay:3.0];
    
}
@end
