README
-----------------------------------------------------------
 nend
 http://nend.net
-----------------------------------------------------------

開発環境
 nendSDK をアプリケーションに組み込むためには
 Xcode 4.5 (iOS SDK 6) 以上が必要です。
 Xcode 4.4 (iOS SDK 5.1) 以下の環境ではご利用できません。

また、Build Phases > Link Binary With Libraries へ

* Security.framework (version 1.2.2~)
* AdSupport.framework (version 2.0.0~) ※iOS6未満も対象に含める場合には必ずOptionalに設定してください。

の追加が必要です。

端末環境
 デバイスは、iPhone 3GS (armv7 対応)以上、iPhone 5, iPod Touch 5th (armv7s 対応)
 OS バージョンは、iOS 4.3 以上 iOS6.1.3 (2013/4/11 時点現在最新) が動作保証対象となります。
 それ以外の端末では正常に動作しない場合があります。

具体的な実装方法、詳細情報、よくある質問等は、nendSDK設定マニュアルをお読みください。



著作権表記

/* -----------------------------------------------------------
  nendSDK ver2.0.0より SBJson3.0.4を利用しています。
  nendSDK ver2.0.1より SBJson3.0.4を改変して利用しています。
 ----------------------------------------------------------- */
 
License

Copyright (C) 2007-2013 Stig Brautaset. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the author nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/* -----------------------------------------------------------------
  nendSDK_iOS ver1.2.2より UIIDの生成にUIApplication+UIIDを利用しています。
 ------------------------------------------------------------------- */

 UIApplication+UIID

 Copyright (c) 2011 Masashi Ono.
 
 This code is licensed under the MIT license: http://www.opensource.org/licenses/mit-license.php
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.