
// TestView.cpp : CTestView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、サムネイル、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTestView コンストラクション/デストラクション

CTestView::CTestView()
{
	// TODO: 構築コードをここに追加します。

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CTestView 描画

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	if(pDoc->m_DrawFlag == TRUE){
		pDC->MoveTo(100, 100);
		pDC->LineTo(500, 50);
	}
	if(pDoc->m_CharFlag == TRUE){
		pDC->TextOutA( 200, 100, _T("テキストの描画"));
	}

	if(pDoc->m_CharFlag == TRUE){
	CString msg;
	msg.Format( _T("m_Number = %d "), pDoc->m_Number );

	CFont *oldFont, newFont;
	newFont.CreatePointFont( 360, _T("MS　ゴシック") );
	oldFont = pDC->SelectObject( &newFont );

	pDC->TextOutA( 200, 100, msg );

	pDC->SelectObject( oldFont );
	newFont.DeleteObject();
	}

	if(pDoc->m_CharFlag == TRUE){
	CString msg;
	msg.Format( _T("m_Num2 = %lf "), pDoc->m_Num2 );

	CFont *oldFont, newFont;
	newFont.CreatePointFont( 360, _T("MS　ゴシック") );
	oldFont = pDC->SelectObject( &newFont );

	pDC->TextOutA( 200, 100, msg );

	pDC->SelectObject( oldFont );
	newFont.DeleteObject();
	}
}


// CTestView 印刷


void CTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

void CTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestView 診断

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView メッセージ ハンドラー
