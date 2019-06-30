
// ImgBasicView.h : CImgBasicView �N���X�̃C���^�[�t�F�C�X
//

#pragma once

#include "resource.h"

#include "ImgBasicDoc.h"


class CImgBasicView : public CFormView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CImgBasicView();
	DECLARE_DYNCREATE(CImgBasicView)

public:
	enum{ IDD = IDD_IMGBASIC_FORM };

// ����
public:
	CImgBasicDoc* GetDocument() const;

	COLORREF 	m_backColor;
	CBrush   	m_backBrush;
	
// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void OnInitialUpdate(); // �\�z��ɏ��߂ČĂяo����܂��B

// ����
public:
	virtual ~CImgBasicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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

#ifndef _DEBUG  // ImgBasicView.cpp �̃f�o�b�O �o�[�W����
inline CImgBasicDoc* CImgBasicView::GetDocument() const
   { return reinterpret_cast<CImgBasicDoc*>(m_pDocument); }
#endif

