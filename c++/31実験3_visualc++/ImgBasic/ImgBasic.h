
// ImgBasic.h : ImgBasic アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CImgBasicApp:
// このクラスの実装については、ImgBasic.cpp を参照してください。
//

#define MAX_THETA   360  /* θ軸のサイズ（0.5[deg]=１画素）*/
#define MAX_RHO     720  /* ρ軸のサイズ                 */


class CImgBasicApp : public CWinAppEx
{
public:
	CImgBasicApp();

	static	CString m_InputDir;
	static	CString m_OutputDir;
	static	CPoint	m_Pos[5];


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

extern CImgBasicApp theApp;
