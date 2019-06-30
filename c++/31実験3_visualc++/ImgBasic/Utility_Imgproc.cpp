#include <stdafx.h>

#include "Utility_ImgProc.h"


void  make_histogram( CImgPgm *data_a, CImgPgm *data_b )
{
long int histogram[256]; /* �q�X�g�O�����p�z�� */
long int max_frequency; /* �p�x�̍ő�l */
int i, j, x, y;			/* ����ϐ� */
int data;				/* �p�x��\���O���t�̒��� */

int Gray_Level = 256;   /* = GRAYLEVEL */

int	x_s, y_s, x_s2, y_s2;

	x_s = data_a->m_xsize;
	y_s = data_a->m_ysize;
	Gray_Level = data_a->m_max_gray+1;

    /* ���摜�̃q�X�g�O���������߂� */
	for ( i = 0; i < Gray_Level; i ++ )	histogram[ i ] = 0;
    for ( y = 0; y < y_s; y++ )	{
        for ( x = 0; x < x_s; x++ )	{
            histogram[ data_a->image[y][x] ] ++;
		}
	}

    /* �p�x�̍ő�l�����߂� */
	max_frequency = find_max( histogram, Gray_Level );

	CString msg;
	msg.Format( "�p�x�̍ő�l = %d\n", max_frequency);
	AfxMessageBox( msg );

    /* �q�X�g�O�����摜�� image2 �ɑ�� */
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

/* Hilditch �̍א����̃v���O���� thinning.c */
int func_nc8( int *b )
/* ���ډ�f�̘A���x�i�S�A���j�����߂�֐� */
{
    int n_odd[4] = { 1, 3, 5, 7 }; /* ��̋ߖT�ԍ� */
    int i, j, sum, d[10]; /* ����ϐ��C�v�Z�r����������ϐ� */
    
    for ( i = 0; i <= 9; i ++ ){
        j = i;    if (i==9) j = 1;
        if ( abs( *( b + j ) ) == 1 ) d[i] = 1;
        else d[i] = 0;
    }
    sum = 0;
    for ( i = 0; i < 4; i ++ ){
        j = n_odd[i];
        //sum = sum + d[j] - d[j] * d[j+1] * d[j+2];
		sum = sum + (1-d[j]) - (1-d[j]) * (1-d[j+1]) * (1-d[j+2]);//2012�N�C��
    }
    return( sum );
}


void thinning( CImgPgm *data_a, CImgPgm *data_b  )
/* �Q�l�摜�̍א�������(image2[y][x] ���ŏ��͍�Ɨ̈�Ƃ��Ďg��)*/
/* �i  = MAX_BRIGHTNESS --> 1, GRAY --> -1, 0 --> 0 �Ƃ݂Ȃ��j  */
/* ���摜image1[y][x] ===> ������̉摜image2[y][x]             */
{
    int offset[9][2] = {{0,0},{1,0},{1,-1},{0,-1},{-1,-1},
           {-1,0},{-1,1},{0,1},{1,1} }; /* �ߖT��f�ւ̃I�t�Z�b�g�l */
    int n_odd[4] = { 1, 3, 5, 7 };      /* �ߖT�ԍ��i��j         */
    int px, py;                         /* �ߖT��f��(x,y)��΍��W  */
    int b[9];                           /* �������܂ނX�ߖT�̒l     */
    int condition[6];               /* �����P�`�U�F=1�̂Ƃ��g�����h */
    int counter;                    /* ���x���ɕω�����������f�̐� */
    int i, x, y, copy, sum;         /* ����ϐ��Ȃ�                 */
    int path;                       /* �摜�̑����񐔂�\���ϐ�     */

	int	x_size1, y_size1;

	int Gray = 128;

    /* ��Ɣz��̏����� */
	x_size1 = data_a->m_xsize;
	y_size1 = data_a->m_ysize;

	data_b->CopyImage( data_a );

    /* �����J�n */
    path = 1;
    do {
        counter = 0;
        for ( y = 0; y < y_size1; y ++ ){
            for ( x = 0; x < x_size1; x ++ ){
                /* (x,y)���܂ނX�ߖT�Ƀf�[�^�������� */
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
                
                /* �����P�F�}�`��f�ł��� */
                if ( b[0] == 1 ) condition[0] = 1;
                
                /* �����Q�F���E�_�ł��� */
                sum = 0;
                for ( i = 0; i < 4; i ++ )
                    sum = sum + 1 - abs( b[ n_odd[i] ] );
                if ( sum >= 1 ) condition[1] = 1;
                
                /* �����R�F�[�_���������Ȃ� */
                sum = 0;
                for ( i = 1; i <= 8; i ++ )
                    sum = sum + abs( b[i] );
                if ( sum >= 2 ) condition[2] = 1;
                
                /* �����S�F�Ǘ��_��ۑ����� */
                sum = 0;
                for ( i = 1; i <= 8; i ++ )
                    if ( b[i] == 1 ) sum++;
                if ( sum >= 1 ) condition[3] = 1;
                
                /* �����T�F�A������ۑ����� */
                if ( func_nc8( b ) == 1 ) condition[4] = 1;
                
                /* �����U�F�����Q�̐����̕Б��������폜���� */
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
                
                /* �ŏI���� */
                if ( condition[0] && condition[1] && condition[2] &&
                     condition[3] && condition[4] && condition[5] ){
                    data_b->image[y][x] = Gray; /* = -1 ��\���Ă��� */
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
