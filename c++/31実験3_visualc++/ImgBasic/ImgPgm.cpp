#include "StdAfx.h"
#include "ImgPgm.h"

#include "ImgBasic.h"
#include "Random.h"
#include <math.h>

CImgPgm::CImgPgm(void)
{
	image = NULL;
	m_SetFlag = FALSE;
}

CImgPgm::~CImgPgm(void)
{
	if( image != NULL ) ImageFree( m_ysize, image );
}

unsigned char **CImgPgm::ImageAlloc( int x, int y  )
{
	unsigned char **im;
	im = new unsigned char*[y]; 
	for( int i=0; i<y; i++ ) im[i] = new unsigned char [x];
	return im;
}


void CImgPgm::ImageFree( int y, unsigned char **im  )
{
	if( im == NULL ) return;
	for( int i=0; i<y; i++ ) delete im[i];
	delete im;
}

void CImgPgm::Create( int x, int y, int gray )
{
	m_xsize = x;
	m_ysize = y;
	m_max_gray = gray;

	if( image!=NULL ) ImageFree( m_ysize, image );

	image = ImageAlloc( m_xsize, m_ysize );

	m_SetFlag = FALSE;
}

BOOL CImgPgm::LoadFile( CString *m_file_name, CString *dir_name )
{
char buffer[1024];	/* データ読み込み用作業変数 */
int  buf_size = 1024;
FILE *fp;			/* ファイルポインタ */

	if( (fp=GetLoadFilePointer( m_file_name, dir_name )) == NULL ) return FALSE;

    /* ファイルタイプ(=P5)の確認 */
	fgets( buffer, buf_size, fp );
	if ( buffer[0] != 'P' || buffer[1] != '5' ){
		AfxMessageBox( "ファイルのフォーマットが P5 とは異なります．\n" );
		return FALSE;
    }

	/* x_size, y_size の代入（#から始まるコメントは読み飛ばす） */
    m_xsize = 0;    m_ysize = 0;
    while ( m_xsize==0 || m_ysize==0 )
	{
		fgets( buffer, buf_size, fp );
		if ( buffer[0] != '#' ){
			sscanf_s( buffer, "%d %d", &m_xsize, &m_ysize );
		}
	}

	/* max_gray の代入（#から始まるコメントは読み飛ばす） */
	m_max_gray = 0;
	while ( m_max_gray==0 )
	{
		fgets( buffer, buf_size, fp );
		if ( buffer[0] != '#' ){
			sscanf_s( buffer, "%d", &m_max_gray );
		}
	}

    if ( m_max_gray != MAX_BRIGHTNESS )
	{
		AfxMessageBox( "最大階調値が不適切です．\n" );
		return FALSE;
	}

	Create( m_xsize, m_ysize, m_max_gray );

/* 画像データを読み込んで画像用配列に代入する */
	for( int y=0; y<m_ysize; y++ ) {
		fread( &image[y][0], sizeof( unsigned char ), m_xsize, fp );
	}
	fclose(fp);

//	AfxMessageBox( "データは正しく読み込まれました．\n" );
	m_SetFlag = TRUE;

	return TRUE;
}

