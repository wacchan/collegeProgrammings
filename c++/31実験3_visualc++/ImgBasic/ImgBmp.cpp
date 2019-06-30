#include "StdAfx.h"
#include "ImgBmp.h"

#include "ImgBasic.h"
#include <math.h>


CImgBmp::CImgBmp(void)
{
	pbmi  = NULL;
	pbits = NULL;
	m_SetFlag = FALSE;
}

CImgBmp::~CImgBmp(void)
{
	if( pbmi  != NULL ) delete[] (BYTE*)pbmi;
	if( pbits != NULL ) delete[] (unsigned char*)pbits;
}

void CImgBmp::SetPicture(CImgPgm *pgm)
{
//　ビットマップインフォ作成
	if( pbmi != NULL )  delete[] (BYTE*)pbmi;
	pbmi = (BITMAPINFO*) new BYTE[ sizeof(BITMAPINFOHEADER) ];
	ZeroMemory( &pbmi->bmiHeader, sizeof(pbmi->bmiHeader) );

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = pgm->m_xsize;
	pbmi->bmiHeader.biHeight = pgm->m_ysize;
	pbmi->bmiHeader.biBitCount = 24;
	pbmi->bmiHeader.biPlanes   = 1;
	pbmi->bmiHeader.biSizeImage = 
		((( pgm->m_xsize*24 + 31 ) >>3 ) & 0xfffffffc ) * pgm->m_ysize;
	//////////////////////////////////////////
	pbmi->bmiHeader.biClrImportant = 0;
	pbmi->bmiHeader.biClrUsed = 0;
	pbmi->bmiHeader.biCompression = 0;
	pbmi->bmiHeader.biXPelsPerMeter = 2000; // ?
	pbmi->bmiHeader.biYPelsPerMeter = 2000; // ?

//　ビットマップファイルヘッダ作成
	bmfh.bfType = 'B' + ('M'<<8);
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)*sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + pbmi->bmiHeader.biSizeImage;

	int w = ((pgm->m_xsize*24+31)>>3) & 0xfffffffc;
	if( pbits != NULL ) delete[] pbits;
	pbits = new unsigned char[w * pgm->m_ysize];

	unsigned char *p;
	unsigned char **im;
	im = pgm->image;
	int xs, ys;
	xs = pgm->m_xsize;
	ys = pgm->m_ysize;
	for( int y=0; y<ys; y++ ) {
		p = pbits + w*y;
		for( int x=0; x<xs; x++ ) {
			*(p++) = im[ys-1-y][x];
			*(p++) = im[ys-1-y][x];
			*(p++) = im[ys-1-y][x];
		}
	}

	m_xsize = xs;
	m_ysize = ys;
	m_pbits_wide = w;

	m_SetFlag = TRUE;
}

void CImgBmp::SetPicture_g(CImgPgm *pgm, float gain )
{
//　ビットマップインフォ作成
	if( pbmi != NULL )  delete[] (BYTE*)pbmi;
	pbmi = (BITMAPINFO*) new BYTE[ sizeof(BITMAPINFOHEADER) ];
	ZeroMemory( &pbmi->bmiHeader, sizeof(pbmi->bmiHeader) );

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = pgm->m_xsize;
	pbmi->bmiHeader.biHeight = pgm->m_ysize;
	pbmi->bmiHeader.biBitCount = 24;
	pbmi->bmiHeader.biPlanes   = 1;
	pbmi->bmiHeader.biSizeImage = 
		((( pgm->m_xsize*24 + 31 ) >>3 ) & 0xfffffffc ) * pgm->m_ysize;
	//////////////////////////////////////////
	pbmi->bmiHeader.biClrImportant = 0;
	pbmi->bmiHeader.biClrUsed = 0;
	pbmi->bmiHeader.biCompression = 0;
	pbmi->bmiHeader.biXPelsPerMeter = 2000; // ?
	pbmi->bmiHeader.biYPelsPerMeter = 2000; // ?

//　ビットマップファイルヘッダ作成
	bmfh.bfType = 'B' + ('M'<<8);
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)*sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + pbmi->bmiHeader.biSizeImage;

	int w = ((pgm->m_xsize*24+31)>>3) & 0xfffffffc;
	if( pbits != NULL ) delete[] pbits;
	pbits = new unsigned char[w * pgm->m_ysize];

	unsigned char *p;
	unsigned char **im;
	im = pgm->image;
	int xs, ys, z;
	xs = pgm->m_xsize;
	ys = pgm->m_ysize;
	for( int y=0; y<ys; y++ ) {
		p = pbits + w*y;
		for( int x=0; x<xs; x++ ) {
			z = (unsigned int)(im[ys-1-y][x]*gain);	if( z > 255 ) z = 255;
			*(p++) = z;
			*(p++) = z;
			*(p++) = z;
		}
	}

	m_xsize = xs;
	m_ysize = ys;
	m_pbits_wide = w;

	m_SetFlag = TRUE;
}

