
// ImgBasic.h : ImgBasic �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��


// CImgBasicApp:
// ���̃N���X�̎����ɂ��ẮAImgBasic.cpp ���Q�Ƃ��Ă��������B
//

#define MAX_THETA   360  /* �Ǝ��̃T�C�Y�i0.5[deg]=�P��f�j*/
#define MAX_RHO     720  /* �ώ��̃T�C�Y                 */


class CImgBasicApp : public CWinAppEx
{
public:
	CImgBasicApp();

	static	CString m_InputDir;
	static	CString m_OutputDir;
	static	CPoint	m_Pos[5];


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

extern CImgBasicApp theApp;
