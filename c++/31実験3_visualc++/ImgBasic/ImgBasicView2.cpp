// ImgBasicView2.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ImgBasic.h"
#include "ImgBasicView2.h"
#include "ImgBasicDoc.h"

// CImgBasicView2

IMPLEMENT_DYNCREATE(CImgBasicView2, CFormView)

CImgBasicView2::CImgBasicView2()
	: CFormView(CImgBasicView2::IDD)
	, m_WindowsText(_T(""))
{
	m_backColor = RGB(255,255,255);
	m_backBrush.CreateSolidBrush( m_backColor );

	//////////////////////////////////////////////////////////////
	m_hSelectCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hWaitCursor   = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	m_MouseLeftButtonDown = FALSE;
	m_MouseDragRect.SetRect( 100, 10, 100, 100 );
	//////////////////////////////////////////////////////////////
}

CImgBasicView2::~CImgBasicView2()
{
}

void CImgBasicView2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture2, m_Picture2);
	DDX_Text(pDX, IDC_ImgView2_TextBox, m_WindowsText);



}

BEGIN_MESSAGE_MAP(CImgBasicView2, CFormView)
	ON_WM_CTLCOLOR()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CImgBasicView2 診断

#ifdef _DEBUG
void CImgBasicView2::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CImgBasicView2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CImgBasicView2 メッセージ ハンドラー


HBRUSH CImgBasicView2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ここで DC の属性を変更してください。
	pDC->SetBkColor( m_backColor );
	return static_cast<HBRUSH>(m_backBrush.GetSafeHandle());

	// TODO:  既定値を使用したくない場合は別のブラシを返します。
	return hbr;
}


BOOL CImgBasicView2::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	cs.cx = 500;
	cs.cy = 700;

	return CFormView::PreCreateWindow(cs);
}


void CImgBasicView2::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}


void CImgBasicView2::OnDraw(CDC* pDC )
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	CImgBasicDoc* pDoc = (CImgBasicDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	m_WindowsText = pDoc->m_Kind_of_Proc;
	UpdateData( FALSE );

	CImgBmp *p_bmp;
	HDC			hDC;			// デバイスコンテキストのハンドル

	if( !pDoc->m_Bmp1.m_SetFlag ) return;
	p_bmp = &(pDoc->m_Bmp1);

//	if( !pDoc->p_Pgm1 ) return;
//	CImgBmp bmp_temp;
//	bmp_temp.SetPicture( pDoc->p_Pgm1 );
//	p_bmp = &(pDoc->p_Bmp1);
	
		HBITMAP		myDIB;			// ビットマップのハンドル
		HBITMAP		oldDIB;
//		HDC			hDC;			// デバイスコンテキストのハンドル
		HDC			hCompatiDC;		// メモリデバイスコンテキスト
		PAINTSTRUCT	ps;				// クライアント領域の描画に使う情報を保持


		// m_hWndで示す現在のウィンドウのデバイスコンテキストを取得
		// このデバイスコンテキストは描画終了後に ReleaseDCで開放する必要がある．
		hDC = m_Picture2.GetDC()->GetSafeHdc();
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


BOOL CImgBasicView2::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	/////////////////////////////////////////////////////////////////////
	CImgBasicDoc* pDoc = (CImgBasicDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if( pDoc->m_busy == TRUE ) {
		::SetCursor( m_hWaitCursor );
//		AfxMessageBox( "Wait" );
	}  else  {
		SetCursor( m_hSelectCursor );
//		AfxMessageBox( "Normal" );
	}

   return 1;

	/////////////////////////////////////////////////////////////////////
//	return CFormView::OnSetCursor(pWnd, nHitTest, message);
}


void CImgBasicView2::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	/////////////////////////////////////////////////////////////////////
	CImgBasicDoc* pDoc = (CImgBasicDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	CRect rct;
	m_Picture2.GetWindowRect( &rct);
	ScreenToClient( &rct );

//	TRACE( "%d %d %d %d", rct.top, rct.bottom, rct.left, rct.right );
//	TRACE( "   %d %d    ", point.x, point.y );
//	TRACE( "   %d %d\n", point.x - rct.left, point.y - rct.top );
	if( m_MouseLeftButtonDown == TRUE )
	{
		CClientDC dc(this);
		OnPrepareDC( &dc );
		SIZE		size, size2;
		CRect	lpMouseLast;

		lpMouseLast = m_MouseDragRect;
		size.cx = size.cy = 1;
		size2 = size;

		if( point.x - rct.left < 0 ) point.x = rct.left;
		if( point.x - rct.left > 255 ) point.x = rct.left+255;
		m_MouseDragRect.left = point.x;
		m_MouseDragRect.right = point.x+1;
		m_MouseDragRect.top  = rct.top;
		m_MouseDragRect.bottom = rct.top+256;

		dc.DrawDragRect( m_MouseDragRect, size, lpMouseLast, size2 );

		CString mes;
		mes.Format( "階調値 = %d", point.x - rct.left );
		m_WindowsText = pDoc->m_Kind_of_Proc + "  " + mes;
		UpdateData( FALSE );
	}
	/////////////////////////////////////////////////////////////////////

	CFormView::OnMouseMove(nFlags, point);
}


void CImgBasicView2::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	///////////////////////////////////////////////////////////////////////////////////
	CImgBasicDoc* pDoc = (CImgBasicDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	if( pDoc->m_Kind_of_Proc != "ヒストグラム" ) return;

	CRect rct;
	m_Picture2.GetWindowRect( &rct);
	ScreenToClient( &rct );

	CClientDC dc(this);
	OnPrepareDC( &dc );
	SIZE		size, size2;
	CRect	lpMouseLast;

	lpMouseLast = m_MouseDragRect;
	size.cx = size.cy = 1;
	size2 = size;

	if( point.x - rct.left < 0 ) point.x = rct.left;
	if( point.x - rct.left > 255 ) point.x = rct.left+255;

	m_MouseDragRect.left = point.x;
	m_MouseDragRect.right = point.x+1;
	m_MouseDragRect.top  = rct.top;
	m_MouseDragRect.bottom = rct.top+256;


	if( pDoc->m_MouseFirst == TRUE )
	{
		pDoc->m_MouseFirst = FALSE; 
		dc.DrawDragRect( m_MouseDragRect, size, NULL, size2 );
	}
	else
	{
		dc.DrawDragRect( m_MouseDragRect, size, lpMouseLast, size2 );
	}
		m_MouseLeftButtonDown = TRUE;

	CString mes;
	mes.Format( "階調値 = %d", point.x - rct.left );
	m_WindowsText = pDoc->m_Kind_of_Proc + "  " + mes;
	UpdateData( FALSE );
	
	///////////////////////////////////////////////////////////////////////////////////

	CFormView::OnLButtonDown(nFlags, point);
}


void CImgBasicView2::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	m_MouseLeftButtonDown = FALSE;	

	CFormView::OnLButtonUp(nFlags, point);
}


void CImgBasicView2::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint )
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	if( lHint==0 || lHint == 2 ) InvalidateRect( NULL );
	if( lHint==3 ) SetCursor( m_hWaitCursor );

}
