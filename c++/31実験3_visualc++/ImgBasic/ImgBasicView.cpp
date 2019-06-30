
// ImgBasicView.cpp : CImgBasicView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、サムネイル、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "ImgBasic.h"
#endif

#include "ImgBasicDoc.h"
#include "ImgBasicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImgBasicView

IMPLEMENT_DYNCREATE(CImgBasicView, CFormView)

BEGIN_MESSAGE_MAP(CImgBasicView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CImgBasicView コンストラクション/デストラクション

CImgBasicView::CImgBasicView()
	: CFormView(CImgBasicView::IDD)
{
	// TODO: 構築コードをここに追加します。
	m_backColor = RGB(255,255,255);
	m_backBrush.CreateSolidBrush( m_backColor );
}

CImgBasicView::~CImgBasicView()
{
}

void CImgBasicView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture1, m_Picture1);
}

BOOL CImgBasicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。
//	cs.cx = 500;
//	cs.cy = 700;
//	cs.style &= ~WS_SIZEBOX;  
	return CFormView::PreCreateWindow(cs);
}

void CImgBasicView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CImgBasicView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImgBasicView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImgBasicView 診断

#ifdef _DEBUG
void CImgBasicView::AssertValid() const
{
	CFormView::AssertValid();
}

void CImgBasicView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CImgBasicDoc* CImgBasicView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgBasicDoc)));
	return (CImgBasicDoc*)m_pDocument;
}
#endif //_DEBUG


// CImgBasicView メッセージ ハンドラー


HBRUSH CImgBasicView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ここで DC の属性を変更してください。
	pDC->SetBkColor( m_backColor );
	return static_cast<HBRUSH>(m_backBrush.GetSafeHandle());

	// TODO:  既定値を使用したくない場合は別のブラシを返します。
	return hbr;
}


void CImgBasicView::OnDraw(CDC* pDC )
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CImgBasicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CImgBmp *p_bmp;
	HDC			hDC;			// デバイスコンテキストのハンドル

	if( !pDoc->m_Bmp0.m_SetFlag ) return;
	p_bmp = &(pDoc->m_Bmp0);

//	if( !pDoc->p_Pgm0 ) return;

//	CImgBmp bmp_temp;
//	bmp_temp.SetPicture( pDoc->p_Pgm0 );
//	p_bmp = &bmp_temp;
//	p_bmp = pDoc->p_Bmp0;
	
		HBITMAP		myDIB;			// ビットマップのハンドル
		HBITMAP		oldDIB;
//		HDC			hDC;			// デバイスコンテキストのハンドル
		HDC			hCompatiDC;		// メモリデバイスコンテキスト
		PAINTSTRUCT	ps;				// クライアント領域の描画に使う情報を保持


		// m_hWndで示す現在のウィンドウのデバイスコンテキストを取得
		// このデバイスコンテキストは描画終了後に ReleaseDCで開放する必要がある．
		hDC = m_Picture1.GetDC()->GetSafeHdc();
//		hDC = ::GetDC(m_hWnd);

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
