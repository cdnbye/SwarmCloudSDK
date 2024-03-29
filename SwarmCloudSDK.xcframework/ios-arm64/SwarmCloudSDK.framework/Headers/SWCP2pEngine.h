//
//  SWCP2pEngine.h
//  SwarmCloudSDK
//
//  Created by Timmy on 2021/5/5.
//  Copyright © 2021 SwarmCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SWCP2pConfig.h"
#import "SWCByteRange.h"

typedef NS_ENUM(NSInteger, SWCMimeType) {
    SWCMimeTypeUnknown = 0,
    SWCMimeTypeM3U8,
};

NS_ASSUME_NONNULL_BEGIN

typedef NSString * _Nonnull (^SegmentId) (NSString * _Nonnull streamId, NSNumber *sn, NSString * _Nonnull segmentUrl, SWCRange byteRange);

extern NSString *const kP2pEngineDidReceiveStatistics ;

@protocol SWCP2pEngineDelegate <NSObject>
    
@optional

- (NSTimeInterval)bufferedDuration;

- (NSTimeInterval)currentPosition;

@end

@interface SWCP2pEngine : NSObject

/** The config of SDK. SDK的P2P配置 */
@property(nonatomic, strong) SWCP2pConfig *p2pConfig;

/** The version of SDK. SDK的版本号 */
@property(nonatomic, copy, readonly, class) NSString *engineVersion;

/** The version of p2p protocol, ，only have the same protocol version as another platform can both interconnect with each other. p2p私有协议的版本号，与其他平台互通的前提是 P2P 协议版本号相同。 */
@property(nonatomic, copy, readonly, class) NSString *dcVersion;

/** Get the connection state of p2p engine. 获取P2P Engine的连接状态 */
@property(nonatomic, assign, readonly) BOOL isConnected;


/** Get the peer ID of p2p engine. 获取P2P Engine的peer ID */
@property(nonatomic, copy, readonly) NSString *peerId;

/** Pass a block to generate segment Id. 产生标识ts文件的字符串的block。*/
@property (nonatomic, strong) SegmentId segmentIdForHls;

/** The delegate of Player Stats. */
@property (nonatomic, weak) id<SWCP2pEngineDelegate> delegate;

- (instancetype)init NS_UNAVAILABLE;

/**
 Start p2p engine with token and the specified config.
 
 @param token  The token which can be obtained from CDNBye console.
 @param config  The specified p2p config or nil.
 */
- (void)startWithToken:(NSString *)token andP2pConfig:(nullable SWCP2pConfig *)config NS_SWIFT_NAME(start(token:p2pConfig:));

/**
 Start p2p engine with token and the specified config.
 
 @param token  The token which can be obtained from CDNBye console.
 @param config  The specified p2p config or nil.
 @param error  Pointer to receive service error.
 */
- (void)startWithToken:(NSString *)token p2pConfig:(nullable SWCP2pConfig *)config error:(NSError **)error NS_SWIFT_NAME(start(token:p2pConfig:error:));

/**
 Get the shared instance of P2pEngine.
 Please call [P2pEngine initWithToken: andP2pConfig:] before calling it.
 */
+ (instancetype)sharedInstance;

/**
 Get parsed local stream url by passing the original stream url(m3u8) to P2pEngine instance.
 
 @param url  The original stream url(m3u8).
 @result A parsed local http url.
 */
- (NSURL *)parseStreamURL:(NSURL *)url NS_SWIFT_NAME(parse(streamURL:));

/**
Get parsed local stream url by passing the original stream url(m3u8) to P2pEngine instance.

@param url  The original stream url(m3u8).
 @param videoId  video Id for the given url.
@result A parsed local http url.
*/
- (NSURL *)parseStreamURL:(NSURL *)url withVideoId:(NSString *)videoId NS_SWIFT_NAME(parse(streamURL:videoId:));

/**
Get parsed local stream url by passing the original stream url(m3u8) to P2pEngine instance.

@param url  The original stream url(m3u8).
@param videoId  video Id for the given url.
@param mimeType If your URI doesn’t end with .m3u8, you can pass SWCMimeTypeM3U8 to the third parameter of parseStreamUrl to explicitly indicate the type of the content.
@result A parsed local http url.
*/
- (NSURL *)parseStreamURL:(NSURL *)url withVideoId:(NSString *)videoId mimeType:(SWCMimeType)mimeType NS_SWIFT_NAME(parse(streamURL:videoId:mimeType:));

/**
 Stop p2p and free used resources.
 */
- (void)stopP2p;

/**
 Restart p2p engine.
 */
- (void)restartP2p;

/**
 Disabled P2P at runtime
 */
- (void)disableP2p;

/**
 Enable P2P at runtime
 */
- (void)enableP2p;

/**
Stop P2P and shut down the proxy server.
*/
- (void)shutdown;

- (void)restartLocalProxy:(NSError **)error;

- (NSNumber *)currentLevel;

@end

NS_ASSUME_NONNULL_END
