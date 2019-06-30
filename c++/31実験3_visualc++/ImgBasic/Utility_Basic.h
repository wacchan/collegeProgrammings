#pragma once

//#include "stdafx.h"

/* 定数宣言 */
#define MAX_BRIGHTNESS  255 /* 想定する最大階調値 */
#define GRAYLEVEL       256 /* 想定する階調数(=最大階調値+1) */

#define PI  3.141592653589  /* 円周率 */
//#define MAX_THETA   360  /* θ軸のサイズ（0.5[deg]=１画素）*/
//#define MAX_RHO     720  /* ρ軸のサイズ                 */

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

