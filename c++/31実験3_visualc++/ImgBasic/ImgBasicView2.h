#pragma once

#include "ImgBasicDoc.h"
#include "afxwin.h"

// CImgBasicView2 �t�H�[�� �r���[

class CImgBasicView2 : public CFormView
{
	DECLARE_DYNCREATE(CImgBasicView2)

protected:
	CImgBasicView2();           // ���I�����Ŏg�p����� protected �R���X�g���N�^�[
	virtual ~CImgBasicView2();

public:
	enum { IDD = IDD_ImgBasicView2 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


	COLORREF 	m_backColor;
	CBrush   	m_backBrush;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	CStatic m_Picture2;
	CString m_WindowsText;

	HCURSOR m_hSelectCursor, m_hWaitCursor;
	CRect	m_MouseDragRect;
	BOOL	m_MouseLeftButtonDown;

	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


