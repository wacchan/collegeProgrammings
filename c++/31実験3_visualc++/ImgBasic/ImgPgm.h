#pragma once

#include "MaskFilter.h"

class CImgPgm
{
public:
	CImgPgm(void);
	~CImgPgm(void);

	unsigned char **ImageAlloc( int x, int y  );
	void ImageFree( int y, unsigned char **im  );
	void Create( int x, int y, int gray );
	BOOL LoadFile( CString *m_file_name, CString *dir_name );
	BOOL LoadFile( CString m_file_name );
	BOOL SaveFile( CString *file_name, CString *dir_name );
	BOOL SaveFile( CString m_file_name );

	CImgPgm& operator = (CImgPgm& A);
	void CopyImage( CImgPgm *p );

	void spacial_filtering( SFilter w );
	void spacial_median_filtering( );

	void ImgReverse();
	void ImgBin(int thresh, int count[] );

	void AddNoiseGaussian( double mean, double var );
	void AddNoiseImpulse( double thresh );

	void HistLinearTrans();
	void HistEquivTrans();

	void ZeroCross( int bias );

	int	m_xsize;
	int	m_ysize;
	int	m_max_gray;
	unsigned char **image;

	BOOL	m_SetFlag;

////////////////////////////////////////////////////////////////////////////////
//  FFT用
////////////////////////////////////////////////////////////////////////////////
	void	SetPeakPoint( int n, CPoint cp[] );

	void	MakeFigure( int kind, double omega_p, double omega_q, double theta );
	double	FigRect( double t );
	double	FigTriangle( double t );
	void	FigLine( double omega_p, double omega_q, double theta  );
	void	SetBit( unsigned char c );

	
////////////////////////////////////////////////////////////////////////////////
//  Hough変換用
////////////////////////////////////////////////////////////////////////////////
	int		find_itera( CPoint cp );
	int		find_min( long vec[], int num );
	void	DetectPeak( int n, CPoint cp[], int thresh );
	int		Find_Image_Max( CPoint *cp, int *n );
//	void	SetPeakPoint( int n, CPoint cp[] );

////////////////////////////////////////////////////////////////////////////////
//  PatR用
////////////////////////////////////////////////////////////////////////////////
	int		CompareImage( CImgPgm *p );
	int		CompareImage( CPoint orig, CImgPgm *p, CPoint temp, int width, int height );

////////////////////////////////////////////////////////////////////////////////
//  合成用
////////////////////////////////////////////////////////////////////////////////
	void UserProc1( CImgPgm *p1, CImgPgm *p2, CImgPgm *p3 );
	void UserProc2( CImgPgm *p1, CImgPgm *p2, CImgPgm *p3 );
	void UserProc3( CImgPgm *p1, CImgPgm *p2, CImgPgm *p3 );
	void UserProcColor1( int lm, CImgPgm *pblue, CImgPgm *pgreen, CImgPgm *pred );
	void UserProcColor2( int lm[], CImgPgm *p[] );

};
