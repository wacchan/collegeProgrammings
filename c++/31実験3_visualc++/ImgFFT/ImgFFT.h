
// ImgFFT.h : ImgFFT �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��


// CImgFFTApp:
// ���̃N���X�̎����ɂ��ẮAImgFFT.cpp ���Q�Ƃ��Ă��������B
//

class CImgFFTApp : public CWinAppEx
{
public:
	CImgFFTApp();

	static	CString m_InputDir;
	static	CString m_OutputDir;

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImgFFTApp theApp;
