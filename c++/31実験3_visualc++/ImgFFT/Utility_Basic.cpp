

#include "stdafx.h"
#include "ImgFFT.h"

#include "MyInput.h"
#include "MyInput2.h"

/////////////////////////////////////////////
// PGMファイル名取得
//     flag = 0 ： 入力ファイル名
//          = 1 ： 出力ファイル名
CString GetPgmFileName( int flag )
{
CString fname;
BOOL    in_out;
CString m_filter;

	if( flag==1 ) {
		in_out = FALSE;
		m_filter = "Output Image File(*.pgm)|*.pgm|All File(*.*)|*.*||";
	}  else {
		in_out = TRUE;
		m_filter = "Input Image File(*.pgm)|*.pgm|All File(*.*)|*.*||";
	}

	CFileDialog  dlg(FALSE, "pgm", NULL, 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
		m_filter );

	dlg.m_ofn.lpstrTitle = "Portabel Gray Map File";
	if( dlg.DoModal() == IDCANCEL ) {
		return "";
	}

	fname = dlg.GetPathName();

	return fname;
}

FILE *GetSaveFilePointer( CString *file_name, CString *dir_name )
{
CString m_file_name;
FILE	*fp;
errno_t  err;

	CFileDialog  dlg(FALSE, "pgm", NULL, 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
		"Output Image File(*.pgm)|*.pgm|All File(*.*)|*.*||");

	dlg.m_ofn.lpstrTitle = "Portabel Gray Map File";
	dlg.m_ofn.lpstrInitialDir = CImgFFTApp::m_OutputDir;
	if( dlg.DoModal() == IDCANCEL ) {
		return NULL;
	}

	m_file_name = dlg.GetPathName();
	*file_name = m_file_name;

	CString	mm;
	mm = m_file_name;
	mm = mm.Left( mm.ReverseFind( _T('\\') ) );
	mm += _T('\\');
	*dir_name = mm;


	if( (err=fopen_s(&fp,m_file_name,"wb"))!= 0 ) {
		CString buff1;
		buff1.Format( "ファイルを開くことが出来ませんでした\n  File Open Error : <%s> ", m_file_name );
		AfxMessageBox( buff1 );
		return NULL;
	}

	return fp;
}


FILE *GetLoadFilePointer( CString *file_name, CString *dir_name )
{
CString m_file_name;
FILE	*fp;
errno_t err;

	CFileDialog  dlg(TRUE, "pgm", NULL, 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
		"Input Image File(*.pgm)|*.pgm|All File(*.*)|*.*||");

	dlg.m_ofn.lpstrTitle = "Portabel Gray Map File 入力ファイル選択";
	dlg.m_ofn.lpstrInitialDir = *dir_name;
	if( dlg.DoModal() == IDCANCEL ) {
		return NULL;
	}
	m_file_name = dlg.GetPathName();
	*file_name = m_file_name;

	CString	mm;
	mm = m_file_name;
	mm = mm.Left( mm.ReverseFind( _T('\\') ) );
	mm += _T('\\');
	*dir_name = mm;

    /* 入力ファイルのオープン */
	if( (err=fopen_s(&fp,m_file_name,"rb"))!= 0 ) {
		CString msg1;
		msg1.Format( "その名前のファイルは存在しません\n  File Open Error : <%s> ", m_file_name );
		AfxMessageBox( msg1 );
		return NULL;
	}

	return fp;
}

double	GetNum( CString message )
{
CMyInput dlg;
double	num;

	dlg.m_num = m_Box_Num;
	dlg.m_Message = message;
	dlg.DoModal();
	m_Box_Num = dlg.m_num;
	num = m_Box_Num;
	return num;
}

void	GetNum2( CString title, CString mes1, CString mes2, double *v1, double *v2 )
{
CMyInput2 dlg;
	dlg.m_num1 = m_Box2_Num1;
	dlg.m_num2 = m_Box2_Num2;
	dlg.m_Title = title;
	dlg.m_Message1 = mes1;
	dlg.m_Message2 = mes2;
	dlg.DoModal();
	*v1 = dlg.m_num1;
	*v2 = dlg.m_num2;
	m_Box2_Num1 = *v1;
	m_Box2_Num2 = *v2;
}

int OutputFileSelect( CString *fname, CString *dir_name, int kind ) 
{
	CString m_file_name;
	int m_kind;

	CMyFileDialog  dlg(FALSE, "pgm", fname->GetBuffer(256), 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ENABLEHOOK, 
		"PGM File(*.pgm)|*.pgm|BMP File(*.bmp)|*.bmp|All File(*.*)|*.*||");
	fname->ReleaseBuffer();

	dlg.m_ofn.lpstrTitle = "出力ファイル(pgm or bmp)";
	dlg.m_ofn.lpstrInitialDir = *dir_name;

	dlg.m_ofn.nFilterIndex = kind;
	dlg.m_ofn.hInstance = AfxGetInstanceHandle();

	if( dlg.DoModal() == IDCANCEL ) {
		return kind;
	}

	*fname = dlg.m_Fname;
	m_kind = dlg.m_kind;

	*dir_name = dlg.m_FolderPath;

	return m_kind;
}

