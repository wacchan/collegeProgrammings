#pragma once

//#include "stdafx.h"

/* �萔�錾 */
#define MAX_BRIGHTNESS  255 /* �z�肷��ő�K���l */
#define GRAYLEVEL       256 /* �z�肷��K����(=�ő�K���l+1) */

#define PI  3.141592653589  /* �~���� */
//#define MAX_THETA   360  /* �Ǝ��̃T�C�Y�i0.5[deg]=�P��f�j*/
//#define MAX_RHO     720  /* �ώ��̃T�C�Y                 */

//#define MAX_FFT	1024


CString GetPgmFileName( int flag=0 );
FILE	*GetSaveFilePointer( CString *file_name, CString *dir_name );
FILE	*GetLoadFilePointer( CString *file_name, CString *dir_name );
double	GetNum( CString message );
void	GetNum2( CString title, CString mes1, CString mes2, double *v1, double *v2 );
int		OutputFileSelect( CString *fname, CString *dir_name, int kind );



static double m_Box_Num=0;

static double m_Box2_Num1=0;
static double m_Box2_Num2=0;

