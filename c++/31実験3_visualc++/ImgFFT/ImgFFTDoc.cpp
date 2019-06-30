
// ImgFFTDoc.cpp : CImgFFTDoc クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、サムネイル、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "ImgFFT.h"
#endif

#include "ImgFFTDoc.h"

#include <propkey.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImgFFTDoc

IMPLEMENT_DYNCREATE(CImgFFTDoc, CDocument)

BEGIN_MESSAGE_MAP(CImgFFTDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CImgFFTDoc::OnFileOpen)
	ON_COMMAND(ID_Img1_Reverse, &CImgFFTDoc::OnImg1Reverse)
	ON_UPDATE_COMMAND_UI(ID_Img1_Reverse, &CImgFFTDoc::OnUpdateImg1Reverse)
	ON_COMMAND(ID_ImgFFT, &CImgFFTDoc::OnImgFFT)
	ON_UPDATE_COMMAND_UI(ID_ImgFFT, &CImgFFTDoc::OnUpdateImgFFT)
	ON_COMMAND(ID_ImgIFFT, &CImgFFTDoc::OnImgIFFT)
	ON_UPDATE_COMMAND_UI(ID_ImgIFFT, &CImgFFTDoc::OnUpdateImgIFFT)
	ON_COMMAND(ID_ImgFilter1, &CImgFFTDoc::OnImgFilter1)
	ON_UPDATE_COMMAND_UI(ID_ImgFilter1, &CImgFFTDoc::OnUpdateImgFilter1)
	ON_COMMAND(ID_ImgFilter2, &CImgFFTDoc::OnImgFilter2)
	ON_UPDATE_COMMAND_UI(ID_ImgFilter2, &CImgFFTDoc::OnUpdateImgFilter2)
	ON_COMMAND(ID_ImgFilter3, &CImgFFTDoc::OnImgFilter3)
	ON_UPDATE_COMMAND_UI(ID_ImgFilter3, &CImgFFTDoc::OnUpdateImgFilter3)
	ON_COMMAND(ID_Img1Real, &CImgFFTDoc::OnImg1Real)
	ON_UPDATE_COMMAND_UI(ID_Img1Real, &CImgFFTDoc::OnUpdateImg1Real)
	ON_COMMAND(ID_Img1Power, &CImgFFTDoc::OnImg1Power)
	ON_UPDATE_COMMAND_UI(ID_Img1Power, &CImgFFTDoc::OnUpdateImg1Power)
	ON_COMMAND(ID_Img1Ima, &CImgFFTDoc::OnImg1Ima)
	ON_UPDATE_COMMAND_UI(ID_Img1Ima, &CImgFFTDoc::OnUpdateImg1Ima)
	ON_COMMAND(ID_ImgFILE_MakeFig, &CImgFFTDoc::OnImgfileMakeFig)
	ON_COMMAND(ID_Img1GainFix, &CImgFFTDoc::OnImg1GainFix)
	ON_UPDATE_COMMAND_UI(ID_Img1GainFix, &CImgFFTDoc::OnUpdateImg1GainFix)
	ON_COMMAND(ID_ImgBackup0, &CImgFFTDoc::OnImgBackup0)
	ON_UPDATE_COMMAND_UI(ID_ImgBackup0, &CImgFFTDoc::OnUpdateImgBackup0)
	ON_COMMAND(ID_ImgBackup1, &CImgFFTDoc::OnImgBackup1)
	ON_UPDATE_COMMAND_UI(ID_ImgBackup1, &CImgFFTDoc::OnUpdateImgBackup1)
	ON_COMMAND(ID_ImgFILE_Save0, &CImgFFTDoc::OnImgFileSave0)
	ON_UPDATE_COMMAND_UI(ID_ImgFILE_Save0, &CImgFFTDoc::OnUpdateImgFileSave0)
	ON_COMMAND(ID_ImgFILE_Save1, &CImgFFTDoc::OnImgFileSave1)
	ON_UPDATE_COMMAND_UI(ID_ImgFILE_Save1, &CImgFFTDoc::OnUpdateImgFileSave1)
END_MESSAGE_MAP()


// CImgFFTDoc コンストラクション/デストラクション

