// MyFileDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ImgBasic.h"
#include "MyFileDialog.h"


// CMyFileDialog

IMPLEMENT_DYNAMIC(CMyFileDialog, CFileDialog)

CMyFileDialog::CMyFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}

CMyFileDialog::~CMyFileDialog()
{
}


BEGIN_MESSAGE_MAP(CMyFileDialog, CFileDialog)
END_MESSAGE_MAP()



// CMyFileDialog メッセージ ハンドラ



void CMyFileDialog::OnTypeChange()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
/*
	CString f_name, ff_name, dir_name, title_name;
	ff_name  = GetPathName();  // d:\data\abc.bmp
	m_Fname  = GetFileName();  // abc.bmp
	title_name = GetFileTitle();  // abc
	dir_name = GetFileExt();      // bmp
*/
	UpdateData( TRUE );
	m_Fname  = GetPathName();  // abc.bmp
	m_kind = m_ofn.nFilterIndex;
	m_FolderPath = GetFolderPath();


//	 CEdit* pE =(CEdit*)GetParent()->GetDlgItem( edt1 );

//	 CWnd* ppe = (CWnd*)GetParent();
//	 pE = (CEdit*)ppe->GetDlgItem( AFX_IDC_LISTBOX );
//	 pE = (CEdit*)this->GetDlgItem( edt1 );
//	 pE = (CEdit*)this->GetDlgCtrlID();

//	 pE = (CEdit*)GetDlgItem( edt1 );


	CFileDialog::OnTypeChange();
}


void CMyFileDialog::OnFileNameChange()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
//	AfxMessageBox( "change" );
	UpdateData( TRUE );
	m_Fname  = GetPathName();  // abc.bmp
	m_kind = m_ofn.nFilterIndex;
	m_FolderPath = GetFolderPath();

	CFileDialog::OnFileNameChange();
}


BOOL CMyFileDialog::OnFileNameOK()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	UpdateData( TRUE );
	m_Fname  = GetPathName();  // abc.bmp
	m_kind = m_ofn.nFilterIndex;
	m_FolderPath = GetFolderPath();
	m_ExtName = GetFileExt();

	if( m_ExtName.GetLength() == 0 ) {
		if( m_kind == 1 ) m_ExtName = "pgm";
		else m_ExtName = "bmp";

		return CFileDialog::OnFileNameOK();
	}

	if( m_ExtName.Compare( "bmp" )==0 ) {
		m_kind = 2;
		m_ofn.nFilterIndex = m_kind;
	} else {
		m_kind = 1;
		m_ofn.nFilterIndex = m_kind;
	}

	return CFileDialog::OnFileNameOK();
}


BOOL CMyFileDialog::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	TRACE( "Windows message : %d,  %d <%5d>\n", message, HIWORD(wParam), WM_DESTROY );
	if( message == WM_DESTROY ) {
//		UpdateData( TRUE );
	}


	return CFileDialog::OnWndMsg(message, wParam, lParam, pResult);
}


