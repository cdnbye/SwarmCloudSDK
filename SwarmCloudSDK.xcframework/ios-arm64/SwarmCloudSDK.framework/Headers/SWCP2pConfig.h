//
//  SWCP2pConfig.h
//  SwarmCloudSDK
//
//  Created by Timmy on 2021/5/5.
//  Copyright © 2021 SwarmCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WebRTC/RTCConfiguration.h"

typedef NS_ENUM(NSInteger, SWCLogLevel) {
    SWCLogLevelNone,
    SWCLogLevelDebug,
    SWCLogLevelInfo,
    SWCLogLevelWarn,
    SWCLogLevelError,
};

typedef NS_ENUM(NSInteger, SWCAnnounceLocation) {
    SWCAnnounceLocationChina,
    SWCAnnounceLocationHongkong,
    SWCAnnounceLocationUSA,
    SWCAnnounceLocationEurope,
};

NS_ASSUME_NONNULL_BEGIN

@interface SWCP2pConfig : NSObject

/** WebRTC configuration. WebRTC配置 */
@property(nonatomic, strong, nullable) RTCConfiguration *webRTCConfig;

/** The address of signal server. 主信令服务器地址 */
@property(nonatomic, copy, nullable) NSString *wsSignalerAddr;

/** The address of signal server. 备用信令服务器地址 */
@property(nonatomic, copy, nullable) NSString *wsSignalerAddrBackup;

/** The address of tracker server. tracker服务器地址 */
@property(nonatomic, copy, nullable) NSString *announce;

/** The country enum for tracker server address. tracker服务器地址所在国家的枚举 */
@property(nonatomic, assign) SWCAnnounceLocation announceLocation;

/** Enable or disable p2p engine. 是否开启P2P，默认true */
@property(nonatomic, assign) BOOL p2pEnabled;

/** Only allow uploading on Wi-Fi. 是否只在wifi模式上传数据 */
@property(nonatomic, assign) BOOL wifiOnly;

/** The port for local http server. Hls本地代理服务器的端口号 */
@property(nonatomic, assign) NSInteger localPortHls;

/** Max download timeout for WebRTC datachannel. datachannel下载二进制数据的最大超时时间 */
@property(nonatomic, assign) NSTimeInterval dcDownloadTimeout;

/** The max size of binary data that can be stored in the disk for VOD. 磁盘缓存大小 */
@property(nonatomic, assign) NSUInteger diskCacheLimit;

/** The max size of binary data that can be stored in the memory cache. 内存缓存大小 */
@property(nonatomic, assign) NSUInteger memoryCacheLimit;

/** TS file download timeout. 下载ts文件超时时间 */
@property(nonatomic, assign) NSTimeInterval downloadTimeout;

/** User defined tag which is presented in console. 用户自定义标签 */
@property(nonatomic, copy) NSString *tag;

/** Print log level. 打印日志级别 */
@property(nonatomic, assign) SWCLogLevel logLevel;

/** Max peer connections at the same time. 最大连接节点数量 */
@property(nonatomic, assign) NSUInteger maxPeerConnections;

/** Use HTTP ranges requests where it is possible. Allows to continue (and not start over) aborted P2P downloads over HTTP. 在可能的情况下使用Http Range请求来补足p2p下载超时的剩余部分数据 */
@property(nonatomic, assign) BOOL useHttpRange;

/** Set http headers while requesting ts and m3u8. 设置请求ts和m3u8时的http headers */
@property(nonatomic, copy) NSDictionary *httpHeadersForHls;

/** Trickle ICE is an optimization of the ICE specification for NAT traversal. NAT穿越时采用rickle ICE策略 */
@property(nonatomic, assign) BOOL trickleICE;

/** Allow the P2P transmission of m3u8 file.. 是否允许m3u8文件的P2P传输 */
@property(nonatomic, assign) BOOL sharePlaylist;

/** Time for HTTP download if p2p download timeout. P2P下载超时后留给HTTP下载的时间 */
@property(nonatomic, assign) NSTimeInterval httpLoadTime;

@property(nonatomic, assign) NSUInteger maxMediaFilesInPlaylist;

@property(nonatomic, assign) BOOL proxySuspendInBackground;

/** All media suffixes that allow P2P transmission. 允许进行P2P传输的所有媒体文件后缀 */
@property(nonatomic, copy) NSArray<NSString *> *hlsMediaFiles;

/** All media extensions that allow P2P transmission. 允许进行P2P传输的所有媒体文件名后缀 */
@property(nonatomic, copy) NSArray<NSString *> *hlsMediaFileExtensions;

/** Save logs to the file. 是否将日志持久化到外部存储 */
@property(nonatomic, assign) BOOL logPersistent;

/** The path to the log files, default is Library/Caches/Logs/ . 日志文件的存储路径，默认路径是 Library/Caches/Logs/ */
@property(nonatomic, copy) NSString *logFilePath;

/** Make a preflight request to online Geo IP database provider to get ASN, only work for live mode. 直播模式下向在线IP数据库请求ASN等信息，从而获得更准确的调度 */
@property(nonatomic, assign) BOOL geoIpPreflight;

@property(nonatomic, copy) NSString *alternativeTrackerIp;

/**
 Create a new instance with default configuration.
 实例化方法，用默认配置初始化。
 */
+ (instancetype)defaultConfiguration;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
