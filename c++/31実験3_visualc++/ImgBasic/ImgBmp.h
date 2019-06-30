#pragma once

#include "ImgPgm.h"

class CImgBmp
{
public:
	CImgBmp(void);
	~CImgBmp(void);

	void SetPicture(CImgPgm *pgm);
	void ClearPicture( );
	BOOL SaveFile();
	BOOL SaveFile( CString m_file_name );

	BITMAPFILEHEADER	bmfh;
	BITMAPINFO			*pbmi;
	unsigned char		*pbits;

	BOOL				m_SetFlag;

/////////////////////////////////////////////////////////////////////////////
//  FFT—p
/////////////////////////////////////////////////////////////////////////////

	void SetPicture_g(CImgPgm *pgm, float gain = 1.0 );
	void SetPicture_2(CImgPgm *pgm, CImgPgm *pgm2 );

	void AddPoint( int n, CPoint cp[], unsigned char col[][3], int col_num );
	void SetPoint( int x, int y, unsigned char col[] );

	int					m_xsize;
	int					m_ysize;
	int					m_pbits_wide;

/////////////////////////////////////////////////////////////////////////////
//  Hough•ÏŠ·—p
/////////////////////////////////////////////////////////////////////////////
	void Hough_inverse( int n, CPoint cp[], unsigned char ic[][3], int col_num );
	void draw_line( CPoint cp, unsigned char ic[], double max_theta, double max_rho );

/////////////////////////////////////////////////////////////////////////////
//  PatR—p
/////////////////////////////////////////////////////////////////////////////
//	void SetPicture2(CImgPgm *pgm, CImgPgm *pgm2 );
	void SetPicture_3(CImgPgm *pgm1, CImgPgm *pgm2, CImgPgm *pgm3 );
	void CopyImage( CImgBmp *bmp1 );

/////////////////////////////////////////////////////////////////////////////

};
