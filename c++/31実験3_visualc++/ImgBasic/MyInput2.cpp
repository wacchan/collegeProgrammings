// MyInput2.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ImgBasic.h"
#include "MyInput2.h"


// CMyInput2 ダイアログ

IMPLEMENT_DYNAMIC(CMyInput2, CDialog)

CMyInput2::CMyInput2(CWnd* pParent /*=NULL*/)
	: CDialog(CMyInput2::IDD, pParent)
	, m_Title(_T(""))
	, m_Message1(_T(""))
	, m_Message2(_T(""))
	, m_num1(0)
	, m_num2(0)
{

}

CMyInput2::~CMyInput2()
{
}

void CMyInput2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MyInput2_MessageTitle, m_Title);
	DDX_Text(pDX, IDC_MyInput2_Message1, m_Message1);
	DDX_Text(pDX, IDC_MyInput2_Message2, m_Message2);
	DDX_Text(pDX, IDC_MyInput2_num1, m_num1);
	DDX_Text(pDX, IDC_MyInput2_num2, m_num2);
}


BEGIN_MESSAGE_MAP(CMyInput2, CDialog)
END_MESSAGE_MAP()


// CMyInput2 メッセージ ハンドラ

