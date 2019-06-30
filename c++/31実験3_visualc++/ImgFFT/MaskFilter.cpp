#include <stdafx.h>

#include "MaskFilter.h"


void	SetFilterSobel_h( SFilter *w )
{
// Sobel水平方向微分) //
int weight[3][3] = {
		{ -1,  0,  1 },
		{ -2,  0,  2 },
		{ -1,  0,  1 }  };

	w->scale = 1.0;		/* <== フィルタ処理後に掛ける数 */
	w->bias = 128.0;		/* <== scale を掛けた後で加える数 */
	w->normalize = 1;	/* 1 の時、最大最小値で自動的に規格化 */
						/* 1 の時、w->scale と w->bias は無効 */
						/* 0 の時、w->scale と w->bias が有効 */
	for( int i=0; i<3; i++ ) {
		for( int j=0; j<3; j++ ) {
			w->weight[i][j] = weight[i][j];
		}
	}
}

void	SetFilterSobel_v( SFilter *w )
{
// Sobel垂直方向微分 //
int weight[3][3] = {
	{ -1,  -2,  -1 },
	{  0,   0,   0 },
	{  1,   2,   1 }  };

	w->scale = 1.0;		/* <== フィルタ処理後に掛ける数 */
	w->bias = 128.0;	/* <== scale を掛けた後で加える数 */
	w->normalize = 1;	/* 1 の時、最大最小値で自動的に規格化 */
						/* 1 の時、w->scale と w->bias は無効 */
						/* 0 の時、w->scale と w->bias が有効 */
	for( int i=0; i<3; i++ ) {
		for( int j=0; j<3; j++ ) {
			w->weight[i][j] = weight[i][j];
		}
	}

}

void	SetFilterSmooth( SFilter *w )
{
// 3x3の8近傍線形平滑化) //
int weight[3][3] = {
		{ 1,  1,  1 },
		{ 1,  2,  1 },
		{ 1,  1,  1 }  };

	w->scale = 0.1;		/* <== フィルタ処理後に掛ける数 */
	w->bias  = 0.0;	/* <== scale を掛けた後で加える数 */
	w->normalize = 0;	/* 1 の時、最大最小値で自動的に規格化 */
						/* 1 の時、w->scale と w->bias は無効 */
						/* 0 の時、w->scale と w->bias が有効 */

	for( int i=0; i<3; i++ ) {
		for( int j=0; j<3; j++ ) {
			w->weight[i][j] = weight[i][j];
		}
	}
}

void	SetFilterLaplace( SFilter *w )
{
// Laplacian //
int weight[3][3] = {
		{  1,   1,   1 },
		{  1,  -8,   1 },
		{  1,   1,   1 }  };

	w->scale = 1.0;		/* <== フィルタ処理後に掛ける数 */
	w->bias = 128.0;	/* <== scale を掛けた後で加える数 */
	w->normalize = 0;	/* 1 の時、最大最小値で自動的に規格化 */
						/* 1 の時、w->scale と w->bias は無効 */
						/* 0 の時、w->scale と w->bias が有効 */

	for( int i=0; i<3; i++ ) {
		for( int j=0; j<3; j++ ) {
			w->weight[i][j] = weight[i][j];
		}
	}

}


void	SetFilterUser1( SFilter *w )
{
// User 1 //
int weight[3][3] = {
		{  0,   0,   0 },
		{  0,   1,   0 },
		{  0,   0,   0 }  };

	w->scale = 1.0;		/* <== フィルタ処理後に掛ける数 */
	w->bias  = 0.0;		/* <== scale を掛けた後で加える数 */
	w->normalize = 0;	/* 1 の時、最大最小値で自動的に規格化 */
						/* 1 の時、w->scale と w->bias は無効 */
						/* 0 の時、w->scale と w->bias が有効 */

	for( int i=0; i<3; i++ ) {
		for( int j=0; j<3; j++ ) {
			w->weight[i][j] = weight[i][j];
		}
	}

}


void	SetFilterUser2( SFilter *w )
{
// User 2 //
int weight[3][3] = {
		{  0,   0,   0 },
		{  0,   1,   0 },
		{  0,   0,   0 }  };

	w->scale = 1.0;		/* <== フィルタ処理後に掛ける数 */
	w->bias  = 0.0;		/* <== scale を掛けた後で加える数 */
	w->normalize = 0;	/* 1 の時、最大最小値で自動的に規格化 */
						/* 1 の時、w->scale と w->bias は無効 */
						/* 0 の時、w->scale と w->bias が有効 */

	for( int i=0; i<3; i++ ) {
		for( int j=0; j<3; j++ ) {
			w->weight[i][j] = weight[i][j];
		}
	}

}


void	SetFilterUser3( SFilter *w )
{
// User 3 //
int weight[3][3] = {
		{  0,   0,   0 },
		{  0,   1,   0 },
		{  0,   0,   0 }  };

	w->scale = 1.0;		/* <== フィルタ処理後に掛ける数 */
	w->bias  = 0.0;		/* <== scale を掛けた後で加える数 */
	w->normalize = 0;	/* 1 の時、最大最小値で自動的に規格化 */
						/* 1 の時、w->scale と w->bias は無効 */
						/* 0 の時、w->scale と w->bias が有効 */

	for( int i=0; i<3; i++ ) {
		for( int j=0; j<3; j++ ) {
			w->weight[i][j] = weight[i][j];
		}
	}

}


unsigned char ImgMedian( unsigned char im[], int n )
{
	int i, j;
	unsigned char temp;

	for( i=0; i<n-1; i++ ) {
		for( j=i; j<n-1; j++ ) {
			if( im[i] < im[j+1] ) {
				temp = im[i];
				im[i] = im[j+1];
				im[j+1] = temp;
			}
		}
	}
	return im[n/2];
}

