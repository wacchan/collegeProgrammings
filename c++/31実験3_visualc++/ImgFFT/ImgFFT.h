
// ImgFFT.h : ImgFFT アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CImgFFTApp:
// このクラスの実装については、ImgFFT.cpp を参照してください。
//

class CImgFFTApp : public CWinAppEx
{
public:
	CImgFFTApp();

	static	CString m_InputDir;
	static	CString m_OutputDir;

// オーバーライド
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 実装
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImgFFTApp theApp;
