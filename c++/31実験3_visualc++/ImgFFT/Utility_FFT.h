
/* 定数宣言 */
#define MAX_BRIGHTNESS  255 /* 想定する最大階調値 */
#define GRAYLEVEL       256 /* 想定する階調数(=最大階調値+1) */

#define PI  3.141592653589  /* 円周率 */
//#define MAX_THETA   360  /* θ軸のサイズ（0.5[deg]=１画素）*/
//#define MAX_RHO     720  /* ρ軸のサイズ                 */

#define MAX_FFT	1024

// #include "ImgPgm.h"
// #include "Complex.h"
#include "stdafx.h"

int		kfft( CComplex c[], int n, double f );
void	swap_complex( CComplex *first, CComplex *second );
int		Make_FFT_Data( CImgPgm *data, CCompMat *CMat );
void	kfft2( CCompMat *CMat, int num_of_data, int flag );
void	fft_filtering1( CCompMat *CMat, int num_of_data );
void	fft_filtering2( CCompMat *CMat, int num_of_data );
void	fft_filtering3( CCompMat *CMat, int num_of_data );