BOOL CImgPgm::LoadFile( CString m_file_name )
{
char buffer[1024];	/* データ読み込み用作業変数 */
int  buf_size = 1024;
FILE *fp;			/* ファイルポインタ */

	if( ( fopen_s( &fp, m_file_name, "rb" )) != 0 ) return FALSE;

    /* ファイルタイプ(=P5)の確認 */
	fgets( buffer, buf_size, fp );
	if ( buffer[0] != 'P' || buffer[1] != '5' ){
		AfxMessageBox( "ファイルのフォーマットが P5 とは異なります．\n" );
		return FALSE;
    }

	/* x_size, y_size の代入（#から始まるコメントは読み飛ばす） */
    m_xsize = 0;    m_ysize = 0;
    while ( m_xsize==0 || m_ysize==0 )
	{
		fgets( buffer, buf_size, fp );
		if ( buffer[0] != '#' ){
			sscanf_s( buffer, "%d %d", &m_xsize, &m_ysize );
		}
	}

	/* max_gray の代入（#から始まるコメントは読み飛ばす） */
	m_max_gray = 0;
	while ( m_max_gray==0 )
	{
		fgets( buffer, buf_size, fp );
		if ( buffer[0] != '#' ){
			sscanf_s( buffer, "%d", &m_max_gray );
		}
	}

    if ( m_max_gray != MAX_BRIGHTNESS )
	{
		AfxMessageBox( "最大階調値が不適切です．\n" );
		return FALSE;
	}

	Create( m_xsize, m_ysize, m_max_gray );

/* 画像データを読み込んで画像用配列に代入する */
	for( int y=0; y<m_ysize; y++ ) {
		fread( &image[y][0], sizeof( unsigned char ), m_xsize, fp );
	}
	fclose(fp);

//	AfxMessageBox( "データは正しく読み込まれました．\n" );
	m_SetFlag = TRUE;

	return TRUE;
}




BOOL CImgPgm::SaveFile( CString m_file_name )
{
int		x, y;
FILE *fp;
errno_t err;

	if( (err=fopen_s( &fp, m_file_name, "wb" )) != 0 ) return FALSE;

// ファイル識別子 "P5" を先頭に出力する //
	fputs("P5\n",fp);
// ヒント：fputs() か fprintf() を使う //
// # で始まるコメント行（省略可能） //
	fputs( "# Created by Image Processing\n", fp );
// 画像の横幅(m_xsize),縦幅(m_ysize)の出力 //
	fprintf(fp,"%d %d\n", m_xsize, m_ysize);
// 最大階調値 (m_max_gray) の出力 //
	fprintf(fp, "%d\n", m_max_gray);
// 画像データimage[y][x]の出力//
// fputc() を使う //
	for(y=0; y<m_ysize; y++)
		for(x=0; x<m_xsize; x++)
			fputc(image[y][x], fp);





	fclose(fp);

//	AfxMessageBox( "データは正しく出力されました．" );

	return TRUE;
}


CImgPgm& CImgPgm::operator = (CImgPgm& A)
{

	m_xsize = A.m_xsize;
	m_ysize = A.m_ysize;
	m_max_gray = A.m_max_gray;
	image = NULL;
	Create( A.m_xsize, A.m_ysize, A.m_max_gray );
	for( int y=0; y<A.m_ysize; y++ ) {
		memcpy( image[y], A.image[y], A.m_xsize );
	}

	return *this;
}

void CImgPgm::CopyImage( CImgPgm *p )
{
	int xx, yy, gg;
	xx = p->m_xsize;
	yy = p->m_ysize;
	gg = p->m_max_gray;
	Create( xx, yy, gg );
	for( int y=0; y<yy; y++ ) {
		memcpy( image[y], p->image[y], xx );
	}
	m_SetFlag = TRUE;
}


void CImgPgm::ImgReverse()
{
int x, y;
//	int d;

	for( y=0; y<m_ysize; y++ ) 
	{
		for( x=0; x<m_xsize; x++ ) 
		{
			image[y][x] = MAX_BRIGHTNESS - image[y][x];
		}
	}

}

void CImgPgm::ImgBin(int thresh, int count[] )
{
	int x,y,d,dd;
	int x_s, y_s;
	int	count_0, count_255;

	dd = thresh;
	count_0 = 0;
	count_255 = 0;

	x_s = m_xsize;
	y_s = m_ysize;

	for(y=0;y<y_s;y++){
		for(x=0;x<x_s;x++){
			d = image[y][x];
			if(d < (dd & 255) ) 
			{
				image[y][x] = 0;
				count_0++;
			}
			else
			{
				image[y][x] = 255;
				count_255++;
			}
		} 
	}
	count[0] = count_0;
	count[1] = count_255;
}


