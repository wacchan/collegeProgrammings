
// ImgBasicView.cpp : CImgBasicView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�T���l�C���A����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
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

// CImgBasicView �R���X�g���N�V����/�f�X�g���N�V����

CImgBasicView::CImgBasicView()
	: CFormView(CImgBasicView::IDD)
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B
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
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B
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


// CImgBasicView �f�f

#ifdef _DEBUG
void CImgBasicView::AssertValid() const
{
	CFormView::AssertValid();
}

void CImgBasicView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CImgBasicDoc* CImgBasicView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgBasicDoc)));
	return (CImgBasicDoc*)m_pDocument;
}
#endif //_DEBUG


// CImgBasicView ���b�Z�[�W �n���h���[


HBRUSH CImgBasicView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ������ DC �̑�����ύX���Ă��������B
	pDC->SetBkColor( m_backColor );
	return static_cast<HBRUSH>(m_backBrush.GetSafeHandle());

	// TODO:  ����l���g�p�������Ȃ��ꍇ�͕ʂ̃u���V��Ԃ��܂��B
	return hbr;
}


void CImgBasicView::OnDraw(CDC* pDC )
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CImgBasicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CImgBmp *p_bmp;
	HDC			hDC;			// �f�o�C�X�R���e�L�X�g�̃n���h��

	if( !pDoc->m_Bmp0.m_SetFlag ) return;
	p_bmp = &(pDoc->m_Bmp0);

//	if( !pDoc->p_Pgm0 ) return;

//	CImgBmp bmp_temp;
//	bmp_temp.SetPicture( pDoc->p_Pgm0 );
//	p_bmp = &bmp_temp;
//	p_bmp = pDoc->p_Bmp0;
	
		HBITMAP		myDIB;			// �r�b�g�}�b�v�̃n���h��
		HBITMAP		oldDIB;
//		HDC			hDC;			// �f�o�C�X�R���e�L�X�g�̃n���h��
		HDC			hCompatiDC;		// �������f�o�C�X�R���e�L�X�g
		PAINTSTRUCT	ps;				// �N���C�A���g�̈�̕`��Ɏg������ێ�


		// m_hWnd�Ŏ������݂̃E�B���h�E�̃f�o�C�X�R���e�L�X�g���擾
		// ���̃f�o�C�X�R���e�L�X�g�͕`��I����� ReleaseDC�ŊJ������K�v������D
		hDC = m_Picture1.GetDC()->GetSafeHdc();
//		hDC = ::GetDC(m_hWnd);

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
