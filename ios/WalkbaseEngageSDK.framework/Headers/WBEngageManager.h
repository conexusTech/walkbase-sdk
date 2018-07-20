//
//  WBEngageManager.h
//  WalkbaseEngageSDK
//
//  Created by Markus Rautopuro on 20.11.2014.
//  Copyright (c) 2018 Walkbase. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WBEngageManagerDelegate.h"

/** This document explains the how to integrate **Walkbase Engage SDK** into your application. Also, the documentation of `WalkbaseEngage` class, which contains the main functionality for Walkbase Engage SDK.
 
 ## Walkbase Engage SDK
 
 See the repository `README.md` for details.
 
 */

@interface WBEngageManager : NSObject

/**---------------------------------------------------------------------------------------
 * @name Properties
 *  ---------------------------------------------------------------------------------------
 */

/** Returns the current API key in use.
 */
@property (nonatomic, readonly, copy) NSString *apiKey;

/** The base URL for API to use. Default is `https://angel.walkbase.com´.
 */
@property (nonatomic, strong) NSURL *apiBaseURL;

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

@end