void CImgPgm::spacial_filtering( SFilter w )
/* 画像の空間フィルタリングを行う．         */
/* Sobelフィルタ（水平方向微分）            */
/* 原画像 data_a ===> 変換後の画像 data_b   */
{
    double scale_const = 1.0; /* <== 最後に掛ける値 */
    double bias_const = 0.0;
    double pixel_value; /* 計算値 */
    double min, max; /* 計算値の最小値，最大値 */
    int x, y, i, j;  /* ループ変数 */
	int	x_s, y_s;

    scale_const = w.scale;
    bias_const = w.bias;

    /* フィルタリング後の階調値の最小値，最大値を求める */
    min = 255.0;
    max = 0.0;
	x_s = m_xsize;
	y_s = m_ysize;

    for ( y= 1; y<y_s-1; y++ ){
        for ( x=1; x<x_s-1; x++ ){
            pixel_value = 0.0;
            for ( i=-1; i<2; i++ )
                for ( j=-1; j<2; j++ )
                    pixel_value = pixel_value + 
                        w.weight[i+1][j+1] * image[y+i][x+j];
            pixel_value = pixel_value * scale_const + bias_const;
            if ( pixel_value < min ) min = pixel_value;
            if ( pixel_value > max ) max = pixel_value;
        }
    }
    if ( (int)(max - min) == 0 ) return;

	unsigned char **im;
	im = ImageAlloc( m_xsize, m_ysize );

    /* image2[y][x] の初期化(外郭の画素のため）*/
	for( y=0; y<y_s; y++ )
		for( x=0; x<x_s; x++ )
			im[y][x] = 0;
    /* 処理後の値を線形変換してから image2 に代入 */
    for( y=1; y<y_s-1; y++ )
	{
        for( x=1; x<x_s-1; x++ )
		{
            pixel_value = 0.0;
            for ( i=-1; i<2; i++ )
                for ( j=-1; j<2; j++ )
                    pixel_value = pixel_value +  
						w.weight[i+1][j+1] * image[y+i][x+j];
            pixel_value = pixel_value * scale_const + bias_const;
			if (w.normalize){
				pixel_value = MAX_BRIGHTNESS /
                         ( max - min ) * ( pixel_value - min );
			} else {
				if (pixel_value > 255) pixel_value=255;
				if (pixel_value < 0) pixel_value=0;
			}
            im[y][x] = (unsigned char)pixel_value;
        }
    }
	
	for( y=0; y<y_s; y++ ) {
		memcpy( image[y], im[y], m_xsize );
	}
	ImageFree( m_ysize, im );
}


void CImgPgm::spacial_median_filtering( )
/* 画像の空間フィルタリングを行う．         */
{
    int x, y, i, j, ij;  /* ループ変数 */
	int	x_s, y_s;

	unsigned char work[9];

	x_s = m_xsize;
	y_s = m_ysize;

	unsigned char **im;
	im = ImageAlloc( m_xsize, m_ysize );

    /* image2[y][x] の初期化(外郭の画素のため）*/
	for( y=0; y<y_s; y++ )
		for( x=0; x<x_s; x++ )
			im[y][x] = 0;
    /* 処理後の値を線形変換してから image2 に代入 */
    for( y=1; y<y_s-1; y++ )
	{
        for( x=1; x<x_s-1; x++ )
		{
			ij = 0;
			for( i=-1; i<2; i++ ) {
				for( j=-1; j<2; j++ ) {
					work[ij++] = image[y+i][x+j];
				}
			}
			im[y][x] = ImgMedian( work, 9 );
		}
	}
	
	for( y=0; y<y_s; y++ ) {
		memcpy( image[y], im[y], m_xsize );
	}
	ImageFree( m_ysize, im );
}


void CImgPgm::AddNoiseGaussian( double mean, double var )
/* 画像に白色ガウス雑音を付加する．         */
{
int x, y;
int u;

	randomize();
	for( y=0; y<m_ysize; y++ ) 
	{
		for( x=0; x<m_xsize; x++ ) 
		{
			u = (int)(image[y][x] + rand_n2()*var + mean);
			if( u > MAX_BRIGHTNESS ) u = MAX_BRIGHTNESS;
			if( u < 0              ) u = 0;
			image[y][x] = (unsigned char)u;
		}
	}
}


