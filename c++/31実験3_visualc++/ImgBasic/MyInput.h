#pragma once

#include "ImgBasic.h"

// CMyInput �_�C�A���O

class CMyInput : public CDialog
{
	DECLARE_DYNAMIC(CMyInput)

public:
	CMyInput(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CMyInput();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_MyInput1_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	CString m_Message;
	double m_num;
};
