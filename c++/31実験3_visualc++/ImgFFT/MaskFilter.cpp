#include <stdafx.h>

#include "MaskFilter.h"


void	SetFilterSobel_h( SFilter *w )
{
// Sobel������������) //
int weight[3][3] = {
		{ -1,  0,  1 },
		{ -2,  0,  2 },
		{ -1,  0,  1 }  };

	w->scale = 1.0;		/* <== �t�B���^������Ɋ|���鐔 */
	w->bias = 128.0;		/* <== scale ���|������ŉ����鐔 */
	w->normalize = 1;	/* 1 �̎��A�ő�ŏ��l�Ŏ����I�ɋK�i�� */
						/* 1 �̎��Aw->scale �� w->bias �͖��� */
						/* 0 �̎��Aw->scale �� w->bias ���L�� */
	for( int i=0; i<3; i++ ) {
		for( int j=0; j<3; j++ ) {
			w->weight[i][j] = weight[i][j];
		}
	}
}

void	SetFilterSobel_v( SFilter *w )
{
// Sobel������������ //
int weight[3][3] = {
	{ -1,  -2,  -1 },
	{  0,   0,   0 },
	{  1,   2,   1 }  };

	w->scale = 1.0;		/* <== �t�B���^������Ɋ|���鐔 */
	w->bias = 128.0;	/* <== scale ���|������ŉ����鐔 */
	w->normalize = 1;	/* 1 �̎��A�ő�ŏ��l�Ŏ����I�ɋK�i�� */
						/* 1 �̎��Aw->scale �� w->bias �͖��� */
						/* 0 �̎��Aw->scale �� w->bias ���L�� */
	for( int i=0; i<3; i++ ) {
		for( int j=0; j<3; j++ ) {
			w->weight[i][j] = weight[i][j];
		}
	}

}

void	SetFilterSmooth( SFilter *w )
{
// 3x3��8�ߖT���`������) //
int weight[3][3] = {
		{ 1,  1,  1 },
		{ 1,  2,  1 },
		{ 1,  1,  1 }  };

	w->scale = 0.1;		/* <== �t�B���^������Ɋ|���鐔 */
	w->bias  = 0.0;	/* <== scale ���|������ŉ����鐔 */
	w->normalize = 0;	/* 1 �̎��A�ő�ŏ��l�Ŏ����I�ɋK�i�� */
						/* 1 �̎��Aw->scale �� w->bias �͖��� */
						/* 0 �̎��Aw->scale �� w->bias ���L�� */

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

	w->scale = 1.0;		/* <== �t�B���^������Ɋ|���鐔 */
	w->bias = 128.0;	/* <== scale ���|������ŉ����鐔 */
	w->normalize = 0;	/* 1 �̎��A�ő�ŏ��l�Ŏ����I�ɋK�i�� */
						/* 1 �̎��Aw->scale �� w->bias �͖��� */
						/* 0 �̎��Aw->scale �� w->bias ���L�� */

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

	w->scale = 1.0;		/* <== �t�B���^������Ɋ|���鐔 */
	w->bias  = 0.0;		/* <== scale ���|������ŉ����鐔 */
	w->normalize = 0;	/* 1 �̎��A�ő�ŏ��l�Ŏ����I�ɋK�i�� */
						/* 1 �̎��Aw->scale �� w->bias �͖��� */
						/* 0 �̎��Aw->scale �� w->bias ���L�� */

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

	w->scale = 1.0;		/* <== �t�B���^������Ɋ|���鐔 */
	w->bias  = 0.0;		/* <== scale ���|������ŉ����鐔 */
	w->normalize = 0;	/* 1 �̎��A�ő�ŏ��l�Ŏ����I�ɋK�i�� */
						/* 1 �̎��Aw->scale �� w->bias �͖��� */
						/* 0 �̎��Aw->scale �� w->bias ���L�� */

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

	w->scale = 1.0;		/* <== �t�B���^������Ɋ|���鐔 */
	w->bias  = 0.0;		/* <== scale ���|������ŉ����鐔 */
	w->normalize = 0;	/* 1 �̎��A�ő�ŏ��l�Ŏ����I�ɋK�i�� */
						/* 1 �̎��Aw->scale �� w->bias �͖��� */
						/* 0 �̎��Aw->scale �� w->bias ���L�� */

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

