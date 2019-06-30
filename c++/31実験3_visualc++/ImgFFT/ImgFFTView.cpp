
// ImgFFTView.cpp : CImgFFTView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�T���l�C���A����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
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

// CImgFFTView �R���X�g���N�V����/�f�X�g���N�V����

CImgFFTView::CImgFFTView()
	: CFormView(CImgFFTView::IDD)
	, m_gainEdit(0)
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B
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
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

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


// CImgFFTView �f�f

#ifdef _DEBUG
void CImgFFTView::AssertValid() const
{
	CFormView::AssertValid();
}

void CImgFFTView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CImgFFTDoc* CImgFFTView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgFFTDoc)));
	return (CImgFFTDoc*)m_pDocument;
}
#endif //_DEBUG


// CImgFFTView ���b�Z�[�W �n���h���[


void CImgFFTView::OnDraw(CDC* pDC )
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CImgFFTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CImgBmp *p_bmp;
	HDC			hDC;			// �f�o�C�X�R���e�L�X�g�̃n���h��

	if( !pDoc->m_Bmp0.m_SetFlag ) return;
	p_bmp = &(pDoc->m_Bmp0);

	// m_hWnd�Ŏ������݂̃E�B���h�E�̃f�o�C�X�R���e�L�X�g���擾
	// ���̃f�o�C�X�R���e�L�X�g�͕`��I����� ReleaseDC�ŊJ������K�v������D
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
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������

		HBITMAP		myDIB;			// �r�b�g�}�b�v�̃n���h��
		HBITMAP		oldDIB;
//		HDC			hDC;			// �f�o�C�X�R���e�L�X�g�̃n���h��
		HDC			hCompatiDC;		// �������f�o�C�X�R���e�L�X�g
		PAINTSTRUCT	ps;				// �N���C�A���g�̈�̕`��Ɏg������ێ�


		// m_hWnd�Ŏ������݂̃E�B���h�E�̃f�o�C�X�R���e�L�X�g���擾
		// ���̃f�o�C�X�R���e�L�X�g�͕`��I����� ReleaseDC�ŊJ������K�v������D
//		hDC = m_picture.GetDC()->GetSafeHdc();

		// �`��̏���������
		// �`�悪�I��������K�� EndPaint�����s����K�v������D
		::BeginPaint( m_hWnd, &ps );

		// hDC�ƌ݊����̂��郁�����f�o�C�X�R���e�L�X�g���쐬����D
		hCompatiDC = ::CreateCompatibleDC( hDC );

		// DIB�`�����r�b�g�}�b�v���� DDB�i�f�o�C�X�ˑ��j�`���r�b�g�}�b�v���쐬����D
//		myDIB = ::CreateDIBitmap( hDC, &p_bmp->pbmi->bmiHeader,
//			CBM_INIT, m_BmpImage, m_BmpInfo, DIB_RGB_COLORS );
		myDIB = ::CreateDIBitmap( hDC, &p_bmp->pbmi->bmiHeader, 
			CBM_INIT,
			p_bmp->pbits, p_bmp->pbmi, DIB_RGB_COLORS);

		// hCompatiDC�� myDIB�̎����I�u�W�F�N�g���g�p�ł���悤�ɂ���D
		// �I���W�i���r�b�g�}�b�v�� oldDIB�ɕۑ����Ă����C��ŕ���������D
		oldDIB = (HBITMAP)::SelectObject( hCompatiDC, myDIB );

		// hCompatiDC�ɂ���摜��hDC�ɕ\������D
	//	BitBlt( hDC, 0, 0, m_BmpInfo->bmiHeader.biWidth,
	//		m_BmpInfo->bmiHeader.biHeight, hCompatiDC, 0, 0, SRCCOPY );

		BitBlt( hDC, 0, 0, p_bmp->pbmi->bmiHeader.biWidth,
			p_bmp->pbmi->bmiHeader.biHeight, hCompatiDC,
			0, 0, SRCCOPY );

//		StretchBlt( hDC, 0, 0, m_width, m_height, hCompatiDC, 0, 0, 
//		p_bmp->pbmi->bmiHeader.biWidth,
//		p_bmp->pbmi->bmiHeader.biHeight,
//		SRCCOPY );

		// BeginPaint�Ή�����
		::EndPaint( m_hWnd, &ps );

		// �I�u�W�F�N�g�̉���Ȃ�
		::SelectObject( hCompatiDC, oldDIB );
		::DeleteObject( myDIB );
		::DeleteObject( hCompatiDC );
//		::ReleaseDC( m_hWnd, hDC );

		// -------------------------------------�@�����܂Œǉ�

}



void CImgFFTView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
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

//  SB_BOTTOM   ��ԉ��܂ŃX�N���[���B
//  SB_ENDSCROLL   �X�N���[���I���B
//  SB_LINEDOWN   1 �s���փX�N���[���B
//  SB_LINEUP   1 �s��փX�N���[���B
//  SB_PAGEDOWN   1 �y�[�W���փX�N���[���B
//  SB_PAGEUP   1 �y�[�W��փX�N���[���B
//  SB_THUMBPOSITION   ��Έʒu�փX�N���[���B���݈ʒu�� nPos �Œ񋟁B
//  SB_THUMBTRACK   �w��ʒu�փX�N���[�� �{�b�N�X���h���b�O�B���݈ʒu�� nPos �Œ񋟁B
//  SB_TOP   ��ԏ�܂ŃX�N���[���B 

	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CImgFFTView::OnBnClickedImgGainReset()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B	CImgFFTDoc* pDoc = GetDocument();
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
