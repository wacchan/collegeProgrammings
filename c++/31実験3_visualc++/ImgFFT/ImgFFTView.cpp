
// ImgFFTView.cpp : CImgFFTView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、サムネイル、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "ImgFFT.h"
#endif

#include "ImgFFTDoc.h"
#include "ImgFFTView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImgFFTView

IMPLEMENT_DYNCREATE(CImgFFTView, CFormView)

BEGIN_MESSAGE_MAP(CImgFFTView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_ImgGainReset, &CImgFFTView::OnBnClickedImgGainReset)
END_MESSAGE_MAP()

// CImgFFTView コンストラクション/デストラクション

CImgFFTView::CImgFFTView()
	: CFormView(CImgFFTView::IDD)
	, m_gainEdit(0)
{
	// TODO: 構築コードをここに追加します。
	m_gainEdit = 0.0f;
	m_InitFlag = TRUE;
}

CImgFFTView::~CImgFFTView()
{
}

void CImgFFTView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture1, m_Picture1);
	DDX_Control(pDX, IDC_Picture2, m_Picture2);
	DDX_Text(pDX, IDC_ImgGainEdit, m_gainEdit);
	DDX_Control(pDX, IDC_ImgGainSlider, m_SliderCtrl);
}

BOOL CImgFFTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CFormView::PreCreateWindow(cs);
}

void CImgFFTView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CImgFFTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if( m_InitFlag == TRUE ) {
		m_SliderCtrl.SetRange( 1, 255 );
		m_SliderCtrl.SetPos( 128 );
		m_SliderCtrl.SetTicFreq( 16 );

		float g;
		g = (float)(128) / (float)64.0 - 1;
		g = (float)pow( 10, g );

		pDoc->m_gain = g;
		m_gainEdit   = g;
		UpdateData( FALSE );
	}
}

void CImgFFTView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImgFFTView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImgFFTView 診断

#ifdef _DEBUG
void CImgFFTView::AssertValid() const
{
	CFormView::AssertValid();
}

void CImgFFTView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CImgFFTDoc* CImgFFTView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgFFTDoc)));
	return (CImgFFTDoc*)m_pDocument;
}
#endif //_DEBUG


// CImgFFTView メッセージ ハンドラー


void CImgFFTView::OnDraw(CDC* pDC )
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CImgFFTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CImgBmp *p_bmp;
	HDC			hDC;			// デバイスコンテキストのハンドル

	if( !pDoc->m_Bmp0.m_SetFlag ) return;
	p_bmp = &(pDoc->m_Bmp0);

	// m_hWndで示す現在のウィンドウのデバイスコンテキストを取得
	// このデバイスコンテキストは描画終了後に ReleaseDCで開放する必要がある．
	hDC = m_Picture1.GetDC()->GetSafeHdc();
	DrawPicture( p_bmp, hDC );
	::ReleaseDC( m_hWnd, hDC );

	if( !pDoc->m_Bmp1.m_SetFlag ) return;
//	p_bmp = &(pDoc->m_Bmp1);
	p_bmp = pDoc->GetBmp();

	hDC = m_Picture2.GetDC()->GetSafeHdc();
	DrawPicture( p_bmp, hDC );
	::ReleaseDC( m_hWnd, hDC );
}

void CImgFFTView::DrawPicture( CImgBmp *p_bmp, HDC hDC ) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください

		HBITMAP		myDIB;			// ビットマップのハンドル
		HBITMAP		oldDIB;
//		HDC			hDC;			// デバイスコンテキストのハンドル
		HDC			hCompatiDC;		// メモリデバイスコンテキスト
		PAINTSTRUCT	ps;				// クライアント領域の描画に使う情報を保持


		// m_hWndで示す現在のウィンドウのデバイスコンテキストを取得
		// このデバイスコンテキストは描画終了後に ReleaseDCで開放する必要がある．
//		hDC = m_picture.GetDC()->GetSafeHdc();

		// 描画の準備をする
		// 描画が終了したら必ず EndPaintを実行する必要がある．
		::BeginPaint( m_hWnd, &ps );

		// hDCと互換性のあるメモリデバイスコンテキストを作成する．
		hCompatiDC = ::CreateCompatibleDC( hDC );

		// DIB形成期ビットマップから DDB（デバイス依存）形式ビットマップを作成する．
//		myDIB = ::CreateDIBitmap( hDC, &p_bmp->pbmi->bmiHeader,
//			CBM_INIT, m_BmpImage, m_BmpInfo, DIB_RGB_COLORS );
		myDIB = ::CreateDIBitmap( hDC, &p_bmp->pbmi->bmiHeader, 
			CBM_INIT,
			p_bmp->pbits, p_bmp->pbmi, DIB_RGB_COLORS);

		// hCompatiDCで myDIBの示すオブジェクトを使用できるようにする．
		// オリジナルビットマップを oldDIBに保存しておき，後で復活させる．
		oldDIB = (HBITMAP)::SelectObject( hCompatiDC, myDIB );

		// hCompatiDCにある画像をhDCに表示する．
	//	BitBlt( hDC, 0, 0, m_BmpInfo->bmiHeader.biWidth,
	//		m_BmpInfo->bmiHeader.biHeight, hCompatiDC, 0, 0, SRCCOPY );

		BitBlt( hDC, 0, 0, p_bmp->pbmi->bmiHeader.biWidth,
			p_bmp->pbmi->bmiHeader.biHeight, hCompatiDC,
			0, 0, SRCCOPY );

//		StretchBlt( hDC, 0, 0, m_width, m_height, hCompatiDC, 0, 0, 
//		p_bmp->pbmi->bmiHeader.biWidth,
//		p_bmp->pbmi->bmiHeader.biHeight,
//		SRCCOPY );

		// BeginPaint対応処理
		::EndPaint( m_hWnd, &ps );

		// オブジェクトの解放など
		::SelectObject( hCompatiDC, oldDIB );
		::DeleteObject( myDIB );
		::DeleteObject( hCompatiDC );
//		::ReleaseDC( m_hWnd, hDC );

		// -------------------------------------　ここまで追加

}



void CImgFFTView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	CImgFFTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	if( (CSliderCtrl *)pScrollBar == &m_SliderCtrl ) {
		if( nSBCode == SB_ENDSCROLL ) {
			int k = m_SliderCtrl.GetPos();
			float g;
			g = (float)(k) / (float)64.0 - 1;
			g = (float)pow( 10, g );

			pDoc->m_gain = g;
			m_gainEdit   = g;
			UpdateData( FALSE );

			pDoc->ReDrawPgm1();
		}
	}

//  SB_BOTTOM   一番下までスクロール。
//  SB_ENDSCROLL   スクロール終了。
//  SB_LINEDOWN   1 行下へスクロール。
//  SB_LINEUP   1 行上へスクロール。
//  SB_PAGEDOWN   1 ページ下へスクロール。
//  SB_PAGEUP   1 ページ上へスクロール。
//  SB_THUMBPOSITION   絶対位置へスクロール。現在位置は nPos で提供。
//  SB_THUMBTRACK   指定位置へスクロール ボックスをドラッグ。現在位置は nPos で提供。
//  SB_TOP   一番上までスクロール。 

	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CImgFFTView::OnBnClickedImgGainReset()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。	CImgFFTDoc* pDoc = GetDocument();
	CImgFFTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	m_SliderCtrl.SetPos( 128 );

	float g;
	g = (float)(128) / (float)64.0 - 1;
	g = (float)pow( 10, g );

	pDoc->m_gain = g;
	m_gainEdit   = g;
	UpdateData( FALSE );

	pDoc->ReDrawPgm1();
}
