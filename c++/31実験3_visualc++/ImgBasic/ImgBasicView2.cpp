// ImgBasicView2.cpp : �����t�@�C��
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


// CImgBasicView2 �f�f

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


// CImgBasicView2 ���b�Z�[�W �n���h���[


HBRUSH CImgBasicView2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ������ DC �̑�����ύX���Ă��������B
	pDC->SetBkColor( m_backColor );
	return static_cast<HBRUSH>(m_backBrush.GetSafeHandle());

	// TODO:  ����l���g�p�������Ȃ��ꍇ�͕ʂ̃u���V��Ԃ��܂��B
	return hbr;
}


BOOL CImgBasicView2::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	cs.cx = 500;
	cs.cy = 700;

	return CFormView::PreCreateWindow(cs);
}


void CImgBasicView2::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}


void CImgBasicView2::OnDraw(CDC* pDC )
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B

	CImgBasicDoc* pDoc = (CImgBasicDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	m_WindowsText = pDoc->m_Kind_of_Proc;
	UpdateData( FALSE );

	CImgBmp *p_bmp;
	HDC			hDC;			// �f�o�C�X�R���e�L�X�g�̃n���h��

	if( !pDoc->m_Bmp1.m_SetFlag ) return;
	p_bmp = &(pDoc->m_Bmp1);

//	if( !pDoc->p_Pgm1 ) return;
//	CImgBmp bmp_temp;
//	bmp_temp.SetPicture( pDoc->p_Pgm1 );
//	p_bmp = &(pDoc->p_Bmp1);
	
		HBITMAP		myDIB;			// �r�b�g�}�b�v�̃n���h��
		HBITMAP		oldDIB;
//		HDC			hDC;			// �f�o�C�X�R���e�L�X�g�̃n���h��
		HDC			hCompatiDC;		// �������f�o�C�X�R���e�L�X�g
		PAINTSTRUCT	ps;				// �N���C�A���g�̈�̕`��Ɏg������ێ�


		// m_hWnd�Ŏ������݂̃E�B���h�E�̃f�o�C�X�R���e�L�X�g���擾
		// ���̃f�o�C�X�R���e�L�X�g�͕`��I����� ReleaseDC�ŊJ������K�v������D
		hDC = m_Picture2.GetDC()->GetSafeHdc();
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


BOOL CImgBasicView2::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	/////////////////////////////////////////////////////////////////////
	CImgBasicDoc* pDoc = (CImgBasicDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
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
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
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
		mes.Format( "�K���l = %d", point.x - rct.left );
		m_WindowsText = pDoc->m_Kind_of_Proc + "  " + mes;
		UpdateData( FALSE );
	}
	/////////////////////////////////////////////////////////////////////

	CFormView::OnMouseMove(nFlags, point);
}


void CImgBasicView2::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	///////////////////////////////////////////////////////////////////////////////////
	CImgBasicDoc* pDoc = (CImgBasicDoc *)GetDocument();
	ASSERT_VALID(pDoc);

	if( pDoc->m_Kind_of_Proc != "�q�X�g�O����" ) return;

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
	mes.Format( "�K���l = %d", point.x - rct.left );
	m_WindowsText = pDoc->m_Kind_of_Proc + "  " + mes;
	UpdateData( FALSE );
	
	///////////////////////////////////////////////////////////////////////////////////

	CFormView::OnLButtonDown(nFlags, point);
}


void CImgBasicView2::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	m_MouseLeftButtonDown = FALSE;	

	CFormView::OnLButtonUp(nFlags, point);
}


void CImgBasicView2::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint )
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	if( lHint==0 || lHint == 2 ) InvalidateRect( NULL );
	if( lHint==3 ) SetCursor( m_hWaitCursor );

}