void CImgBmp::SetPicture_2(CImgPgm *pgm, CImgPgm *pgm2 )
{
//　ビットマップインフォ作成
	if( pbmi != NULL )  delete[] (BYTE*)pbmi;
	pbmi = (BITMAPINFO*) new BYTE[ sizeof(BITMAPINFOHEADER) ];
	ZeroMemory( &pbmi->bmiHeader, sizeof(pbmi->bmiHeader) );

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = pgm->m_xsize;
	pbmi->bmiHeader.biHeight = pgm->m_ysize;
	pbmi->bmiHeader.biBitCount = 24;
	pbmi->bmiHeader.biPlanes   = 1;
	pbmi->bmiHeader.biSizeImage = 
		((( pgm->m_xsize*24 + 31 ) >>3 ) & 0xfffffffc ) * pgm->m_ysize;
	//////////////////////////////////////////
	pbmi->bmiHeader.biClrImportant = 0;
	pbmi->bmiHeader.biClrUsed = 0;
	pbmi->bmiHeader.biCompression = 0;
	pbmi->bmiHeader.biXPelsPerMeter = 2000; // ?
	pbmi->bmiHeader.biYPelsPerMeter = 2000; // ?

//　ビットマップファイルヘッダ作成
	bmfh.bfType = 'B' + ('M'<<8);
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)*sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + pbmi->bmiHeader.biSizeImage;

	int w = ((pgm->m_xsize*24+31)>>3) & 0xfffffffc;
	if( pbits != NULL ) delete[] pbits;
	pbits = new unsigned char[w * pgm->m_ysize];

	unsigned char *p;
	unsigned char **im, **im2;
	im = pgm->image;
	im2 = pgm2->image;
	int xs, ys;
	xs = pgm->m_xsize;
	ys = pgm->m_ysize;
	for( int y=0; y<ys; y++ ) {
		p = pbits + w*y;
		for( int x=0; x<xs; x++ ) {
			*(p++) = im[ys-1-y][x];
			*(p++) = im[ys-1-y][x];
			*(p++) = im[ys-1-y][x] + im2[ys-1-y][x];
		}
	}
	m_xsize = xs;
	m_ysize = ys;
	m_pbits_wide = w;

	m_SetFlag = TRUE;
}


void CImgBmp::ClearPicture( )
{
	if( pbmi != NULL )  delete[] (BYTE*)pbmi;
	if( pbits != NULL ) delete[] pbits;
	pbmi = NULL;
	pbits = NULL;
	m_SetFlag = FALSE;
}


BOOL CImgBmp::SaveFile()
{
	CString m_file_name;

	CFileDialog  dlg(FALSE, "bmp", NULL, 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
		"Output Image File(*.bmp)|*.bmp|All File(*.*)|*.*||");

	dlg.m_ofn.lpstrTitle = "Save Bit Map File";
	if( dlg.DoModal() == IDCANCEL ) {
		return FALSE;
	}

	m_file_name = dlg.GetPathName();

	HANDLE	hfile;
	DWORD	tmp;

	hfile = CreateFile( m_file_name, GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
						CREATE_ALWAYS, 0, NULL );
	WriteFile( hfile, &bmfh, sizeof(bmfh), &tmp, NULL );
	WriteFile( hfile, &pbmi->bmiHeader, sizeof( pbmi->bmiHeader), &tmp, NULL );
	SetFilePointer( hfile, bmfh.bfOffBits, NULL, FILE_BEGIN );
	WriteFile( hfile, pbits, pbmi->bmiHeader.biSizeImage, &tmp, NULL );

	CloseHandle( hfile);

	return TRUE;
}


