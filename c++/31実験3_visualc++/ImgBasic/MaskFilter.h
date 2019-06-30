#pragma once


typedef struct {
	int weight[3][3];
	double scale;
	double bias;
	int normalize;
} SFilter;

//////////////////////////////////////////////////////
	void	SetFilterSobel_h( SFilter *w );
	void	SetFilterSobel_v( SFilter *w );
	void	SetFilterSmooth(  SFilter *w );
	void	SetFilterLaplace( SFilter *w );

	void	SetFilterUser1( SFilter *w );
	void	SetFilterUser2( SFilter *w );
	void	SetFilterUser3( SFilter *w );

	unsigned char ImgMedian( unsigned char im[], int n );
//////////////////////////////////////////////////////
