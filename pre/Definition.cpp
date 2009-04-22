#include ".\Definition.h"

#include <fstream>

#include <uf.h>

//! Error Report Function
int report_error( char *file, int line, char *call, int irc)
{
    if (irc)
    {
        char err[133];
        UF_get_fail_message(irc, err);
        fprintf(stderr, "\n%s\nerror %d at line %d in %s\n%s\n",
            err, irc, line, file, call);
    }
    return(irc);
}


// ValRndPnt function make small value 3D Point zero
void ValRndPnt(double C[3])
{
	int size = 3;
    for (int i = 0 ; i<size ; ++i) C[i] = ValRnd(C[i]);
}
// make a value 0 that is near to 0.
double ValRnd(double tmp)
{
	if (abs(tmp) < 0.000001) return 0.0;
	else if (tmp>0)
	{
		unsigned int temN = (unsigned int)tmp;
		if ((tmp-(double)temN) < 0.000001) return (double)temN;
		else if ( ((double)temN+1.0-tmp) < 0.000001 ) return (double)(temN+1);
	}
	else if(tmp<0)
	{
		long int tmpN = (long int)tmp;
		if (((double)tmpN-tmp) < 0.000001) return (double)tmpN;
		else if ((tmp-(double)tmpN+1.0) < 0.000001) return (double)(tmpN-1);
	}
	return tmp;
}

// ValRndPnt function make small value 3D Point zero
void ValRndPnt6(double C[3])
{
	int size = 3;
    for (int i = 0 ; i<size ; ++i) C[i] = ValRnd6(C[i]);
}
// make a value 0 that is near to 0.
double ValRnd6(double tmp)
{
	double under = tmp - (int)tmp;
	long ui = (long)(under*1000000);
	tmp = double( (int)tmp + ((double)ui)*0.000001 );
	return tmp;
}

int WaitGetEnter(void)
{
	char c;	scanf("%c", &c);
	return c;
}

// Map function
// Translate a Point from the world coordinate to the local coordinate
void Map(const double A[12],double B[3])
{
	double C[3];
	double D[3];

	D[0]=A[0]*A[9]+A[1]*A[10]+A[2]*A[11];
	D[1]=A[3]*A[9]+A[4]*A[10]+A[5]*A[11];
	D[2]=A[6]*A[9]+A[7]*A[10]+A[8]*A[11];

	C[0]=A[0]*B[0]+A[1]*B[1]+A[2]*B[2]-D[0];
	C[1]=A[3]*B[0]+A[4]*B[1]+A[5]*B[2]-D[1];
	C[2]=A[6]*B[0]+A[7]*B[1]+A[8]*B[2]-D[2];

	ValRndPnt(C);	// 절대값 1*e-6 이하 값은 0으로 처리

	B[0]=C[0];
	B[1]=C[1];
	B[2]=C[2];
}

// Cir_Map Function
// Translate a arc_center from the world coordinate to the local coordinate
void Cir_Map ( const double A[12], double Center[3] )
{
	double D[3];
	
	D[0]=A[0]*A[9]+A[1]*A[10]+A[2]*A[11];
	D[1]=A[3]*A[9]+A[4]*A[10]+A[5]*A[11];
	D[2]=A[6]*A[9]+A[7]*A[10]+A[8]*A[11];

	Center[0] = Center[0] - D[0];
	Center[1] = Center[1] - D[1];
	Center[2] = Center[2] - D[2];

	ValRndPnt(Center);
}