BOOL CImgBmp::SaveFile( CString m_file_name )
{

	HANDLE	hfile;
	DWORD	tmp;

	hfile = CreateFile( m_file_name, GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
						CREATE_ALWAYS, 0, NULL );
	WriteFile( hfile, &bmfh, sizeof(bmfh), &tmp, NULL );
	WriteFile( hfile, &pbmi->bmiHeader, sizeof( pbmi->bmiHeader), &tmp, NULL );
	SetFilePointer( hfile, bmfh.bfOffBits, NULL, FILE_BEGIN );
	WriteFile( hfile, pbits, pbmi->bmiHeader.biSizeImage, &tmp, NULL );

	CloseHandle( hfile);

	return TRUE;
}

void CImgBmp::AddPoint( int n, CPoint cp[], unsigned char col[][3], int col_num )
{
	int i, j, x, y;
	CString mes;
	for( i=0; i<n; i++ ) {
		x = cp[i].x;	y = m_ysize - cp[i].y - 1;
		j = i % col_num;
		SetPoint( x-1, y-1, col[j] );
		SetPoint( x-1, y  , col[j] );
		SetPoint( x-1, y+1, col[j] );
		SetPoint( x  , y-1, col[j] );
		SetPoint( x  , y  , col[j] );
		SetPoint( x  , y+1, col[j] );
		SetPoint( x+1, y-1, col[j] );
		SetPoint( x+1, y  , col[j] );
		SetPoint( x+1, y+1, col[j] );
	}
}

void CImgBmp::SetPoint( int x, int y, unsigned char col[] )
{
	unsigned char *p;
	p = pbits + m_pbits_wide * y + 3*x;

	*(p++) = col[0];
	*(p++) = col[1];
	*(p++) = col[2];
}

/////////////////////////////////////////////////////////////////////////////////////
//	Hough変換用
/////////////////////////////////////////////////////////////////////////////////////

void CImgBmp::Hough_inverse( int n, CPoint cp[], unsigned char ic[][3], int col_num )
/* 逆変換して画像中に直線を描く． */
{
int i;
	for( i=0; i<n; i++ ) {
		draw_line( cp[i], ic[i%col_num], MAX_THETA, MAX_RHO );
	}
}