CImgFFTDoc::CImgFFTDoc()
{
	// TODO: この位置に 1 度だけ呼ばれる構築用のコードを追加してください。
	p_Pgm0 = NULL;
	p_Pgm1 = NULL;
	p_Pgm2 = NULL;
	p_Pgm0_temp = NULL;
	p_Pgm1_temp = NULL;

	m_freq1 = 0.1;
	m_freq2 = 0.0;
	m_rotate = 0.0;
	m_kind = 0;

	Comp_mat = NULL;
	Comp_mat_temp = NULL;
	m_disp_kind = 0;
	m_FFT_Flag = FALSE;

	m_FFTImgGainFlag = TRUE;
//	m_FFTImgGainFlag = FALSE;
	m_FftMax = 255;
	m_FftMin = 0;

	m_Reverse_Flag = FALSE;
	m_gain = 0.5;
}

CImgFFTDoc::~CImgFFTDoc()
{
	if( p_Pgm0 != NULL ) delete p_Pgm0;
	if( p_Pgm1 != NULL ) delete p_Pgm1;
	if( p_Pgm2 != NULL ) delete p_Pgm2;
	if( p_Pgm0_temp != NULL ) delete p_Pgm0_temp;
	if( p_Pgm1_temp != NULL ) delete p_Pgm1_temp;

	m_Bmp0.ClearPicture();
	m_Bmp1.ClearPicture();

	if( Comp_mat != NULL ) delete Comp_mat;
	if( Comp_mat_temp != NULL ) delete Comp_mat_temp;

}

BOOL CImgFFTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}




// CImgFFTDoc シリアル化

void CImgFFTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 格納するコードをここに追加してください。
	}
	else
	{
		// TODO: 読み込むコードをここに追加してください。
	}
}

#ifdef SHARED_HANDLERS

// サムネイルのサポート
void CImgFFTDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// このコードを変更してドキュメントのデータを描画します
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 検索ハンドラーのサポート
void CImgFFTDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ドキュメントのデータから検索コンテンツを設定します。 
	// コンテンツの各部分は ";" で区切る必要があります

	// 例:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImgFFTDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImgFFTDoc 診断

#ifdef _DEBUG
void CImgFFTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImgFFTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImgFFTDoc コマンド





////////////////////////////////////////////////////////////////////////////////
void CImgFFTDoc::Check_Backup_Pgm0() 
{
	if( p_Pgm0 != NULL )  {
		if( p_Pgm0_temp != NULL ) delete p_Pgm0_temp;
		p_Pgm0_temp = new CImgPgm;
		p_Pgm0_temp->CopyImage( p_Pgm0 );
		delete p_Pgm0;
	}
	p_Pgm0 = new CImgPgm;
}

void CImgFFTDoc::Check_Backup_Pgm1() 
{
	if( p_Pgm1 != NULL )  {
		if( p_Pgm1_temp != NULL ) delete p_Pgm1_temp;
		p_Pgm1_temp = new CImgPgm;
		p_Pgm1_temp->CopyImage( p_Pgm1 );
		delete p_Pgm1;
	}
	p_Pgm1 = new CImgPgm;
}

void CImgFFTDoc::Check_Backup_CMat() 
{
	if( Comp_mat != NULL )  {
		if( Comp_mat_temp != NULL ) delete Comp_mat_temp;
		Comp_mat_temp = new CCompMat;
		Comp_mat_temp->CopyCMat( Comp_mat );
		delete Comp_mat;
	}
	Comp_mat = new CCompMat;
	Comp_mat->CopyCMat( Comp_mat_temp );
}

