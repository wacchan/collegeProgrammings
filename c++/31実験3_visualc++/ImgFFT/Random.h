#pragma once


//		乱数のseedを現在時刻で初期化する．
void randomize();

//		[0,1) の一様乱数を発生する．
double rand_u();

//		0 から n-1 までの整数乱数を発生する．
int rand_i( int n );

//		[-w/2, +w/2) の一様乱数を発生する．
int rand_ui( int w );

//		正規分布（平均 0 分散 1 のガウス分布）に従う乱数を発生する．
double rand_n2();