void CImgPgm::AddNoiseImpulse( double thresh )
/* 画像に白色インパルス雑音を付加する．         */
{
int x, y;

	randomize();
	for( y=0; y<m_ysize; y++ ) 
	{
		for( x=0; x<m_xsize; x++ ) 
		{
			if( rand_u() > thresh ) {
				if( rand_u() > 0.5 ) { image[y][x] = MAX_BRIGHTNESS; }
					else			 { image[y][x] = 0; }
			}
		}
	}
}

void CImgPgm::HistLinearTrans()
/* 画素の階調分布に対して線形変換を行う．             */
{
    int min, max; /* 階調値の最小値，最大値 */
    int x, y;     /* 制御変数 */
    int x_s, y_s;
    double pixel_value;
    x_s = m_xsize;
    y_s = m_ysize;

    /* 階調値の最小値，最大値を求める */
/*    min = 255;  max = 0;
    for ( y = 0; y < y_s; y ++ ){
        for ( x = 0; x < x_s; x ++ ){
            if ( image[y][x] < min ) min = image[y][x];
            if ( image[y][x] > max ) max = image[y][x];
        }
    }
*/
	double v1, v2;
	GetNum2( "階調値の最大・最小値入力", "最小値(0-255)", "最大値(0-255)", &v1, &v2 );
	//min=GetNum( "最小値を入力してください" );
	//max=GetNum( "最大値を入力してください" );
	min = (int)v1;
	max = (int)v2;
  if (min==max){min=0; max=255;}
        CString msg;
	msg.Format( "階調値の最小値 = %d，最大値 = %d\n", min, max );
	AfxMessageBox( msg );
    /* 階調を線形変換して image2[y][x] に代入 */

    for ( y = 0; y < y_s; y ++ )
		for ( x = 0; x < x_s; x ++ ){
			pixel_value = ( image[y][x] - min )
                           * MAX_BRIGHTNESS / (double)(max - min) ;
			if (pixel_value > 255) pixel_value=255;
			if (pixel_value < 0) pixel_value=0;
			image[y][x]=(unsigned char) pixel_value;
		}
}

void CImgPgm::HistEquivTrans()
{
//	サンプルプログラム2: ヒストグラム等化
//  幅：m_xsize;
//　高さ：m_ysize;
//　データ：image[][];
	int hist[MAX_BRIGHTNESS+1];
	int x,y,i;
	for (i=0; i<=MAX_BRIGHTNESS; i++)
		hist[i]=0;
	for (y=0; y<m_ysize; y++)
		for(x=0; x<m_xsize; x++)
			hist[image[y][x]]++;
	hist[0]=0;
	for(i=1; i<=MAX_BRIGHTNESS; i++)
		hist[i]=hist[i-1]+hist[i];
	for(i=0; i<=MAX_BRIGHTNESS; i++)
		hist[i]=(int)((hist[i]*MAX_BRIGHTNESS)/hist[MAX_BRIGHTNESS]);
	for(y=0; y<m_ysize; y++)
		for(x=0; x<m_xsize; x++)
			image[y][x]=hist[image[y][x]];
}

#define MINDIFF 2

void CImgPgm::ZeroCross( int bias )
{
	int x, y, x_s, y_s, gray;
	x_s = m_xsize;
	y_s = m_ysize;
	gray = m_max_gray;
	unsigned char **im;

	im = ImageAlloc( x_s, y_s );
	for( y=0; y<y_s; y++ )
		for( x=0; x<x_s; x++ )
			im[y][x] = 0;

	for( y=0; y<y_s; y++ ) {
		for( x=1; x<x_s-1; x++ ) {
			if( (image[y][x-1]-bias)*(image[y][x+1]-bias) < 0
				&& abs(image[y][x-1]-bias)> MINDIFF
				&& abs(image[y][x+1]-bias)> MINDIFF
			) im[y][x]=255;
		}
	}

	for( x=0; x<x_s; x++ ) {
		for( y=1; y<y_s-1; y++ ) {
			if( (image[y-1][x]-bias)*(image[y+1][x]-bias) < 0
				&& abs(image[y-1][x]-bias)> MINDIFF
				&& abs(image[y+1][x]-bias)> MINDIFF
			) im[y][x]=255;
		}
	}

	for( y=0; y<y_s; y++ ) {
		memcpy( image[y], im[y], m_xsize );
	}
	ImageFree( m_ysize, im );

}

