
// ImgFFTView.h : CImgFFTView クラスのインターフェイス
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"


class CImgFFTView : public CFormView
{
protected: // シリアル化からのみ作成します。
	CImgFFTView();
	DECLARE_DYNCREATE(CImgFFTView)

public:
	enum{ IDD = IDD_IMGFFT_FORM };

// 属性
public:
	CImgFFTDoc* GetDocument() const;

	BOOL	m_InitFlag;

// 操作
public:
	void DrawPicture( CImgBmp *p_bmp, HDC hDC ) ;

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void OnInitialUpdate(); // 構築後に初めて呼び出されます。

// 実装
public:
	virtual ~CImgFFTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Picture1;
	CStatic m_Picture2;
	float m_gainEdit;
	CSliderCtrl m_SliderCtrl;
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedImgGainReset();
};

#ifndef _DEBUG  // ImgFFTView.cpp のデバッグ バージョン
inline CImgFFTDoc* CImgFFTView::GetDocument() const
   { return reinterpret_cast<CImgFFTDoc*>(m_pDocument); }
#endif

