
// testApl.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CtestAplApp:
// このクラスの実装については、testApl.cpp を参照してください。
//

class CtestAplApp : public CWinApp
{
public:
	CtestAplApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	DECLARE_MESSAGE_MAP()
};

extern CtestAplApp theApp;