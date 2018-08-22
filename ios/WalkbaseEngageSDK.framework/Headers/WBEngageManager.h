//
//  WBEngageManager.h
//  WalkbaseEngageSDK
//
//  Created by Markus Rautopuro on 20.11.2014.
//  Copyright (c) 2014 Markus Rautopuro. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WBEngageManagerDelegate.h"

/** This document explains the how to integrate **Walkbase Engage SDK** into your application. Also, the documentation of `WalkbaseEngage` class, which contains the main functionality for Walkbase Engage SDK.
 
 ## Walkbase Engage SDK
 
 ### Requirements

 Using **Walkbase Engage iOS SDK** in your application requires at least **Xcode 6.1.1** and deployment target of minimum **iOS 7.1.2**.
 
 The following iOS frameworks must be linked to the project:
 
 * AdSupport
 * CoreBluetooth
 * CoreLocation
 
 In your project, set the following Background Modes:
 
 * Location updates
 * Uses Bluetooth LE accessories
 
 ## Integration

 iOS 8 requires `NSLocationAlwaysUsageDescription` (for example `"Scans nearby iBeacons to detect your location."`) to be added into the project's `Info.plist` file. If this key is not added, the Location Services authorization will (silently) fail.
 
 Copy `WalkbaseEngageSDK.framework` to your project.
 
 In your `AppDelegate.m` add:
 
    @import WalkbaseEngageSDK;
 
 And in `application:didFinishLaunchingWithOptions:` add:
 
    [WBEngageManager startWithAPIKey:YOUR_API_KEY];
 
 YOUR_API_KEY is `NSString` of your API key (such as `@"129481240912"`), obtained from Walkbase.
 
 ## Implementation
 
 Your application should implement error handling for the most common errors that can occur in using `CoreLocation` and `CoreBluetooth`. `WBEngageManager` will call `WBEngageManagerDelegate`'s `didFailWithError:` method with corresponding error codes.
 
 See `WBEngageManagerDelegate` for details.

 */

@interface WBEngageManager : NSObject

/**---------------------------------------------------------------------------------------
 * @name Properties
 *  ---------------------------------------------------------------------------------------
 */

/** Returns the current API key in use.
 */
@property (nonatomic, readonly, copy) NSString *apiKey;

/** Returns a version of this SDK.
 */
@property (nonatomic, readonly, copy) NSString *version;

/** Sets debugging flag, for debugging purposes.
 */
@property (nonatomic, assign) BOOL debugMode;

/** Data about the detected beacons is sent to this delegate. See the definition of `WBEngageManagerDelegate` for details.
 */
@property (nonatomic, weak) id <WBEngageManagerDelegate> delegate;

/** The current state of the Engage engine.
 */
@property (nonatomic, readonly, assign) WBEngageManagerState state;

/** A list of detected iBeacons by iBeacon identifier (an `NSString` with UUID, major and minor separated by "-").
 */
@property (nonatomic, readonly, strong) NSMutableDictionary *detectedBeacons;

/**---------------------------------------------------------------------------------------
 * @name Instance methods
 *  ---------------------------------------------------------------------------------------
 */

/** Returns a singleton instance of the `WBEngageManager` class.
 
 @return An instance of `WBEngageManager`
 */

+ (instancetype)sharedInstance;


/** Starts the beacon tracking with the specified `apiKey`.
 
 If beacon monitoring fails, the `WBEngageManagerDelegate` will be called.
 
 @param apiKey The API key
 @return An instance of `WBEngageManager`
 */
+ (WBEngageManager *)startWithAPIKey:(NSString *)apiKey;

/** Sets a custom identifier that uniquely identifies the user. The identifier can be
 any non-nil string. Default is `nil`.
 
 @param userIdentifier The custom user identifier
 */
+ (void)setUserIdentifier:(NSString *)userIdentifier;

/** Pauses the beacon tracking temporarily. */
+ (void)pause;

/** Resumes the beacon tracking.
 
 @return Returns NO if the WBEngageManager hasn't been previously successfully started.
 */
+ (BOOL)resume;

/** Marks the advertisement as opened to the backend. */
+ (void)markAdvertisementOpened:(WBEngageAdvertisement *)advertisement;

/** Marks the advertisement as claimed to the backend. */
+ (void)markAdvertisementClaimed:(WBEngageAdvertisement *)advertisement;

/** Sets debugging flag, for debugging purposes. */
+ (void)setDebugMode:(BOOL)debugMode;

/** Returns an unique identifier for this device, in UUID format. */
+ (NSString *)deviceID;

@end
