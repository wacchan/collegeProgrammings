#pragma once


// CMyMakeFigureDialog �_�C�A���O

class CMyMakeFigureDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyMakeFigureDialog)

public:
	CMyMakeFigureDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CMyMakeFigureDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_MyMakeFigureDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	double m_freq1;
	double m_freq2;
	double m_rotate;
	int m_kind;

};