void CImgPgm::SetPeakPoint( int n, CPoint cp[] )
{
	int x, y, itera;

	for( y=0; y<m_ysize; y++ ) {
		for( x=0; x<m_xsize; x++ ) {
			image[y][x] = 0;
		}
	}

	for( itera=0; itera<n; itera++ ) {
		int xs, xe, ys, ye;
		xs = cp[itera].x-1;		xe = cp[itera].x+1;
		ys = cp[itera].y-1;		ye = cp[itera].y+1;
		if( xs < 0 ) xs = 0;
		if( xe >= m_xsize ) xe = m_xsize-1;
		if( ys < 0 ) ys = 0;
		if( ye >= m_ysize ) ye = m_ysize-1;
		for( x=xs; x <=xe; x++ ) {
			for( y=ys; y<=ye; y++ ) {
				image[y][x] = 255;
			}
		}
	}
}


void CImgPgm::MakeFigure( int kind, double omega_p, double omega_q, double theta )
{
	int x,y;
	double p,q;
	double epi = 3.141592653589;
//	double omega_p=0.5;   /* p軸方向への角周波数 */
//	double omega_q=0.0;  /* q軸方向への角周波数 */
//	double theta=0.3; /* 回転角度 */
	switch( kind ) {
		case 1:
				for(y=0; y<m_ysize; y++)
					for(x=0; x<m_xsize; x++){
						p=cos(theta)*x-sin(theta)*y;
						q=sin(theta)*x+cos(theta)*y;
						image[y][x]=(int)(127.*(FigRect(omega_p*p)*FigRect(omega_q*q)+1.));
					}
				break;
		case 2:
				if( theta <= 0 ) theta = 0.0; //00001;
				if( theta > epi/2 )  theta = epi/2-0.01;
				FigLine( omega_p, omega_q, theta );
				break;
		case 3:
				for(y=0; y<m_ysize; y++)
					for(x=0; x<m_xsize; x++){
						p=cos(theta)*x-sin(theta)*y;
						q=sin(theta)*x+cos(theta)*y;
						image[y][x]=(int)(128.*(FigTriangle(omega_p*p)*FigTriangle(omega_q*q)-1.));
					}
				break;
		case 0:
		default:
				for(y=0; y<m_ysize; y++)
					for(x=0; x<m_xsize; x++){
						p=cos(theta)*x-sin(theta)*y;
						q=sin(theta)*x+cos(theta)*y;
						image[y][x]=(int)(127.*(cos(omega_p*p)*cos(omega_q*q)+1.));
					}
				break;
	}

}

double CImgPgm::FigRect( double t )
{
	double temp, va;
	if( t == 0.0 ) return 1.0;
	temp = cos( t );
	if( temp > 0 ) { va = 1.0; }
		else {va = -1.0;}
	return va;
}

double CImgPgm::FigTriangle( double t )
{
	double temp, va;
	int k;
	double tpi=3.141592653589;

	if( t==0.0 ) return 1.0;
	k = (int)(t / (2*tpi));
	if( t>=0 ) { temp = t - 2*tpi*k;  va = (temp)/(tpi+1)-1;}
	else		{ temp = (t - 2*tpi*(k-1)); va = (temp)/(tpi+1)-1;}
//	if( t>=0 ) {
//		if( k%2 == 0 ) {	va = (temp-tpi)/(tpi+1);}  
//		else {				va = (tpi-temp)/(tpi+1);}
//	}  else {
//		if( k%2 == 0 ) {	va = -(temp-tpi)/(tpi+1);}  
//		else {				va = -(tpi-temp)/(tpi+1);}
//	}
	return va;
}


