// MyMakeFigureDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ImgFFT.h"
#include "MyMakeFigureDialog.h"


// CMyMakeFigureDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CMyMakeFigureDialog, CDialog)

CMyMakeFigureDialog::CMyMakeFigureDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyMakeFigureDialog::IDD, pParent)
	, m_freq1(0)
	, m_freq2(0)
	, m_rotate(0)
	, m_kind(0)
{
	m_freq1 = 0.0;
	m_freq2 = 0.0;
	m_rotate = 0.0;
	m_kind = -1;
}

CMyMakeFigureDialog::~CMyMakeFigureDialog()
{
}

void CMyMakeFigureDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ImgMakeFigEdit_freq1, m_freq1);
	DDX_Text(pDX, IDC_ImgMakeFigEdit_freq2, m_freq2);
	DDX_Text(pDX, IDC_ImgMakeFigEdit_rotate, m_rotate);
	DDX_Radio(pDX, IDC_ImgMakeFigRADIO1, m_kind);
}


BEGIN_MESSAGE_MAP(CMyMakeFigureDialog, CDialog)
END_MESSAGE_MAP()


// CMyMakeFigureDialog ���b�Z�[�W �n���h��
