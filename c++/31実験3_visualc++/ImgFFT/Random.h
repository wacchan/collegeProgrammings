#pragma once


//		������seed�����ݎ����ŏ���������D
void randomize();

//		[0,1) �̈�l�����𔭐�����D
double rand_u();

//		0 ���� n-1 �܂ł̐��������𔭐�����D
int rand_i( int n );

//		[-w/2, +w/2) �̈�l�����𔭐�����D
int rand_ui( int w );

//		���K���z�i���� 0 ���U 1 �̃K�E�X���z�j�ɏ]�������𔭐�����D
double rand_n2();