void CImgPgm::FigLine( double omega_p, double omega_q, double theta  )
{
	int	i, x, y, nn;
	double a, b, dlen, _tan, dlen_div;
	double epi = 3.141592653589;
	double eps = 1.0e-6;
	_tan = tan(theta);

//  x   ///////////////////////////////////////////////////
	dlen = sqrt((double)m_xsize*m_xsize + m_ysize*m_ysize) 
			* cos( theta - atan((double)m_ysize/m_xsize));
	dlen_div = (2 * epi / omega_p) / cos( theta ) ;

	nn = (int)(dlen / (2 * epi ) * omega_p / cos(theta));
	for( i=0; i<=nn; i++ ) 
	{
		if( theta < eps ) {
			x = (int)(dlen_div * i);
			for( y=0; y<m_ysize; y++ ) image[y][x] = 255;
		}
		else 
		{
			b = dlen_div *i/ _tan;
			a = -1.0 / _tan;
			if( theta > epi/4 ) {
				for( x=0; x<m_xsize; x++ ) {
					y = (int)(a*x + b);
					y = m_ysize - y;
					if( y>=0 && y<m_ysize) { image[y][x] = 255;	}
				}
			} 
			else 
			{
				for( y=0; y<m_ysize; y++ ) 
				{
					x = (int)((m_ysize-y-b)/a);
					if( x>=0 && x<m_xsize ) { image[y][x] = 255;}
				}
			}
		}
	}

//  y   ///////////////////////////////////////////////////
	dlen = sqrt((double)m_xsize*m_xsize + m_ysize*m_ysize) 
			* cos( theta - atan((double)m_ysize/m_xsize));
	dlen_div = (2 * epi / omega_q) / cos( theta ) ;

	nn = (int)(dlen / (2 * epi ) * omega_q / cos(theta));
	for( i=0; i<=nn; i++ ) 
	{
		if( theta < eps ) {
			y = (int)(dlen_div * i);
			for( x=0; x<m_xsize; x++ ) image[y][x] = 255;
		}
		else 
		{
			b = dlen_div *i/ _tan;
			a = -1.0 / _tan;
			if( theta > epi/4 ) 
			{
				for( y=0; y<m_ysize; y++ ) {
//					x = (int)(a*(m_ysize-y) + b);
					x = (int)(a*(y) + b);
					if( x>=0 && x<m_xsize) { image[y][x] = 255;	}
				}
			} else 
			{
				for( x=0; x<m_xsize; x++ ) {
					y = (int)((x-b)/a);
					if( y>=0 && y<m_ysize ) { image[y][x] = 255;}
				}
			}
		}
	}

}


void CImgPgm::SetBit( unsigned char c )
{
	for( int y=0; y<m_ysize; y++ ) {
		for( int x=0; x<m_xsize; x++ ) {
			image[y][x] = c;
		}
	}
	m_SetFlag = TRUE;
}

//////////////////////////////////////////////////////////////////////////
//   Hough変換用
//////////////////////////////////////////////////////////////////////////
int	CImgPgm::Find_Image_Max( CPoint *cp, int *n )
{
	int	x, y, ymax;

	ymax = 0;	cp->x = 0;	cp->y = 0;
	*n = 0;

	for( y=0; y<m_ysize; y++ ) {
		for( x=0; x<m_xsize; x++ ) {
			if( image[y][x] > ymax ) {
				cp->x = x;
				cp->y = y;
				ymax = image[y][x];
			}
		}
	}
	if( ymax == 0 ) return ymax;
	*n = find_itera( *cp ) ;
	return ymax;
}

int CImgPgm::find_itera( CPoint cp )
{
	int n;
	long v[4];

	v[0] = cp.x;
	v[1] = m_xsize - cp.x;
	v[2] = cp.y;
	v[3] = m_ysize - cp.y;

	n = find_min( v, 4 );
	return n;
}

		
int	CImgPgm::find_min( long vec[], int num )
{
int	min_v;

    min_v = 10000;
	for( int i=0; i<num; i++ )
	{
		if ( vec[i] < min_v ) 
		{
			min_v = vec[i];
		}
	}
	return min_v;
}


