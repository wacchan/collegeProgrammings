// Complex.cpp: CComplex クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ImgProc.h"
#include "Complex.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CComplex::CComplex()
{
	real = 0.0;
	imag = 0.0;
}

CComplex::CComplex( double x, double y )
{
	real = x;
	imag = y;

}

CComplex::~CComplex()
{

}

/////////////////////////////////////////////////////
//    operator +
/////////////////////////////////////////////////////
CComplex	CComplex::operator+( CComplex &other )
{	
	return CComplex( real+other.real, imag+other.imag ); 
};

CComplex	operator+( int first, CComplex &second )
{	
	return CComplex( first+second.real, second.imag );	
};

CComplex	operator+( float first, CComplex &second )
{	
	return CComplex( first+second.real, second.imag );	
};

CComplex	operator+( double first, CComplex &second )
{	
	return CComplex( first+second.real, second.imag );	
}

CComplex	operator+( CComplex &first, int second )
{	return CComplex( first.real+second, first.imag );	}

CComplex	operator+( CComplex &first, float second )
{	return CComplex( first.real+second, first.imag );	}

CComplex	operator+( CComplex &first, double second )
{	return CComplex( first.real+second, first.imag );	}

/////////////////////////////////////////////////////
//    operator -
/////////////////////////////////////////////////////
CComplex	CComplex::operator-( CComplex &other )
{	return CComplex( real-other.real, imag-other.imag ); };

CComplex	operator-( int first, CComplex &second )
{	return CComplex( first-second.real, -second.imag );	};

CComplex	operator-( float first, CComplex &second )
{	return CComplex( first-second.real, -second.imag );	};

CComplex	operator-( double first, CComplex &second )
{	return CComplex( first-second.real, -second.imag );	}

CComplex	operator-( CComplex &first, int second )
{	return CComplex( first.real-second, first.imag );	}

CComplex	operator-( CComplex &first, float second )
{	return CComplex( first.real-second, first.imag );	}

CComplex	operator-( CComplex &first, double second )
{	return CComplex( first.real-second, first.imag );	}

/////////////////////////////////////////////////////
//    operator *
/////////////////////////////////////////////////////
CComplex	CComplex::operator*( CComplex &other )
{
double	re, im;
	re = real * other.real - imag * other.imag;
	im = real * other.imag + imag * other.real;
	return	CComplex( re, im );
}

CComplex	operator*( int first, CComplex &second )
{	return CComplex( first*second.real, first*second.imag );	};

CComplex	operator*( float first, CComplex &second )
{	return CComplex( first*second.real, first*second.imag );	};

CComplex	operator*( double first, CComplex &second )
{	return CComplex( first*second.real, first*second.imag );	}

CComplex	operator*( CComplex &first, int second )
{	return CComplex( first.real*second, first.imag*second );	}

CComplex	operator*( CComplex &first, float second )
{	return CComplex( first.real*second, first.imag*second );	}

CComplex	operator*( CComplex &first, double second )
{	return CComplex( first.real*second, first.imag*second );	}


/////////////////////////////////////////////////////
//    operator /
/////////////////////////////////////////////////////
CComplex	CComplex::operator/( CComplex &other )
{
double	a;
CComplex other_temp, b;

	other_temp.real = other.real;
	other_temp.imag = -other.imag;
	a = other.abs();
	b = *this * other_temp;
	b.real /= a;
	b.imag /= a;
	return b;
//	return	CComplex( first.real/(double)n, first.imag/(double)n );
}

CComplex	operator/( CComplex &first, int n )
{
	return	CComplex( first.real/(double)n, first.imag/(double)n );
}

CComplex	operator/( CComplex &first, float n )
{
	return	CComplex( first.real/(double)n, first.imag/(double)n );
}

CComplex	operator/( CComplex &first, double n )
{
	return	CComplex( first.real/n, first.imag/n );
}

double CComplex::abs()
{
	return sqrt( real*real + imag*imag );
}


//////////////////////////////////////////////////
CCompMat::CCompMat()
{
	x_s = 0;
	y_s = 0;
	mat = NULL;
}

CCompMat::CCompMat( int x, int y )
{
	Create( x, y );
}

CCompMat::~CCompMat()
{
	if( mat != NULL ) {
		for( int i=0; i<x_s; i++ ) {
			delete [] mat[i];
		}
		delete mat;
	}
}

void CCompMat::Create( int x, int y )
{
	x_s = x;
	y_s = y;
	mat = new CComplex *[x];
	for( int i=0; i<x; i++ ) {
		mat[i] = new CComplex[y];
	}
}

void CCompMat::CopyCMat( CCompMat *m )
{
	int xs, ys;
	xs = m->x_s;
	ys = m->y_s;
	Create( xs, ys );
	for( int i=0; i<xs; i++ ) {
		memcpy( mat[i], m->mat[i], ys*sizeof(CComplex) );
	}
}

