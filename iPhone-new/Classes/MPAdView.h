//
//  MPAdView.h
//  MoPub
//
//  Created by Nafis Jamal on 1/19/11.
//  Copyright 2011 Stanford. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import "MPAdBrowserController.h"
#import "MPBaseAdapter.h"
#import "MPStore.h"
#import "MPConstants.h"
#import "MPLogging.h"

@protocol MPAdViewDelegate;

@interface NSString (MPAdditions)
- (NSString *)URLescapedString;
@end

@interface UIDevice (MPAdditions)
- (NSString *)hashedMopubUDID;
@end

@interface MPAdView : UIView <UIWebViewDelegate, MPAdBrowserControllerDelegate, MPAdapterDelegate> 
{
	//
	id<MPAdViewDelegate> _delegate;
	
	// Ad unit identifier for this ad view.
	NSString *_adUnitId;
	
	// 
	NSString *_keywords;
	
	//
	CLLocation *_location;
	
	// Subview that represents the actual ad content. Set via -setAdContentView.
	UIView *_adContentView;
	
	// Default webview used for HTML ads.
	UIWebView *_webView;
	
	// Connection data object for ad request.
	NSMutableData *_data;
	
	// URL used to request ad parameters.
	NSURL *_URL;
	
	// Connection object for ad request.
	NSURLConnection *_conn;
	
	// 
	MPBaseAdapter *_adapter;
	
	//
	NSURL *_clickURL;
	
	//
	NSURL *_interceptURL;
	
	//
	NSURL *_failURL;
	
	//
	NSURL *_impTrackerURL;
	
	//
	NSMutableArray *_excludeParams;
	
	//
	MPStore *_store;
	
	//
	BOOL _shouldInterceptLinks;
	
	//
	BOOL _scrollable;
	
	//
	BOOL _isLoading;
}

@property (nonatomic, assign) id<MPAdViewDelegate> delegate;
@property (nonatomic, copy) NSString *adUnitId;
@property (nonatomic, copy) NSString *keywords;
@property (nonatomic, retain) CLLocation *location;
@property (nonatomic, copy) NSURL *URL;
@property (nonatomic, copy) NSURL *clickURL;
@property (nonatomic, copy) NSURL *interceptURL;
@property (nonatomic, copy) NSURL *failURL;
@property (nonatomic, copy) NSURL *impTrackerURL;
@property (nonatomic, assign) BOOL shouldInterceptLinks;
@property (nonatomic, assign) BOOL scrollable;

- (id)initWithAdUnitId:(NSString *)adUnitId frame:(CGRect)frame;
- (CGSize)adContentViewSize;
- (void)loadAd;
- (void)loadAdWithURL:(NSURL *)URL;
- (void)refreshAd;
- (void)setAdContentView:(UIView *)view;
- (void)adViewDidAppear;

// Informs the ad unit that the device orientation has changed.
- (void)rotateToOrientation:(UIInterfaceOrientation)newOrientation;

- (void)didCloseAd:(id)sender;

- (void)customEventDidLoadAd;
- (void)customEventDidFailToLoadAd;

@end

@protocol MPAdViewDelegate <NSObject>

@required
- (UIViewController *)viewControllerForPresentingModalView;

@optional
- (void)adViewDidFailToLoadAd:(MPAdView *)view;
- (void)adViewDidLoadAd:(MPAdView *)view;
- (void)nativeAdClicked:(MPAdView *)view;
- (void)willPresentModalViewForAd:(MPAdView *)view;
- (void)didDismissModalViewForAd:(MPAdView *)view;
- (void)adViewDidReceiveResponseParams:(NSDictionary *)params;
- (void)adViewShouldClose:(MPAdView *)view;

@end