void CImgPgm::DetectPeak( int n, CPoint cp[], int thresh )
{
int x, y, ymax, ymax2;
CPoint cmp;
int itera;
int nn, id, flag;

	for( itera=0; itera<n; itera++ ) {
		ymax = Find_Image_Max( &cmp, &nn );

		cp[itera] = cmp;
		image[cmp.y][cmp.x] = 0;

		flag = 0;
		id = 1;
		while( id<=nn && flag==0 ) {
			int xs, xe, ys, ye;
			xs = cmp.x - id;	xe = cmp.x + id;
			ys = cmp.y - id;	ye = cmp.y + id;
			if( xs < 0 ) xs = 0;
			if( xe >= m_xsize ) xe = m_xsize - 1;
			if( ys < 0 ) ys = 0;
			if( ye >= m_ysize ) ye = m_ysize - 1;

			ymax2 = image[ys][xs];
			for( x=xs; x<=xe; x++ ) {
				if( image[ys][x] > ymax2 ) ymax2 = image[ys][x];
				if( image[ye][x] > ymax2 ) ymax2 = image[ye][x];
			}
			for( y=ys+1; y<=ye-1; y++ ) {
				if( image[y][xs] > ymax2 ) ymax2 = image[y][xs];
				if( image[y][xe] > ymax2 ) ymax2 = image[y][xe];
			}

			if( ymax2 > ymax+thresh ) { flag = 1; }  
			else {
				ymax = ymax2;
				for( x=xs; x<=xe; x++ ) {
					image[ys][x] = 0;
					image[ye][x] = 0;
				}
				for( y=ys+1; y<=ye-1; y++ ) {
//				for( y=ys; y<=ye; y++ ) {
					image[y][xs] = 0;
					image[y][xe] = 0;
				}
			}
			id++;
		}
	}
	SetPeakPoint( n, cp );
}

/*
void CImgPgm::SetPeakPoint( int n, CPoint cp[] )
{
	int x, y, itera;

	for( y=0; y<m_ysize; y++ ) {
		for( x=0; x<m_xsize; x++ ) {
			image[y][x] = 0;
		}
	}

	for( itera=0; itera<n; itera++ ) {
		int xs, xe, ys, ye;
		xs = cp[itera].x-1;		xe = cp[itera].x+1;
		ys = cp[itera].y-1;		ye = cp[itera].y+1;
		if( xs < 0 ) xs = 0;
		if( xe >= m_xsize ) xe = m_xsize-1;
		if( ys < 0 ) ys = 0;
		if( ye >= m_ysize ) ye = m_ysize-1;
		for( x=xs; x <=xe; x++ ) {
			for( y=ys; y<=ye; y++ ) {
				image[y][x] = 255;
			}
		}
	}
}
*/
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//   PatR変換用
//////////////////////////////////////////////////////////////////////////
int CImgPgm::CompareImage( CImgPgm *p )
{
	int	x, y, xs, ys;
	int xx, yy, gsum=0;
	xx = p->m_xsize;
	yy = p->m_ysize;

	xs = m_xsize>xx ? xx:m_xsize;
	ys = m_ysize>yy ? yy:m_ysize;
	for( x=0; x<xs; x++ ) {
		for( y=0; y<ys; y++ ) {
			gsum += abs( image[y][x] - p->image[y][x] );
		}
	}
	return gsum;
}

