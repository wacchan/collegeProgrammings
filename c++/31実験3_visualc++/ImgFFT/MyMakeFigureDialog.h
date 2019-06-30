#pragma once


// CMyMakeFigureDialog ダイアログ

class CMyMakeFigureDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyMakeFigureDialog)

public:
	CMyMakeFigureDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CMyMakeFigureDialog();

// ダイアログ データ
	enum { IDD = IDD_MyMakeFigureDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	double m_freq1;
	double m_freq2;
	double m_rotate;
	int m_kind;

};