void CImgFFTDoc::MakeReal() 
{
	double m_max, m_min, temp;
	int x, y, xs, ys;
	xs = p_Pgm1->m_xsize;
	ys = p_Pgm1->m_ysize;

	if( m_FFTImgGainFlag == TRUE ) {
		m_max = m_FftMax;
		m_min = m_FftMin;
	} 
	else 
	{
		m_max = log(Comp_mat->mat[0][0].real+1);
		m_min = log(Comp_mat->mat[0][0].real+1);
//		m_max = Comp_mat->mat[0][0].real;
//		m_min = Comp_mat->mat[0][0].real;
		for( y=0; y<ys; y++ ) {
			for( x=0; x<xs; x++ ) {
				temp = log(Comp_mat->mat[y][x].real+1);
//				temp = Comp_mat->mat[y][x].real;
				if( temp > m_max ) m_max = temp;
				if( temp < m_min ) m_min = temp;
			}
		}
	}

	temp = 255.0 / (m_max - m_min);
	int tt;
	for( y=0; y<ys; y++ ) {
		for( x=0; x<xs; x++ ) {
			tt = (int)((log(Comp_mat->mat[y][x].real+1) -m_min )* temp);
//			tt = (int)((Comp_mat->mat[y][x].real - m_min )* temp);
			if( tt > 255 ) tt = 255;
			if( tt < 0   ) tt = 0;
			p_Pgm1->image[y][x] = tt;
		}
	}
	unsigned char tim;
	for(x=0; x<xs/2; x++){
		for(y=0; y<ys/2; y++){
			tim = p_Pgm1->image[y][x];
			p_Pgm1->image[y][x] = p_Pgm1->image[y+ys/2][x+xs/2];
			p_Pgm1->image[y+ys/2][x+xs/2] = tim;
			tim = p_Pgm1->image[y+ys/2][x];
			p_Pgm1->image[y+ys/2][x] = p_Pgm1->image[y][x+xs/2];
			p_Pgm1->image[y][x+xs/2] = tim;
		}
	}
}

void CImgFFTDoc::MakeImag() 
{
	double m_max, m_min, temp;
	int x, y, xs, ys;
	xs = p_Pgm1->m_xsize;
	ys = p_Pgm1->m_ysize;

	if( m_FFTImgGainFlag == TRUE ) {
		m_max = m_FftMax;
		m_min = m_FftMin;
	} 
	else 
	{
		m_max = log(Comp_mat->mat[0][0].imag+1);
		m_min = log(Comp_mat->mat[0][0].imag+1);
//		m_max = Comp_mat->mat[0][0].imag;
//		m_min = Comp_mat->mat[0][0].imag;
		for( y=0; y<ys; y++ ) {
			for( x=0; x<xs; x++ ) {
				temp = log(Comp_mat->mat[y][x].imag+1);
//				temp = Comp_mat->mat[y][x].imag;
				if( temp > m_max ) m_max = temp;
				if( temp < m_min ) m_min = temp;
			}
		}
	}

	temp = 255.0 / (m_max - m_min);
	int tt;
	for( y=0; y<ys; y++ ) {
		for( x=0; x<xs; x++ ) {
			tt = (int)((log(Comp_mat->mat[y][x].imag+1) -m_min )* temp);
//			tt = (int)((Comp_mat->mat[y][x].imag - m_min )* temp);
			if( tt > 255 ) tt = 255;
			if( tt < 0   ) tt = 0;
			p_Pgm1->image[y][x] = tt;
		}
	}
	unsigned char tim;
	for(x=0; x<xs/2; x++){
		for(y=0; y<ys/2; y++){
			tim = p_Pgm1->image[y][x];
			p_Pgm1->image[y][x] = p_Pgm1->image[y+ys/2][x+xs/2];
			p_Pgm1->image[y+ys/2][x+xs/2] = tim;
			tim = p_Pgm1->image[y+ys/2][x];
			p_Pgm1->image[y+ys/2][x] = p_Pgm1->image[y][x+xs/2];
			p_Pgm1->image[y][x+xs/2] = tim;
		}
	}
}

void CImgFFTDoc::MakePower() 
{
	double m_max, m_min, temp;
	int x, y, xs, ys;
	xs = p_Pgm1->m_xsize;
	ys = p_Pgm1->m_ysize;

	m_max = log(Comp_mat->mat[0][0].abs()+1);
	m_min = log(Comp_mat->mat[0][0].abs()+1);
	for( y=0; y<ys; y++ ) {
		for( x=0; x<xs; x++ ) {
			temp = log(Comp_mat->mat[y][x].abs()+1);
			if( temp > m_max ) m_max = temp;
			if( temp < m_min ) m_min = temp;
		}
	}
	temp = 255.0 / (m_max - m_min);
	int tt;
	for( y=0; y<ys; y++ ) {
		for( x=0; x<xs; x++ ) {
			tt = (int)((log(Comp_mat->mat[y][x].abs()+1) -m_min )* temp);
			if( tt > 255 ) tt = 255;
			if( tt < 0   ) tt = 0;
			p_Pgm1->image[y][x] = tt;
		}
	}
	unsigned char tim;
	for(x=0; x<xs/2; x++){
		for(y=0; y<ys/2; y++){
			tim = p_Pgm1->image[y][x];
			p_Pgm1->image[y][x] = p_Pgm1->image[y+ys/2][x+xs/2];
			p_Pgm1->image[y+ys/2][x+xs/2] = tim;
			tim = p_Pgm1->image[y+ys/2][x];
			p_Pgm1->image[y+ys/2][x] = p_Pgm1->image[y][x+xs/2];
			p_Pgm1->image[y][x+xs/2] = tim;
		}
	}

	m_FftMax = m_max;
	m_FftMin = m_min;
}

