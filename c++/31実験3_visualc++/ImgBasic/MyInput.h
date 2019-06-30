#pragma once

#include "ImgBasic.h"

// CMyInput ダイアログ

class CMyInput : public CDialog
{
	DECLARE_DYNAMIC(CMyInput)

public:
	CMyInput(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CMyInput();

// ダイアログ データ
	enum { IDD = IDD_MyInput1_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString m_Message;
	double m_num;
};
