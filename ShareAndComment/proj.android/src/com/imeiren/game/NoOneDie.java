/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package com.imeiren.game;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.widget.Toast;

import com.umeng.socialize.controller.RequestType;
import com.umeng.socialize.controller.UMServiceFactory;
import com.umeng.socialize.controller.UMSocialService;
import com.umeng.socialize.sso.QZoneSsoHandler;
import com.umeng.socialize.sso.SinaSsoHandler;
import com.umeng.socialize.sso.TencentWBSsoHandler;

public class NoOneDie extends Cocos2dxActivity {
	private static final String TAG = NoOneDie.class.getSimpleName();
	private static Handler mHandler = null;
	private static Activity mActivity = null;
	private static UMSocialService mController = UMServiceFactory
			.getUMSocialService("com.umeng.share", RequestType.SOCIAL);

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mActivity = this;
	}

	@Override
	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		// NoOneDie should create stencil buffer
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

		return glSurfaceView;
	}

	static {
		System.loadLibrary("cocos2dcpp");
	}

	/**
	 * @Title: openShareBoard
	 * @Description: 调用友盟的openShare方法， 打开分享平台选择面板
	 * @throws
	 */
	public static void openShareBoard() {
		mHandler = new Handler(Looper.getMainLooper());
		mHandler.postDelayed(new Runnable() {

			@Override
			public void run() {
				if (mActivity != null) {
					/**
					 * 设置新浪微博、QQ空间、腾讯微博的Handler,进行SSO授权
					 *
					 * 注意 ： 新浪平台支持SSO则需要把友盟提供的com.sina.sso拷进src里面，
					 * 需要将友盟提供的libs、res文件拷贝到您的工程对应的目录里面.
					 */
					mController.getConfig().setSsoHandler(new SinaSsoHandler());
					mController.getConfig().setSsoHandler(
							new QZoneSsoHandler(mActivity, "801011739",
									"a71b4890a76b05cdbf818d8c6edb9ecd"));
					mController.getConfig().setSsoHandler(
							new TencentWBSsoHandler());

					// 打开友盟的分享平台选择面板
					mController.openShare(mActivity, false);
				}
			}
		}, 100);
	}

	public static void rate() {
		Log.d(TAG, "in the rate method");
		try {
			Uri uri = Uri.parse("market://details?id="
					+ mActivity.getPackageName());
			Intent intent = new Intent(Intent.ACTION_VIEW, uri);
			intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			mActivity.startActivity(intent);
		} catch (Exception e) {
			Toast.makeText(mActivity, "无法打开应用市场!", Toast.LENGTH_LONG).show();
		}
	}

	public static void shareScore(int score) {
		Intent sendIntent = new Intent(Intent.ACTION_SEND);
		sendIntent.setType("image/*");
		Uri uri = Uri.parse("file:////data/data/"
				+ mActivity.getApplicationInfo().packageName + "/files/share.jpg");
		sendIntent.putExtra(Intent.EXTRA_STREAM, uri);
		//用于一般的分享
		sendIntent.putExtra(Intent.EXTRA_TEXT, "我在世界杯中过了 " + score
				+ " 个人！已经无敌了！来。挑战一下我吧~~");
		//用于微信的分享
		sendIntent.putExtra("Kdescription", "我在世界杯中过了 " + score
				+ " 个人！已经无敌了！来。挑战一下我吧~~");
		mActivity.startActivity(Intent.createChooser(sendIntent, "来，分享一下"));
	}
}
