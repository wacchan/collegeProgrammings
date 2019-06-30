#pragma once

#include <afxdlgs.h>
#include <dlgs.h>

// CMyFileDialog

class CMyFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CMyFileDialog)

public:
	CMyFileDialog(BOOL bOpenFileDialog, // FileOpen Ç… TRUE ÇÅAFileSaveAs Ç… FALSE ÇéwíËÇµÇ‹Ç∑ÅB
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	virtual ~CMyFileDialog();

	CString	m_Fname;
	CString m_FolderPath;
	CString m_ExtName;
	int		m_kind;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnTypeChange();
	virtual void OnFileNameChange();
	virtual BOOL OnFileNameOK();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:

};


