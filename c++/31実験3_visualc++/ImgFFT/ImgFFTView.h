
// ImgFFTView.h : CImgFFTView �N���X�̃C���^�[�t�F�C�X
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"


class CImgFFTView : public CFormView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CImgFFTView();
	DECLARE_DYNCREATE(CImgFFTView)

public:
	enum{ IDD = IDD_IMGFFT_FORM };

// ����
public:
	CImgFFTDoc* GetDocument() const;

	BOOL	m_InitFlag;

// ����
public:
	void DrawPicture( CImgBmp *p_bmp, HDC hDC ) ;

// �I�[�o�[���C�h
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void OnInitialUpdate(); // �\�z��ɏ��߂ČĂяo����܂��B

// ����
public:
	virtual ~CImgFFTView();
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
	CStatic m_Picture1;
	CStatic m_Picture2;
	float m_gainEdit;
	CSliderCtrl m_SliderCtrl;
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedImgGainReset();
};

#ifndef _DEBUG  // ImgFFTView.cpp �̃f�o�b�O �o�[�W����
inline CImgFFTDoc* CImgFFTView::GetDocument() const
   { return reinterpret_cast<CImgFFTDoc*>(m_pDocument); }
#endif

