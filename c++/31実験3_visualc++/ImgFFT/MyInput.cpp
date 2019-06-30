// MyInput.cpp : 実装ファイル
//

#include "stdafx.h"
//#include "ImgBasic.h"
#include "MyInput.h"


// CMyInput ダイアログ

IMPLEMENT_DYNAMIC(CMyInput, CDialog)

CMyInput::CMyInput(CWnd* pParent /*=NULL*/)
	: CDialog(CMyInput::IDD, pParent)
	, m_Message(_T(""))
	, m_num(0)
{

}

CMyInput::~CMyInput()
{
}

void CMyInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MyInput_MessageTitle, m_Message);
	DDX_Text(pDX, IDC_MyInput_num, m_num);
}


BEGIN_MESSAGE_MAP(CMyInput, CDialog)
END_MESSAGE_MAP()


// CMyInput メッセージ ハンドラ
