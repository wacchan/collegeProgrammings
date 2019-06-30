
// ImgBasicDoc.cpp : CImgBasicDoc �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�T���l�C���A����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "ImgBasic.h"
#endif

#include "ImgBasicDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImgBasicDoc

IMPLEMENT_DYNCREATE(CImgBasicDoc, CDocument)

BEGIN_MESSAGE_MAP(CImgBasicDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CImgBasicDoc::OnFileOpen)
	ON_COMMAND(ID_ImgReverse, &CImgBasicDoc::OnImgReverse)
	ON_UPDATE_COMMAND_UI(ID_ImgReverse, &CImgBasicDoc::OnUpdateImgReverse)
	/////////////////////////////////////////////////////////////////////////////////////////
	ON_COMMAND(ID_ImgHistMake, &CImgBasicDoc::OnImgHistMake)
	ON_UPDATE_COMMAND_UI(ID_ImgHistMake, &CImgBasicDoc::OnUpdateImgHistMake)
	ON_COMMAND(ID_ImgHistBin, &CImgBasicDoc::OnImgHistBin)
	ON_UPDATE_COMMAND_UI(ID_ImgHistBin, &CImgBasicDoc::OnUpdateImgHistBin)
	ON_COMMAND(ID_ImgHistLinearT, &CImgBasicDoc::OnImgHistLinearT)
	ON_UPDATE_COMMAND_UI(ID_ImgHistLinearT, &CImgBasicDoc::OnUpdateImgHistLinearT)
	ON_COMMAND(ID_ImgHistEquiv, &CImgBasicDoc::OnImgHistEquiv)
	ON_UPDATE_COMMAND_UI(ID_ImgHistEquiv, &CImgBasicDoc::OnUpdateImgHistEquiv)
	/////////////////////////////////////////////////////////////////////////////////////////
	ON_COMMAND(ID_ImgFilterMask_smooth, &CImgBasicDoc::OnImgFilterMaskSmooth)
	ON_UPDATE_COMMAND_UI(ID_ImgFilterMask_smooth, &CImgBasicDoc::OnUpdateImgFilterMaskSmooth)
	ON_COMMAND(ID_ImgFilterMask_Laplace, &CImgBasicDoc::OnImgFilterMaskLaplace)
	ON_UPDATE_COMMAND_UI(ID_ImgFilterMask_Laplace, &CImgBasicDoc::OnUpdateImgFilterMaskLaplace)
	ON_COMMAND(ID_ImgFilterMask1, &CImgBasicDoc::OnImgFilterMask1)
	ON_UPDATE_COMMAND_UI(ID_ImgFilterMask1, &CImgBasicDoc::OnUpdateImgFilterMask1)
	ON_COMMAND(ID_ImgFilterMask2, &CImgBasicDoc::OnImgFilterMask2)
	ON_UPDATE_COMMAND_UI(ID_ImgFilterMask2, &CImgBasicDoc::OnUpdateImgFilterMask2)
	ON_COMMAND(ID_ImgFilterMask3, &CImgBasicDoc::OnImgFilterMask3)
	ON_UPDATE_COMMAND_UI(ID_ImgFilterMask3, &CImgBasicDoc::OnUpdateImgFilterMask3)
	ON_COMMAND(ID_ImgFilterMedian, &CImgBasicDoc::OnImgFilterMedian)
	ON_UPDATE_COMMAND_UI(ID_ImgFilterMedian, &CImgBasicDoc::OnUpdateImgFilterMedian)
	ON_COMMAND(ID_ImgFilterWhiteGause, &CImgBasicDoc::OnImgFilterWhiteGause)
	ON_UPDATE_COMMAND_UI(ID_ImgFilterWhiteGause, &CImgBasicDoc::OnUpdateImgFilterWhiteGause)
	ON_COMMAND(ID_ImgFilterWhiteImpulse, &CImgBasicDoc::OnImgFilterWhiteImpulse)
	ON_UPDATE_COMMAND_UI(ID_ImgFilterWhiteImpulse, &CImgBasicDoc::OnUpdateImgFilterWhiteImpulse)
	/////////////////////////////////////////////////////////////////////////////////////////
	ON_COMMAND(ID_Img1to0, &CImgBasicDoc::OnImg1to0)
	ON_UPDATE_COMMAND_UI(ID_Img1to0, &CImgBasicDoc::OnUpdateImg1to0)
	ON_COMMAND(ID_ImgBackup0, &CImgBasicDoc::OnImgBackup0)
	ON_UPDATE_COMMAND_UI(ID_ImgBackup0, &CImgBasicDoc::OnUpdateImgBackup0)
	ON_COMMAND(ID_ImgBackup1, &CImgBasicDoc::OnImgBackup1)
	ON_UPDATE_COMMAND_UI(ID_ImgBackup1, &CImgBasicDoc::OnUpdateImgBackup1)
	/////////////////////////////////////////////////////////////////////////////////////////
	ON_COMMAND(ID_ImgThinning, &CImgBasicDoc::OnImgThinning)
	ON_UPDATE_COMMAND_UI(ID_ImgThinning, &CImgBasicDoc::OnUpdateImgThinning)
	ON_COMMAND(ID_ImgZeroCross, &CImgBasicDoc::OnImgZeroCross)
	ON_UPDATE_COMMAND_UI(ID_ImgZeroCross, &CImgBasicDoc::OnUpdateImgZeroCross)
	/////////////////////////////////////////////////////////////////////////////////////////
	ON_COMMAND(ID_ImgFILE_Save0, &CImgBasicDoc::OnImgFileSave0)
	ON_UPDATE_COMMAND_UI(ID_ImgFILE_Save0, &CImgBasicDoc::OnUpdateImgFileSave0)
	ON_COMMAND(ID_ImgFILE_Save1, &CImgBasicDoc::OnImgFileSave1)
	ON_UPDATE_COMMAND_UI(ID_ImgFILE_Save1, &CImgBasicDoc::OnUpdateImgFileSave1)
