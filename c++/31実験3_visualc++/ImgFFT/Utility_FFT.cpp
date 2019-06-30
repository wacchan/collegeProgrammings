
#include <StdAfx.h>
#include "ImgFFT.h"
#include <math.h>

/////////////////////////////////////////////

////////////////////////
//  f == -1.0:  fft 
//  f == +1.0:  ifft
////////////////////////
int kfft( CComplex csig[], int n, double f )
{
int	i, j, k, n1, ns, jj;
double	sc, s1, c1, s, c; 
//	double t, xx, yy;
CComplex	multi, multi_0, temp;

	n1 = n / 2;
	sc = PI;

	j = 0;
	for( i=0; i<n-1; i++ )	// Bit Reversal
	{
		if( i<=j ) {
			swap_complex( &csig[i], &csig[j] );
			//	t=x[i];  x[i]=x[j];  x[j]=t;
			//	t=y[i];  y[i]=y[j];  y[j]=t;
		}
		k = n / 2;
		while( k<=j ) {
			j=j-k;	k/=2;
		}
		j = j+k;
	}

	ns = 1;
	while( ns<=n/2 ) 
	{
		c1 = cos(sc);		s1 = sin(f*sc);
		multi_0.real = c1;	multi_0.imag = s1;
		c = 1.0;			s = 0.0;
		multi.real = c;	multi.imag = s;
		for( i=0; i<ns; i++ ) 
		{
			for( j=i; j<n; j+=(2*ns) )
			{
				jj = j + ns;
				temp = multi * csig[jj];
				csig[jj] = csig[j] - temp;
				csig[j]  = csig[j] + temp;
			}
			multi = multi_0 * multi;
		}
		ns *= 2;
		sc /= 2.0;
	}
	
	if( f<0.0 )
		for( i=0; i<n; i++ ) {
			csig[i] = csig[i] / (double)n;
		}

	return	0;
}


void swap_complex( CComplex *first, CComplex *second )
{
	CComplex temp;
	temp = *first;
	*first = *second;
	*second = temp;
	return;
}


/////////////////////////////////////////
//              ２次元FFT              //
/////////////////////////////////////////
int Make_FFT_Data(  CImgPgm *data, CCompMat *CMat )
/* image1[y][x] のデータを data[y][x], jdata[y][x] に代入する */
{
	int	num_of_data;
	int i, j; /* 制御変数 */
	int x_s, y_s;
	x_s = data->m_xsize;
	y_s = data->m_ysize;

	if ( x_s != y_s ){
		AfxMessageBox( "縦と横の画素数が異なっているので終了します．\n");
		return -1;
	} else {
		num_of_data = x_s;
		for ( i = 0; i < num_of_data; i ++ ){
			for ( j = 0; j < num_of_data; j ++ ){
				CMat->mat[i][j].real = (double)data->image[i][j];
				CMat->mat[i][j].imag = 0.0;
				//r2_data[i][j] = (double)data->image[i][j];
				//j2_data[i][j] = 0.0;
			}
		}
	}
	return 0;
}


void kfft2( CCompMat *CMat, int num_of_data, int flag )
/* 元データを data, jdata, num_of_data に代入してから使う */
/* flag = 1 : ２次元 FFT, flag = -1 : ２次元逆 FFT        */
{
    int i, j; /* ループ変数 */
	CComplex vec[MAX_FFT];

	for ( i = 0; i < num_of_data; i ++ ){
		for ( j = 0; j < num_of_data; j ++ ) vec[j] = CMat->mat[i][j];
		kfft( vec, num_of_data, -flag );
		for ( j = 0; j < num_of_data; j ++ ) CMat->mat[i][j] = vec[j];
	}
	for ( i = 0; i < num_of_data; i ++ ){
		for ( j = 0; j < num_of_data; j ++ ) vec[j] = CMat->mat[j][i];
		kfft( vec, num_of_data, -flag );
		for ( j = 0; j < num_of_data; j ++ ) CMat->mat[j][i] = vec[j];
	}
}


void fft_filtering1( CCompMat *CMat, int num_of_data )
// 周波数領域に対するフィルタリングを行う //
// 例：低域通過フィルタ                   //
{
  int i, j, di, dj;
  double r2;
  double sigma2;
  double sigma=16;
  sigma2=sigma*sigma;
  for ( i = 0; i < num_of_data; i ++ ){
        for ( j = 0; j < num_of_data; j ++ ){
			if(i<num_of_data/2) di=i;
			else				di=num_of_data-i;
			if(j<num_of_data/2)	dj=j;
			else				dj=num_of_data-j;
			r2=di*di+dj*dj;
            CMat->mat[i][j].real *= exp(-r2/sigma2);
            CMat->mat[i][j].imag *= exp(-r2/sigma2);
        }
    }
}

void fft_filtering2( CCompMat *CMat, int num_of_data )
// 周波数領域に対するフィルタリングを行う //
// 例：低域通過フィルタ                   //
{
  int i, j, di, dj;
  double r2;
  double sigma2;
  double sigma=100;
  sigma2=sigma*sigma;
  for ( i = 0; i < num_of_data; i ++ ){
        for ( j = 0; j < num_of_data; j ++ ){
			if(i>num_of_data/2) di=-num_of_data/2+i;
			else				di=num_of_data/2-i;
			if(j>num_of_data/2)	dj=-num_of_data/2+j;
			else				dj=num_of_data/2-j;
			r2=di*di+dj*dj;
            CMat->mat[i][j].real *= exp(-r2/sigma2);
            CMat->mat[i][j].imag *= exp(-r2/sigma2);
        }
    }
}

void fft_filtering3( CCompMat *CMat, int num_of_data )
// 周波数領域に対するフィルタリングを行う //
// 例：低域通過フィルタ                   //
{
  int i, j, di, dj;
  double r2;
  double sigma2;
  double sigma=50;
  sigma2=sigma*sigma;
  for ( i = 0; i < num_of_data; i ++ ){
        for ( j = 0; j < num_of_data; j ++ ){
			if(j<num_of_data/2)	dj=num_of_data/2-j;
			else				dj=-num_of_data/2+j;
			r2=dj*dj;
            CMat->mat[i][j].real *= exp(-r2/sigma2);
            CMat->mat[i][j].imag *= exp(-r2/sigma2);
        }
    }
}

