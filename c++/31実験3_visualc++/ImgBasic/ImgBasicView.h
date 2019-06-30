
// ImgBasicView.h : CImgBasicView クラスのインターフェイス
//

#pragma once

#include "resource.h"

#include "ImgBasicDoc.h"


class CImgBasicView : public CFormView
{
protected: // シリアル化からのみ作成します。
	CImgBasicView();
	DECLARE_DYNCREATE(CImgBasicView)

public:
	enum{ IDD = IDD_IMGBASIC_FORM };

// 属性
public:
	CImgBasicDoc* GetDocument() const;

	COLORREF 	m_backColor;
	CBrush   	m_backBrush;
	
// 操作
public:

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void OnInitialUpdate(); // 構築後に初めて呼び出されます。

// 実装
public:
	virtual ~CImgBasicView();
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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnDraw(CDC* /*pDC*/);

	CStatic m_Picture1;

};

#ifndef _DEBUG  // ImgBasicView.cpp のデバッグ バージョン
inline CImgBasicDoc* CImgBasicView::GetDocument() const
   { return reinterpret_cast<CImgBasicDoc*>(m_pDocument); }
#endif

