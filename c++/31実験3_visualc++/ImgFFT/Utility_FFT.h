
/* �萔�錾 */
#define MAX_BRIGHTNESS  255 /* �z�肷��ő�K���l */
#define GRAYLEVEL       256 /* �z�肷��K����(=�ő�K���l+1) */

#define PI  3.141592653589  /* �~���� */
//#define MAX_THETA   360  /* �Ǝ��̃T�C�Y�i0.5[deg]=�P��f�j*/
//#define MAX_RHO     720  /* �ώ��̃T�C�Y                 */

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