int CImgPgm::CompareImage( CPoint orig, CImgPgm *p, CPoint temp, 
						  int width, int height )
{
	int	x, y, xs, ys;
	int xx, yy, gsum=0;
	CString mes;

	xx = temp.x;
	yy = temp.y;
	xs = orig.x;
	ys = orig.y;
	if( xx + width > p->m_xsize ) {
		mes.Format( "Window Width Over 0 : %d %d %d", xx, width, p->m_xsize );
		AfxMessageBox( mes );
		return 0;
	}
	if( yy + height> p->m_ysize ) {
		mes.Format( "Window Height Over 0 : %d %d %d", yy, height, p->m_ysize );
		AfxMessageBox( mes );
		return 0;
	}
	if( xs + width > m_xsize ) {
		mes.Format( "Window Width Over 1 : %d %d %d", xs, width, m_xsize );
		AfxMessageBox( mes );
		return 0;
	}
	if( ys + height> m_ysize ) {
		mes.Format( "Window Height Over 1 : %d %d %d", ys, height, m_ysize );
		AfxMessageBox( mes );
		return 0;
	}

	for( x=0; x<width; x++ ) {
		for( y=0; y<height; y++ ) {
			gsum += abs( image[y+ys][x+xs] - p->image[y+yy][x+xx] );
		}
	}
	return gsum;
}


//////////////////////////////////////////////////////////////////////////
//   合成用
//////////////////////////////////////////////////////////////////////////
void CImgPgm::UserProc1( CImgPgm *p1, CImgPgm *p2, CImgPgm *p3 )
{
	long v[4], xm, ym;
	v[0] = m_xsize;	v[1] = p1->m_xsize;	v[2] = p2->m_xsize;
	v[3] = p3->m_xsize;
	xm = find_min( v, 4 );
	v[0] = m_ysize; v[1] = p1->m_ysize; v[2] = p2->m_ysize;
	v[3] = p3->m_ysize;
	ym = find_min( v, 4 );
	for( int y=0; y<ym; y++ ) {
		for( int x=0; x<xm; x++ ) {
			image[y][x] = p1->image[y][x] + p2->image[y][x] + p3->image[y][x];
		}
	}
	m_SetFlag = TRUE;
}

void CImgPgm::UserProc2( CImgPgm *p1, CImgPgm *p2, CImgPgm *p3 )
{
	for( int y=0; y<m_ysize; y++ ) {
		for( int x=0; x<m_xsize; x++ ) {
//			image[y][x] = p1->image[y][x] + p2->image[y][x] + p3->image[y][x];
		}
	}
	m_SetFlag = TRUE;
}

void CImgPgm::UserProc3( CImgPgm *p1, CImgPgm *p2, CImgPgm *p3 )
{
	for( int y=0; y<m_ysize; y++ ) {
		for( int x=0; x<m_xsize; x++ ) {
//			image[y][x] = p1->image[y][x] + p2->image[y][x] + p3->image[y][x];
		}
	}
	m_SetFlag = TRUE;
}


void CImgPgm::UserProcColor1( int lm, CImgPgm *pblue, CImgPgm *pgreen, CImgPgm *pred )
{
//  入力データ 本体
//　出力データ　pblue, pgreen, pred
	int L = 255;
	unsigned char c;
	int g;

	g = m_max_gray;

	for( int y=0; y<m_ysize; y++ ) {
		for( int x=0; x<m_xsize; x++ ) {
			pred->image[y][x] = 0;
			pgreen->image[y][x] = 0;
			pblue->image[y][x] = 0;
			c = image[y][x];
			if( lm/2<c && c<=lm ) pred->image[y][x] = (unsigned char)(g * sin( PI*c/lm - PI/2 ));
			if( 0  <=c && c<=lm  ) pgreen->image[y][x] = (unsigned char)(g * sin(PI*c/lm) );
			if( 0  <=c && c<lm/2 ) pblue->image[y][x] = (unsigned char)(g * sin(PI*c/lm + PI/2 ));
		}
	}
}


void CImgPgm::UserProcColor2( int lm[], CImgPgm *p[] )
{
//  入力データ 本体
//　出力データ　p[3] : 0:Blue, 1:Green, 2:Red
	int L;
	unsigned char c;

	L = lm[0];
	if( L<0 || L>2 ) L=0;
	for( int y=0; y<m_ysize; y++ ) {
		for( int x=0; x<m_xsize; x++ ) {
			c = image[y][x];
			p[L]->image[y][x] = c;
		}
	}
}