void CImgFFTDoc::ReDrawPgm1()
{
	if( p_Pgm1 != NULL ) {
		m_Bmp1.SetPicture_g( p_Pgm1, m_gain );
		UpdateAllViews( NULL );
	}
}

CImgBmp	*CImgFFTDoc::GetBmp()
{
	if( m_Reverse_Flag == TRUE ) 
	{
		CImgPgm pgm;
		pgm.CopyImage( p_Pgm1 );
		pgm.ImgReverse();
		m_Bmp1_rev.SetPicture_g( &pgm, m_gain );
		return &m_Bmp1_rev;
	}  
	else 
	{
		return &m_Bmp1;
	}
}
////////////////////////////////////////////////////////////////////////////////


void CImgFFTDoc::OnFileOpen()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	if( p_Pgm0 != NULL )  {
		delete p_Pgm0;
		if( p_Pgm1      != NULL ) { delete p_Pgm1; 	    p_Pgm1 = NULL;}
		if( p_Pgm1_temp != NULL ) { delete p_Pgm1_temp; p_Pgm1_temp = NULL;}
	}
	p_Pgm0 = new CImgPgm;

	if( p_Pgm0->LoadFile( &m_OpenFileName, &(CImgFFTApp::m_InputDir) )==FALSE ) return;
	m_Bmp0.SetPicture( p_Pgm0 );
	m_Bmp1.ClearPicture();
	m_FFT_Flag = FALSE;

	if( Comp_mat != NULL ) delete Comp_mat;
	Comp_mat = NULL;
	if( Comp_mat_temp != NULL ) delete Comp_mat_temp;
	Comp_mat_temp = NULL;

	UpdateAllViews( NULL );	
}


void CImgFFTDoc::OnImg1Reverse()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_Reverse_Flag = !m_Reverse_Flag;
	UpdateAllViews( NULL, 2 );
}


void CImgFFTDoc::OnUpdateImg1Reverse(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( p_Pgm1 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}

	if( m_Reverse_Flag == TRUE ) pCmdUI->SetCheck( 1 );
	 else pCmdUI->SetCheck( 0 );
}


void CImgFFTDoc::OnImgFFT()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	int xs, ys;

//	Check_Backup_Pgm1();

	xs = p_Pgm0->m_xsize;
	ys = p_Pgm0->m_ysize;
	if( Comp_mat != NULL ) delete Comp_mat;
	Comp_mat = new CCompMat;
	Comp_mat->Create( xs, ys );
	
	if( Make_FFT_Data( p_Pgm0, Comp_mat )!= 0 ) {
		delete Comp_mat;
		Comp_mat = NULL;
		return;
	}
	kfft2( Comp_mat, xs, 1 );

	Check_Backup_Pgm1();

	p_Pgm1->Create( xs, ys, p_Pgm0->m_max_gray );
	m_FFT_Flag = TRUE;

	MakePower();
	switch( m_disp_kind ) {
		case 1: MakeReal();		break;
		case 2: MakeImag();		break;
		case 0:
		default: /*MakePower();	*/break;
	}

	m_Bmp1.SetPicture( p_Pgm1 );

	UpdateAllViews( NULL );	
}


void CImgFFTDoc::OnUpdateImgFFT(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgFFTDoc::OnImgIFFT()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	int	x, y, xs, ys;
	xs = p_Pgm1->m_xsize;
	ys = p_Pgm1->m_ysize;

	Check_Backup_Pgm0();
	p_Pgm0->Create( xs, ys, p_Pgm1->m_max_gray );

	CCompMat b( Comp_mat->x_s, Comp_mat->y_s );
	for( x=0; x<b.x_s; x++ ) {
		for( y=0; y<b.y_s; y++ ) {
			b.mat[x][y] = Comp_mat->mat[x][y];
		}
	}

//    kfft2( Comp_mat, xs, -1 );
    kfft2( &b, xs, -1 );

	for( y=0; y<ys; y++ ) {
		for( x=0; x<xs; x++ ) {
//			p_Pgm0->image[y][x] = (int)(Comp_mat->mat[y][x].real);
			p_Pgm0->image[y][x] = (int)(b.mat[y][x].real);
		}
	}
	m_Bmp0.SetPicture( p_Pgm0 );

	UpdateAllViews( NULL );	
}