END_MESSAGE_MAP()


// CImgBasicDoc �R���X�g���N�V����/�f�X�g���N�V����

CImgBasicDoc::CImgBasicDoc()
{
	// TODO: ���̈ʒu�� 1 �x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B
	p_Pgm0 = NULL;
	p_Pgm1 = NULL;
	p_Pgm2 = NULL;
	p_Pgm0_temp = NULL;
	p_Pgm1_temp = NULL;
	m_Kind_of_Proc = "";
	m_Kind_of_Proc_temp = "";
	m_busy = FALSE;
	m_MouseFirst = TRUE;

}

CImgBasicDoc::~CImgBasicDoc()
{
	if( p_Pgm0 != NULL ) delete p_Pgm0;
	if( p_Pgm1 != NULL ) delete p_Pgm1;
	if( p_Pgm2 != NULL ) delete p_Pgm2;
	if( p_Pgm0_temp != NULL ) delete p_Pgm0_temp;
	if( p_Pgm1_temp != NULL ) delete p_Pgm1_temp;

	m_Bmp0.ClearPicture();
	m_Bmp1.ClearPicture();
	m_Bmp2.ClearPicture();

}

BOOL CImgBasicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}




// CImgBasicDoc �V���A����

void CImgBasicDoc::Serialize(CArchive& ar)
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
void CImgBasicDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImgBasicDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// �h�L�������g�̃f�[�^���猟���R���e���c��ݒ肵�܂��B 
	// �R���e���c�̊e������ ";" �ŋ�؂�K�v������܂�

	// ��:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImgBasicDoc::SetSearchContent(const CString& value)
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

// CImgBasicDoc �f�f

#ifdef _DEBUG
void CImgBasicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImgBasicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImgBasicDoc �R�}���h


void CImgBasicDoc::OnFileOpen()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL )  {
		delete p_Pgm0;
		if( p_Pgm1      != NULL ) { delete p_Pgm1; 	    p_Pgm1 = NULL;}
		if( p_Pgm1_temp != NULL ) { delete p_Pgm1_temp; p_Pgm1_temp = NULL;}
	}
	p_Pgm0 = new CImgPgm;

	if( p_Pgm0->LoadFile( &m_OpenFileName, &(CImgBasicApp::m_InputDir) )==FALSE ) {
		p_Pgm0 = NULL;
		if( p_Pgm1      != NULL ) { delete p_Pgm1; 	    p_Pgm1 = NULL;}
		if( p_Pgm1_temp != NULL ) { delete p_Pgm1_temp; p_Pgm1_temp = NULL;}
		m_Bmp0.ClearPicture();
	} else {
		m_Bmp0.SetPicture( p_Pgm0 );
	}

	m_Bmp1.ClearPicture();
	m_Kind_of_Proc = "";
	m_Kind_of_Proc_temp = "";
	m_MouseFirst = TRUE;

	UpdateAllViews( NULL );	
}



