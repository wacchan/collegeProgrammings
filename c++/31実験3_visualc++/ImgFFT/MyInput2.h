#pragma once


// CMyInput2 �_�C�A���O

class CMyInput2 : public CDialog
{
	DECLARE_DYNAMIC(CMyInput2)

public:
	CMyInput2(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CMyInput2();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_MyInput2_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	CString m_Title;
	CString m_Message1;
	CString m_Message2;
	double m_num1;
	double m_num2;
};