void CImgFFTDoc::OnUpdateImgIFFT(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( m_FFT_Flag == TRUE ) {	pCmdUI->Enable( TRUE ); }
	 else					 {	pCmdUI->Enable( FALSE );}
}


void CImgFFTDoc::OnImgFilter1()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	int xs, ys, gray;
	xs = p_Pgm1->m_xsize;
	ys = p_Pgm1->m_ysize;
	gray = p_Pgm1->m_max_gray;

	fft_filtering1( Comp_mat, xs );

	Check_Backup_Pgm1();
	p_Pgm1->Create( xs, ys, gray );
	Check_Backup_CMat();

	m_disp_kind = 0;
	MakePower();

	m_Bmp1.SetPicture_g( p_Pgm1, m_gain );

	UpdateAllViews( NULL );	
}


void CImgFFTDoc::OnUpdateImgFilter1(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( m_FFT_Flag == TRUE ) {	pCmdUI->Enable( TRUE ); }
	 else					 {	pCmdUI->Enable( FALSE );}
}


void CImgFFTDoc::OnImgFilter2()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	int xs, ys;
	xs = p_Pgm1->m_xsize;
	ys = p_Pgm1->m_ysize;

	fft_filtering2( Comp_mat, xs );

	Check_Backup_Pgm1();
	p_Pgm1->Create( xs, ys, p_Pgm0->m_max_gray );
	Check_Backup_CMat();

	m_disp_kind = 0;
	MakePower();

	m_Bmp1.SetPicture_g( p_Pgm1, m_gain );

	UpdateAllViews( NULL );	
}


void CImgFFTDoc::OnUpdateImgFilter2(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( m_FFT_Flag == TRUE ) {	pCmdUI->Enable( TRUE ); }
	 else					 {	pCmdUI->Enable( FALSE );}
}


void CImgFFTDoc::OnImgFilter3()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	int xs, ys;
	xs = p_Pgm1->m_xsize;
	ys = p_Pgm1->m_ysize;

	fft_filtering3( Comp_mat, xs );

	Check_Backup_Pgm1();
	p_Pgm1->Create( xs, ys, p_Pgm0->m_max_gray );
	Check_Backup_CMat();

	m_disp_kind = 0;
	MakePower();

	m_Bmp1.SetPicture_g( p_Pgm1, m_gain );

	UpdateAllViews( NULL );	
}


void CImgFFTDoc::OnUpdateImgFilter3(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( m_FFT_Flag == TRUE ) {	pCmdUI->Enable( TRUE ); }
	 else					 {	pCmdUI->Enable( FALSE );}
}


void CImgFFTDoc::OnImg1Real()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_disp_kind = 1;
	MakeReal();

	m_Bmp1.SetPicture( p_Pgm1 );
	UpdateAllViews( NULL );	
}


void CImgFFTDoc::OnUpdateImg1Real(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( m_FFT_Flag == TRUE ) {	pCmdUI->Enable( TRUE ); }
	 else					 {	pCmdUI->Enable( FALSE );}
	if( m_disp_kind == 1 ) { pCmdUI->SetCheck( 1 ); }
	 else					{ pCmdUI->SetCheck( 0 ); }
}


void CImgFFTDoc::OnImg1Power()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_disp_kind = 0;
	MakePower();

	m_Bmp1.SetPicture( p_Pgm1 );
	UpdateAllViews( NULL );	
}


void CImgFFTDoc::OnUpdateImg1Power(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	// TODO: ここにコマンド更新 UI ハンドラ コードを追加します。
	if( m_FFT_Flag == TRUE ) {	pCmdUI->Enable( TRUE ); }
	 else					 {	pCmdUI->Enable( FALSE );}
	if( m_disp_kind == 0 ) { pCmdUI->SetCheck( 1 ); }
	 else					{ pCmdUI->SetCheck( 0 ); }
}