void CImgBasicDoc::Check_Backup_Pgm0() 
{
	if( p_Pgm0 != NULL )  {
		if( p_Pgm0_temp != NULL ) delete p_Pgm0_temp;
		p_Pgm0_temp = new CImgPgm;
		p_Pgm0_temp->CopyImage( p_Pgm0 );
		delete p_Pgm0;
	}
	p_Pgm0 = new CImgPgm;
}

void CImgBasicDoc::Check_Backup_Pgm1() 
{
	if( p_Pgm1 != NULL )  {
		if( p_Pgm1_temp != NULL ) delete p_Pgm1_temp;
		p_Pgm1_temp = new CImgPgm;
		p_Pgm1_temp->CopyImage( p_Pgm1 );
		delete p_Pgm1;
		m_Kind_of_Proc_temp = m_Kind_of_Proc;
	}
	p_Pgm1 = new CImgPgm;
}


void CImgBasicDoc::OnImgReverse()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();

	p_Pgm1->CopyImage( p_Pgm0 );
	p_Pgm1->ImgReverse();
	m_Bmp1.SetPicture( p_Pgm1 );

	m_Kind_of_Proc = "���]����";
	UpdateAllViews( NULL, 2 );	

}



void CImgBasicDoc::OnUpdateImgReverse(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
		else			{	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgHistMake()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();

	int gray;
	gray = p_Pgm0->m_max_gray;
	p_Pgm1->Create( 256, 256, gray );
	make_histogram( p_Pgm0, p_Pgm1 );

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = "�q�X�g�O����";
	m_MouseFirst = TRUE;

	UpdateAllViews( NULL, 2 );	

}


void CImgBasicDoc::OnUpdateImgHistMake(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgHistBin()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	int dd, count[2];

	dd = (int)GetNum( "臒l����͂��Ă��������D(0-255)" );

	Check_Backup_Pgm1();
	p_Pgm1->CopyImage( p_Pgm0 );

	p_Pgm1->ImgBin( dd, count );
	m_Bmp1.SetPicture( p_Pgm1 );

	CString mes;
	mes.Format( "     �� = %d   �� = %d", count[1], count[0] );
	m_Kind_of_Proc = "�Q�l������" + mes;
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgHistBin(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgHistLinearT()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();

	p_Pgm1->CopyImage( p_Pgm0 );
	p_Pgm1->HistLinearTrans();
	m_Bmp1.SetPicture( p_Pgm1 );

	m_Kind_of_Proc = "�q�X�g�O�������`�ϊ�";
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgHistLinearT(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgHistEquiv()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();

	p_Pgm1->CopyImage( p_Pgm0 );
	p_Pgm1->HistEquivTrans();
	m_Bmp1.SetPicture( p_Pgm1 );

	m_Kind_of_Proc = "�q�X�g�O���������ϊ�";
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgHistEquiv(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgFilterMaskSmooth()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();	p_Pgm1->CopyImage( p_Pgm0 );

	SFilter w;
	SetFilterSmooth( &w );
	p_Pgm1->spacial_filtering( w );

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = "�����t�B���^";

	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgFilterMaskSmooth(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
		else			{	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgFilterMaskLaplace()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();	p_Pgm1->CopyImage( p_Pgm0 );

	SFilter w;
	SetFilterLaplace( &w );
	p_Pgm1->spacial_filtering( w );

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = "�W�ߖT���v���V�A��";
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgFilterMaskLaplace(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
		else			{	pCmdUI->Enable( FALSE );}
}


///////////////////////////////////////////////////////////////////////////
//�@�@���K�p
///////////////////////////////////////////////////////////////////////////

void CImgBasicDoc::OnImgFilterMask1()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();	p_Pgm1->CopyImage( p_Pgm0 );

	SFilter w;
	SetFilterUser1( &w );
	p_Pgm1->spacial_filtering( w );

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = "�}�X�N�P";
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgFilterMask1(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
		else			{	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgFilterMask2()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();	p_Pgm1->CopyImage( p_Pgm0 );

	SFilter w;
	SetFilterUser2( &w );
	p_Pgm1->spacial_filtering( w );

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = "�}�X�N�Q";
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgFilterMask2(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
		else			{	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgFilterMask3()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();	p_Pgm1->CopyImage( p_Pgm0 );

	SFilter w;
	SetFilterUser3( &w );
	p_Pgm1->spacial_filtering( w );

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = "�}�X�N�R";
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgFilterMask3(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
		else			{	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgFilterMedian()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();	p_Pgm1->CopyImage( p_Pgm0 );

	p_Pgm1->spacial_median_filtering(  );

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = "���f�B�A���t�B���^";
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgFilterMedian(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
		else			{	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgFilterWhiteGause()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	double mean, var;

	Check_Backup_Pgm1();	p_Pgm1->CopyImage( p_Pgm0 );

	GetNum2( "���F�K�E�X�m�C�Y�p�����[�^����", "����", "�W���΍�", &mean, &var );
	p_Pgm1->AddNoiseGaussian( mean,  var );

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = "���F�K�E�X�m�C�Y�t��";
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgFilterWhiteGause(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
		else			{	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgFilterWhiteImpulse()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();	p_Pgm1->CopyImage( p_Pgm0 );

	double dd;

	dd = GetNum( "臒l����͂��Ă��������D(0.0-1.0)" );
	p_Pgm1->AddNoiseImpulse( dd );

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = "���F�C���p���X�t��";
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgFilterWhiteImpulse(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
		else			{	pCmdUI->Enable( FALSE );}
}


//////////////////////////////////////////////////////////////
//�@�@�摜�P���摜�O�֓]��
//////////////////////////////////////////////////////////////
void CImgBasicDoc::OnImg1to0()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm0();
	p_Pgm0->CopyImage( p_Pgm1 );
	m_Bmp0.SetPicture( p_Pgm0 );

	UpdateAllViews( NULL, 1 );	
}


void CImgBasicDoc::OnUpdateImg1to0(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm1 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


//////////////////////////////////////////////////////////////
//�@�@�摜�O�����ɖ߂�
//////////////////////////////////////////////////////////////
void CImgBasicDoc::OnImgBackup0()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	delete p_Pgm0;
	p_Pgm0 = new CImgPgm;
	p_Pgm0->CopyImage( p_Pgm0_temp );
	delete p_Pgm0_temp;
	p_Pgm0_temp = NULL;

	m_Bmp0.SetPicture( p_Pgm0 );

	UpdateAllViews( NULL, 1 );	
}


void CImgBasicDoc::OnUpdateImgBackup0(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0_temp != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


//////////////////////////////////////////////////////////////
//�@�@�摜�P�����ɖ߂�
//////////////////////////////////////////////////////////////
void CImgBasicDoc::OnImgBackup1()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	delete p_Pgm1;
	p_Pgm1 = new CImgPgm;
	p_Pgm1->CopyImage( p_Pgm1_temp );
	delete p_Pgm1_temp;
	p_Pgm1_temp = NULL;

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = m_Kind_of_Proc_temp;
	m_Kind_of_Proc_temp = "";

	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgBackup1(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm1_temp != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgThinning()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	m_busy = TRUE;
	UpdateAllViews( NULL, 3 );	
	Check_Backup_Pgm1();

	int gray;
	gray = p_Pgm0->m_max_gray;
	p_Pgm1->Create( p_Pgm0->m_xsize, p_Pgm0->m_ysize, gray );
	thinning( p_Pgm0, p_Pgm1 );
	m_busy = FALSE;

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = "�א���";
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgThinning(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgZeroCross()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Check_Backup_Pgm1();	p_Pgm1->CopyImage( p_Pgm0 );

	p_Pgm1->ZeroCross( 128 );

	m_Bmp1.SetPicture( p_Pgm1 );
	m_Kind_of_Proc = "�[���N���X";
	UpdateAllViews( NULL, 2 );	
}


void CImgBasicDoc::OnUpdateImgZeroCross(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgFileSave0()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
CString fname;
int		kind;

	kind = OutputFileSelect( &fname, &(CImgBasicApp::m_OutputDir), 0 );
	switch( kind ) {
	case 1: p_Pgm0->SaveFile( fname );
		break;
	case 2: m_Bmp0.SaveFile( fname );
		break;
	default:
		break;
	}
}


void CImgBasicDoc::OnUpdateImgFileSave0(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm0 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}


void CImgBasicDoc::OnImgFileSave1()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
CString fname;
int		kind;

	kind = OutputFileSelect( &fname, &(CImgBasicApp::m_OutputDir), 0 );
	switch( kind ) {
	case 1: p_Pgm1->SaveFile( fname );
		break;
	case 2: m_Bmp1.SaveFile( fname );
		break;
	default:
		break;
	}
}


void CImgBasicDoc::OnUpdateImgFileSave1(CCmdUI *pCmdUI)
{
	// TODO: �����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if( p_Pgm1 != NULL ) {	pCmdUI->Enable( TRUE ); }
	 else				 {	pCmdUI->Enable( FALSE );}
}
