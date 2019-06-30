
// TestDoc.cpp : CTestDoc �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�T���l�C���A����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
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


// CTestDoc �R���X�g���N�V����/�f�X�g���N�V����

CTestDoc::CTestDoc()
{
	// TODO: ���̈ʒu�� 1 �x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B
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

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}




// CTestDoc �V���A����

void CTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �i�[����R�[�h�������ɒǉ����Ă��������B
	}
	else
	{
		// TODO: �ǂݍ��ރR�[�h�������ɒǉ����Ă��������B
	}
}

#ifdef SHARED_HANDLERS

// �T���l�C���̃T�|�[�g
void CTestDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ���̃R�[�h��ύX���ăh�L�������g�̃f�[�^��`�悵�܂�
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

// �����n���h���[�̃T�|�[�g
void CTestDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// �h�L�������g�̃f�[�^���猟���R���e���c��ݒ肵�܂��B 
	// �R���e���c�̊e������ ";" �ŋ�؂�K�v������܂�

	// ��:  strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CTestDoc �f�f

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


// CTestDoc �R�}���h


void CTestDoc::OnMydraw()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	m_DrawFlag = TRUE;
	UpdateAllViews( NULL );
}


void CTestDoc::OnMyerase()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	m_DrawFlag = FALSE;
	UpdateAllViews( NULL );
}


void CTestDoc::OnUpdateMydraw(CCmdUI *pCmdUI)
{	
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
    pCmdUI->Enable(!m_DrawFlag);
}


void CTestDoc::OnUpdateMyerase(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	pCmdUI->Enable(m_DrawFlag);
}


void CTestDoc::OnMychar()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
    m_CharFlag = TRUE;
	UpdateAllViews(NULL);
}