void CImgFFTDoc::OnImg1Ima()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_disp_kind = 2;
	MakeImag();

	m_Bmp1.SetPicture( p_Pgm1 );
	UpdateAllViews( NULL );	
}


void CImgFFTDoc::OnUpdateImg1Ima(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( m_FFT_Flag == TRUE ) {	pCmdUI->Enable( TRUE ); }
	 else					 {	pCmdUI->Enable( FALSE );}
	if( m_disp_kind == 2 ) { pCmdUI->SetCheck( 1 ); }
	 else					{ pCmdUI->SetCheck( 0 ); }
}


void CImgFFTDoc::OnImgfileMakeFig()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	if( p_Pgm0 != NULL ) delete p_Pgm0;
	if( p_Pgm1 != NULL ) delete p_Pgm1;
	p_Pgm1 = NULL;
	p_Pgm0 = new CImgPgm;
	p_Pgm0->Create( 256, 256, 255 );
	p_Pgm0->SetBit( 0 );

	CMyMakeFigureDialog dlg;
		dlg.m_freq1 = m_freq1;
		dlg.m_freq2 = m_freq2;
		dlg.m_rotate = m_rotate;
		dlg.m_kind  = m_kind;
	dlg.DoModal();
		m_freq1 = dlg.m_freq1;
		m_freq2 = dlg.m_freq2;
		m_rotate = dlg.m_rotate;
		m_kind = dlg.m_kind;

	p_Pgm0->MakeFigure( m_kind, m_freq1, m_freq2, m_rotate );

	m_Bmp0.SetPicture( p_Pgm0 );
	m_Bmp1.ClearPicture();

	if( Comp_mat != NULL ) delete Comp_mat;
	Comp_mat = NULL;
	if( Comp_mat_temp != NULL ) delete Comp_mat_temp;
	Comp_mat_temp = NULL;

	m_FFT_Flag = FALSE;

	UpdateAllViews( NULL );	
}


void CImgFFTDoc::OnImg1GainFix()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_FFTImgGainFlag = !m_FFTImgGainFlag;
}


void CImgFFTDoc::OnUpdateImg1GainFix(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->SetCheck( m_FFTImgGainFlag );	
}


void CImgFFTDoc::OnImgBackup0()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	delete p_Pgm0;
	p_Pgm0 = new CImgPgm;
	p_Pgm0->CopyImage( p_Pgm0_temp );
	delete p_Pgm0_temp;
	p_Pgm0_temp = NULL;

	m_Bmp0.SetPicture( p_Pgm0 );

	UpdateAllViews( NULL, 1 );	
}


void CImgFFTDoc::OnUpdateImgBackup0(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( p_Pgm0_temp != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgFFTDoc::OnImgBackup1()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	delete p_Pgm1;
	p_Pgm1 = new CImgPgm;
	p_Pgm1->CopyImage( p_Pgm1_temp );
	delete p_Pgm1_temp;
	p_Pgm1_temp = NULL;

	delete Comp_mat;
	Comp_mat = new CCompMat;
	Comp_mat->CopyCMat( Comp_mat_temp );
	delete Comp_mat_temp;
	Comp_mat_temp = NULL;

	m_Bmp1.SetPicture( p_Pgm1 );

	UpdateAllViews( NULL, 2 );	
}


void CImgFFTDoc::OnUpdateImgBackup1(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( p_Pgm1_temp != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgFFTDoc::OnImgFileSave0()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
CString fname;
int		kind;

	kind = OutputFileSelect( &fname, &(CImgFFTApp::m_OutputDir), 0 );
	switch( kind ) {
	case 1: p_Pgm0->SaveFile( fname );
		break;
	case 2: m_Bmp0.SaveFile( fname );
		break;
	default:
		break;
	}	
}


void CImgFFTDoc::OnUpdateImgFileSave0(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgFFTDoc::OnImgFileSave1()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
CString fname;
int		kind;

	kind = OutputFileSelect( &fname, &(CImgFFTApp::m_OutputDir), 0 );
	switch( kind ) {
	case 1: p_Pgm1->SaveFile( fname );
		break;
	case 2: m_Bmp1.SaveFile( fname );
		break;
	default:
		break;
	}	
}


void CImgFFTDoc::OnUpdateImgFileSave1(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	if( p_Pgm1 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}
