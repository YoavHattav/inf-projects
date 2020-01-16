#include <math.h>


double PlusActionFunc(double *data1, double *data2)
{
	return (*data1 + *data2);
}

double MinusActionFunc(double *data1, double *data2)
{
	return (*data1 - *data2);
}

double MultiActionFunc(double *data1, double *data2)
{
	return (*data1 * *data2);
}

double DivideActionFunc(double *data1, double *data2)
{
	return (*data1 / *data2);
}

double POWActionFunc(double *data1, double *data2)
{
	return pow(*data1, *data2);
}
