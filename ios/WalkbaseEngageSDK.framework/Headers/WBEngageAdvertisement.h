//
//  WBEngageAdvertisement.h
//  WalkbaseEngageSDK
//
//  Created by Markus Rautopuro on 11.12.2014.
//  Copyright (c) 2018 Walkbase. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface WBEngageAdvertisement : NSObject

/** The unique identifier of the advertisement. */
@property (nonatomic, assign, readonly) NSUInteger identifier;

/** The title of the advertisement. */
@property (nonatomic, strong, readonly) NSString *title;

/** The contents of the advertisement in plain text. */
@property (nonatomic, strong, readonly) NSString *text;

/** The link which should be opened when the user taps the advertisement.
 
 Can be `nil`, if the advertisement doesn't contain a link.
 */
@property (nonatomic, strong, readonly) NSURL *linkURL;

/** The link to the advertisement image.

 Can be `nil`, if the advertisement doesn't contain an image.
 */
@property (nonatomic, strong, readonly) NSURL *imageURL;

/** The size of the advertisement image.
 
 `imageSize` is `CGSizeZero` if there's no image.
 */
@property (nonatomic, assign, readonly) CGSize imageSize;


- (instancetype) __unavailable init;

/** Initializes the advertisement based on an NSDictionary. */
- (instancetype)initFromDictionary:(NSDictionary *)dictionary;

/** Creates the advertisement object based on the contents of the NSDictionary. */
+ (instancetype)advertisementFromDictionary:(NSDictionary *)dictionary;

/** Returns a textual representation of the advertisement. */
- (NSString *)description;

/** Informs the backend that the advertisement has been opened. */
- (void)markOpened;

/** Informs the backend that the advertisement has been claimed. */
- (void)markClaimed;

@end
