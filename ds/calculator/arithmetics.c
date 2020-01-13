#include <stdio.h>
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
	return pow(*data1,*data2);
}

int main()
{
	double first = 2.5, second = 3.7;

	printf("%f\n", PlusActionFunc(&first, &second));
		
	printf("%f\n", MinusActionFunc(&first, &second));

	printf("%f\n", MultiActionFunc(&first, &second));

	printf("%f\n", DivideActionFunc(&first, &second));

	printf("%f\n", POWActionFunc(&first, &second));

	return 0;
}