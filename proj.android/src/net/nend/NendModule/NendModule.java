package net.nend.NendModule;

//import org.cocos2dx.cpp.Cocos2dxActivity;	// for cocos2d-x v3.0 rc0
import org.cocos2dx.lib.Cocos2dxActivity;	// for cocos2d-x v3.0 rc1

import android.app.Activity;
import android.content.Context;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import net.nend.android.NendAdListener;
import net.nend.android.NendAdView;

public class NendModule {

	private static NendAdView nendAdView;
	private static WindowManager mWm;

	// 広告の初期化
	public static void createAdView(final String apiKey, final String spotID, final float x, final float y) {
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (nendAdView == null) {

					int intSpotID = Integer.parseInt(spotID);

					nendAdView = new NendAdView(activity.getApplicationContext(), intSpotID, apiKey);
					nendAdView.setListener(sAdListener);
			
					if (null == mWm) {
						mWm = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
					}

					WindowManager.LayoutParams mLayoutParams = new WindowManager.LayoutParams();
					mLayoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
					mLayoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
					mLayoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
					mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
					mLayoutParams.gravity = Gravity.TOP | Gravity.LEFT;
					mLayoutParams.x = (int)x;
					mLayoutParams.y = (int)y;
					mWm.addView(nendAdView, mLayoutParams);

					nendAdView.loadAd();
				}
			}
		});
	}

	// 広告の初期化
	public static void createAdViewBottom(final String apiKey, final String spotID) {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (nendAdView == null) {
				int intSpotID = Integer.parseInt(spotID);

				nendAdView = new NendAdView(activity.getApplicationContext(), intSpotID, apiKey);
				nendAdView = new NendAdView(activity, intSpotID, apiKey);
				nendAdView.setListener(sAdListener);

				if (null == mWm) {
					mWm = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
				}
				WindowManager.LayoutParams mLayoutParams = new WindowManager.LayoutParams();
				mLayoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
				mLayoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
				mLayoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
				mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
				mLayoutParams.gravity = Gravity.BOTTOM;
				mWm.addView(nendAdView, mLayoutParams);
				
				nendAdView.loadAd();
				}
			}
		});

	}

	// 広告の初期化
	public static void createAdViewTop(final String apiKey, final String spotID) {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView == null) {
					int intSpotID = Integer.parseInt(spotID);

					nendAdView = new NendAdView(activity.getApplicationContext(), intSpotID, apiKey);
					nendAdView.setListener(sAdListener);

					if (null == mWm) {
						mWm = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
					}
					WindowManager.LayoutParams mLayoutParams = new WindowManager.LayoutParams();
					mLayoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
					mLayoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
					mLayoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
					mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
					mLayoutParams.gravity = Gravity.TOP;
					mWm.addView(nendAdView, mLayoutParams);

					nendAdView.loadAd();
				}
			}
		});
	}

	// 広告の非表示
	public static void hideAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.setVisibility(View.INVISIBLE);
				}
			}
		});
	}

	// 広告の再表示
	public static void showAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.setVisibility(View.VISIBLE);
				}
			}
		});
	}
	
	// 広告の一時停止
	public static void pauseAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.pause();
				}
			}
		});
	}

	// 広告の再開
	public static void resumeAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.resume();
				}
			}
		});
	}
	
	private static NendAdListener sAdListener = new NendAdListener() {
		
		@Override
		public void onReceiveAd(NendAdView arg0) {
			NendModule.onReceiveAd();
		}
		
		@Override
		public void onFailedToReceiveAd(NendAdView arg0) {
			NendModule.onFailedToReceiveAd();
		}
		
		@Override
		public void onDismissScreen(NendAdView arg0) {
			NendModule.onDismissScreen();
		}
		
		@Override
		public void onClick(NendAdView arg0) {
			NendModule.onClick();
		}
	};
	
	public static native void onReceiveAd();
	public static native void onFailedToReceiveAd();
	public static native void onDismissScreen();
	public static native void onClick();
}
