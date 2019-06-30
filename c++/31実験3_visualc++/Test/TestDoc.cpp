
// TestDoc.cpp : CTestDoc クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、サムネイル、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTestDoc

IMPLEMENT_DYNCREATE(CTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestDoc, CDocument)
	ON_COMMAND(ID_MyDraw, &CTestDoc::OnMydraw)
	ON_COMMAND(ID_MyErase, &CTestDoc::OnMyerase)
	ON_UPDATE_COMMAND_UI(ID_MyDraw, &CTestDoc::OnUpdateMydraw)
	ON_UPDATE_COMMAND_UI(ID_MyErase, &CTestDoc::OnUpdateMyerase)
	ON_COMMAND(ID_MyChar, &CTestDoc::OnMychar)
END_MESSAGE_MAP()


// CTestDoc コンストラクション/デストラクション

CTestDoc::CTestDoc()
{
	// TODO: この位置に 1 度だけ呼ばれる構築用のコードを追加してください。
	m_DrawFlag = FALSE;
	m_CharFlag = FALSE;
	m_Number = 123;
	m_Num2 = 1.23456789;
}

CTestDoc::~CTestDoc()
{
}

BOOL CTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}




// CTestDoc シリアル化

void CTestDoc::Serialize(CArchive& ar)
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
void CTestDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CTestDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ドキュメントのデータから検索コンテンツを設定します。 
	// コンテンツの各部分は ";" で区切る必要があります

	// 例:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CTestDoc::SetSearchContent(const CString& value)
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

// CTestDoc 診断

#ifdef _DEBUG
void CTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTestDoc コマンド


void CTestDoc::OnMydraw()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_DrawFlag = TRUE;
	UpdateAllViews( NULL );
}


void CTestDoc::OnMyerase()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_DrawFlag = FALSE;
	UpdateAllViews( NULL );
}


void CTestDoc::OnUpdateMydraw(CCmdUI *pCmdUI)
{	
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
    pCmdUI->Enable(!m_DrawFlag);
}


void CTestDoc::OnUpdateMyerase(CCmdUI *pCmdUI)
{
	// TODO: ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(m_DrawFlag);
}


void CTestDoc::OnMychar()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
    m_CharFlag = TRUE;
	UpdateAllViews(NULL);
}
