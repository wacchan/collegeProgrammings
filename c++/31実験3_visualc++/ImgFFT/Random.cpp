
#include <StdAfx.h>

#include	<stdlib.h>
#include	<math.h>
#include	<time.h>
#include	"Random.h"

//#define	PI	3.141592654


double rand_u()
{
	return rand() / ( (double)(RAND_MAX) + 1 );
}


int rand_i( int n )
{
	return rand() % n;
}


int rand_ui( int w ) 
{
	return (int)( (rand_u() - 0.5 ) * w ) ;
}


void randomize()
{
   srand( (unsigned)time( NULL ) );
}

double rand_n2()
{
	static int sw=0;
	static double save;
	register double t,u;
	
	if( sw =! sw ) {
		t = sqrt( -2.0 * log(1.0 - rand_u()) );
		u = 2.0 * PI * rand_u();
		save = t * sin(u);
		return( t * cos(u) );
	} else {
		return( save );
	}
}
