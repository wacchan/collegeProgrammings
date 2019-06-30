// Complex.h: CComplex クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPLEX_H__484FAD8A_1669_49BB_8CF1_C48DEF91E63D__INCLUDED_)
#define AFX_COMPLEX_H__484FAD8A_1669_49BB_8CF1_C48DEF91E63D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CComplex  
{
public:
	CComplex();
	CComplex( double x, double y );
	virtual ~CComplex();

	double abs();
	double imag;
	double real;

	CComplex operator			+	( CComplex &other );
	friend CComplex operator	+	( int first, CComplex &second );
	friend CComplex operator	+	( float first, CComplex &second );
	friend CComplex operator	+	( double first, CComplex &second );
	friend CComplex operator	+	( CComplex &first, int    second );
	friend CComplex operator	+	( CComplex &first, float  second );
	friend CComplex operator	+	( CComplex &first, double second );

	CComplex operator			-	( CComplex &other );
	friend CComplex operator	-	( int    first, CComplex &second );
	friend CComplex operator	-	( float  first, CComplex &second );
	friend CComplex operator	-	( double first, CComplex &second );
	friend CComplex operator	-	( CComplex &first, int    second );
	friend CComplex operator	-	( CComplex &first, float  second );
	friend CComplex operator	-	( CComplex &first, double second );

	CComplex operator			*   ( CComplex &other );
	friend CComplex operator	*	( int    first, CComplex &second );
	friend CComplex operator	*	( float  first, CComplex &second );
	friend CComplex operator	*	( double first, CComplex &second );
	friend CComplex operator	*	( CComplex &first, int    second );
	friend CComplex operator	*	( CComplex &first, float  second );
	friend CComplex operator	*	( CComplex &first, double second );

	CComplex operator			/	( CComplex &other );
	friend CComplex operator	/	( CComplex &first, int n );
	friend CComplex operator	/	( CComplex &first, float n );
	friend CComplex operator	/	( CComplex &first, double n );

//	CComplex operator=( CComplex &other );

};


class CCompMat  
{
public:
	CCompMat();
	CCompMat( int x, int y );
	void Create(   int x, int y );
	virtual ~CCompMat();
	void CopyCMat( CCompMat *m );

	int x_s;
	int y_s;
	CComplex **mat;

};


#endif // !defined(AFX_COMPLEX_H__484FAD8A_1669_49BB_8CF1_C48DEF91E63D__INCLUDED_)