void CImgBmp::draw_line( CPoint cp, unsigned char ic[], double max_theta, double max_rho )
/* θρ平面上（image1上）の点(xs,ys)を画像上の直線に逆変換し，   */
/* 結果を image に描く                                    */
{
    double theta, rho, rho_max, _sin, _cos;  /* 作業変数 */
    int x, y;  /* 制御変数 */
	int x_s, y_s;

	int	xs,ys;
	x_s = m_xsize;
	y_s = m_ysize;

	xs = cp.x;
	ys = cp.y;

    theta = 180.0 * xs / max_theta;  /* [deg] */
    _sin = sin( theta / 180.0 * PI );
    _cos = cos( theta / 180.0 * PI );
    rho_max = 1.0 / 1.5 * x_s + 1.0 / 1.5 * y_s;
    rho = ( ys - max_rho / 2.0 ) * rho_max / max_rho * 2.0; 
    /*  rho = x _cos + y _sin  --->  y = rho/_sin - x _cos/_sin  */
    if ( 45.0 <= theta && theta <= 135.0 ){ /* 数値の単位は[deg] */
        for ( x=0; x<x_s; x++ ){
            y = (int)( ( rho - x * _cos ) / _sin );
            if ( 0 <= y && y < y_s )
				SetPoint( x, m_ysize-y-1, ic );
        }
    } else {
        for ( y=0; y<y_s; y++ ){
            x = (int)( ( rho - y * _sin ) / _cos );
            if ( 0 <= x && x < x_s )
				SetPoint( x, m_ysize-y-1, ic );
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//	PatR用
/////////////////////////////////////////////////////////////////////////////////////
void CImgBmp::SetPicture_3(CImgPgm *pgm1, CImgPgm *pgm2, CImgPgm *pgm3 )
{
//　ビットマップインフォ作成
	if( pbmi != NULL )  delete[] (BYTE*)pbmi;
	pbmi = (BITMAPINFO*) new BYTE[ sizeof(BITMAPINFOHEADER) ];
	ZeroMemory( &pbmi->bmiHeader, sizeof(pbmi->bmiHeader) );

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = pgm1->m_xsize;
	pbmi->bmiHeader.biHeight = pgm1->m_ysize;
	pbmi->bmiHeader.biBitCount = 24;
	pbmi->bmiHeader.biPlanes   = 1;
	pbmi->bmiHeader.biSizeImage = 
		((( pgm1->m_xsize*24 + 31 ) >>3 ) & 0xfffffffc ) * pgm1->m_ysize;
	//////////////////////////////////////////
	pbmi->bmiHeader.biClrImportant = 0;
	pbmi->bmiHeader.biClrUsed = 0;
	pbmi->bmiHeader.biCompression = 0;
	pbmi->bmiHeader.biXPelsPerMeter = 2000; // ?
	pbmi->bmiHeader.biYPelsPerMeter = 2000; // ?

//　ビットマップファイルヘッダ作成
	bmfh.bfType = 'B' + ('M'<<8);
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)*sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + pbmi->bmiHeader.biSizeImage;

	int w = ((pgm1->m_xsize*24+31)>>3) & 0xfffffffc;
	if( pbits != NULL ) delete[] pbits;
	pbits = new unsigned char[w * pgm1->m_ysize];

	unsigned char *p;
	unsigned char **im1, **im2, **im3;
	im1 = pgm1->image;
	im2 = pgm2->image;
	im3 = pgm3->image;
	int xs, ys;
	xs = pgm1->m_xsize;
	ys = pgm1->m_ysize;
	for( int y=0; y<ys; y++ ) {
		p = pbits + w*y;
		for( int x=0; x<xs; x++ ) {
			*(p++) = im1[ys-1-y][x];
			*(p++) = im2[ys-1-y][x];
			*(p++) = im3[ys-1-y][x];
		}
	}
	m_xsize = xs;
	m_ysize = ys;
	m_pbits_wide = w;

	m_SetFlag = TRUE;
}

void CImgBmp::CopyImage( CImgBmp *bmp1 )
{
//　ビットマップインフォ作成

	if( pbmi != NULL )  delete[] (BYTE*)pbmi;
	pbmi = (BITMAPINFO*) new BYTE[ sizeof(BITMAPINFOHEADER) ];
	ZeroMemory( &pbmi->bmiHeader, sizeof(pbmi->bmiHeader) );

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp1->m_xsize;
	pbmi->bmiHeader.biHeight = bmp1->m_ysize;
	pbmi->bmiHeader.biBitCount = 24;
	pbmi->bmiHeader.biPlanes   = 1;
	pbmi->bmiHeader.biSizeImage = 
		((( bmp1->m_xsize*24 + 31 ) >>3 ) & 0xfffffffc ) * bmp1->m_ysize;
	//////////////////////////////////////////
	pbmi->bmiHeader.biClrImportant = 0;
	pbmi->bmiHeader.biClrUsed = 0;
	pbmi->bmiHeader.biCompression = 0;
	pbmi->bmiHeader.biXPelsPerMeter = 2000; // ?
	pbmi->bmiHeader.biYPelsPerMeter = 2000; // ?

//　ビットマップファイルヘッダ作成
	bmfh.bfType = 'B' + ('M'<<8);
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)*sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + pbmi->bmiHeader.biSizeImage;


	int w = ((bmp1->m_xsize*24+31)>>3) & 0xfffffffc;
	if( pbits != NULL ) delete[] pbits;
	pbits = new unsigned char[w * bmp1->m_ysize];

	unsigned char *p, *p1;
	p = pbits;
	p1 = bmp1->pbits;

	memcpy( p, p1, w*bmp1->m_ysize );

	m_xsize = bmp1->m_xsize;
	m_ysize = bmp1->m_ysize;
	m_pbits_wide = w;

	m_SetFlag = TRUE;
}
