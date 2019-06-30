#include <stdafx.h>

#include "Utility_ImgProc.h"


void  make_histogram( CImgPgm *data_a, CImgPgm *data_b )
{
long int histogram[256]; /* ヒストグラム用配列 */
long int max_frequency; /* 頻度の最大値 */
int i, j, x, y;			/* 制御変数 */
int data;				/* 頻度を表すグラフの長さ */

int Gray_Level = 256;   /* = GRAYLEVEL */

int	x_s, y_s, x_s2, y_s2;

	x_s = data_a->m_xsize;
	y_s = data_a->m_ysize;
	Gray_Level = data_a->m_max_gray+1;

    /* 原画像のヒストグラムを求める */
	for ( i = 0; i < Gray_Level; i ++ )	histogram[ i ] = 0;
    for ( y = 0; y < y_s; y++ )	{
        for ( x = 0; x < x_s; x++ )	{
            histogram[ data_a->image[y][x] ] ++;
		}
	}

    /* 頻度の最大値を求める */
	max_frequency = find_max( histogram, Gray_Level );

	CString msg;
	msg.Format( "頻度の最大値 = %d\n", max_frequency);
	AfxMessageBox( msg );

    /* ヒストグラム画像を image2 に代入 */
	x_s2 = Gray_Level;
    y_s2 = Gray_Level;

    for ( y = 0; y < y_s2; y ++ ) {
        for ( x = 0; x < x_s2; x ++ ) {
			data_b->image[y][x] = 0;
		}
	}
    for ( i = 0; i < Gray_Level; i ++ ){
        data = (int)( MAX_BRIGHTNESS / 
            (double)max_frequency * (double)histogram[i] );
        for ( j = 0; j < data; j ++ )
            data_b->image[Gray_Level-1-j][i] = MAX_BRIGHTNESS;
		if (i % 50 == 0)
			for (j = 0; j<Gray_Level; j++)
				if (j % 5 == 0) data_b->image[j][i] = MAX_BRIGHTNESS;
    }
}


int	find_max( long vec[], int num )
{
int	max_frequency;

    max_frequency = 0;
	for( int i=0; i<num; i++ )
	{
		if ( vec[i] > max_frequency ) 
		{
			max_frequency = vec[i];
		}
	}
	return max_frequency;
}

/* Hilditch の細線化のプログラム thinning.c */
int func_nc8( int *b )
/* 注目画素の連結度（４連結）を求める関数 */
{
    int n_odd[4] = { 1, 3, 5, 7 }; /* 奇数の近傍番号 */
    int i, j, sum, d[10]; /* 制御変数，計算途中を代入する変数 */
    
    for ( i = 0; i <= 9; i ++ ){
        j = i;    if (i==9) j = 1;
        if ( abs( *( b + j ) ) == 1 ) d[i] = 1;
        else d[i] = 0;
    }
    sum = 0;
    for ( i = 0; i < 4; i ++ ){
        j = n_odd[i];
        //sum = sum + d[j] - d[j] * d[j+1] * d[j+2];
		sum = sum + (1-d[j]) - (1-d[j]) * (1-d[j+1]) * (1-d[j+2]);//2012年修正
    }
    return( sum );
}


void thinning( CImgPgm *data_a, CImgPgm *data_b  )
/* ２値画像の細線化処理(image2[y][x] を最初は作業領域として使う)*/
/* （  = MAX_BRIGHTNESS --> 1, GRAY --> -1, 0 --> 0 とみなす）  */
/* 原画像image1[y][x] ===> 処理後の画像image2[y][x]             */
{
    int offset[9][2] = {{0,0},{1,0},{1,-1},{0,-1},{-1,-1},
           {-1,0},{-1,1},{0,1},{1,1} }; /* 近傍画素へのオフセット値 */
    int n_odd[4] = { 1, 3, 5, 7 };      /* 近傍番号（奇数）         */
    int px, py;                         /* 近傍画素の(x,y)絶対座標  */
    int b[9];                           /* 自分を含む９近傍の値     */
    int condition[6];               /* 条件１～６：=1のとき“成立” */
    int counter;                    /* ラベルに変化が生じた画素の数 */
    int i, x, y, copy, sum;         /* 制御変数など                 */
    int path;                       /* 画像の走査回数を表す変数     */

	int	x_size1, y_size1;

	int Gray = 128;

    /* 作業配列の初期化 */
	x_size1 = data_a->m_xsize;
	y_size1 = data_a->m_ysize;

	data_b->CopyImage( data_a );

    /* 処理開始 */
    path = 1;
    do {
        counter = 0;
        for ( y = 0; y < y_size1; y ++ ){
            for ( x = 0; x < x_size1; x ++ ){
                /* (x,y)を含む９近傍にデータを代入する */
                for ( i = 0; i < 9; i ++ ){
                    b[i] = 0;
                    px = x + offset[i][0];    py = y + offset[i][1];
                    if ( px >= 0 && px < x_size1 && 
                         py >= 0 && py < y_size1 )
                         if ( data_b->image[py][px] == MAX_BRIGHTNESS )
                             b[i] = 1; 
                         else if ( data_b->image[py][px] == Gray ) b[i] = -1;
                }
                for ( i = 0; i < 6; i ++ ) condition[i] = 0;
                
                /* 条件１：図形画素である */
                if ( b[0] == 1 ) condition[0] = 1;
                
                /* 条件２：境界点である */
                sum = 0;
                for ( i = 0; i < 4; i ++ )
                    sum = sum + 1 - abs( b[ n_odd[i] ] );
                if ( sum >= 1 ) condition[1] = 1;
                
                /* 条件３：端点を除去しない */
                sum = 0;
                for ( i = 1; i <= 8; i ++ )
                    sum = sum + abs( b[i] );
                if ( sum >= 2 ) condition[2] = 1;
                
                /* 条件４：孤立点を保存する */
                sum = 0;
                for ( i = 1; i <= 8; i ++ )
                    if ( b[i] == 1 ) sum++;
                if ( sum >= 1 ) condition[3] = 1;
                
                /* 条件５：連結性を保存する */
                if ( func_nc8( b ) == 1 ) condition[4] = 1;
                
                /* 条件６：線幅２の線分の片側だけを削除する */
                sum = 0;
                for ( i = 1; i <= 8; i ++ )
                    if ( b[i] != -1 ) sum ++;
                    else {
                        copy = b[i];    
                        b[i] = 0;
                        if ( func_nc8( b ) == 1 ) sum ++;
                        b[i] = copy;
                    }
                if ( sum == 8 ) condition[5] = 1;
                
                /* 最終判定 */
                if ( condition[0] && condition[1] && condition[2] &&
                     condition[3] && condition[4] && condition[5] ){
                    data_b->image[y][x] = Gray; /* = -1 を表している */
                    counter ++;
                }
            } /* end of x */
        } /* end of y */
        if ( counter != 0 ){
            for ( y=0; y<y_size1; y++)
                for ( x=0; x<x_size1; x++)
                    if ( data_b->image[y][x] == Gray ) data_b->image[y][x] = 0;
        }
        path ++;
    } while ( counter != 0 );
}
