#include <stdio.h>
#include <stddef.h>

void DataSize()
{
printf("int %d\n", sizeof(int));
printf("char %d\n", sizeof(char));
printf("float %d\n", sizeof(float));
printf("double %d\n", sizeof(double));
printf("long double %ld\n", sizeof(long double));
printf("unsigned int %u\n", sizeof(unsigned int));
printf("unsigned char %d\n", sizeof(unsigned char));
printf("signed char %d\n", sizeof(signed char));
printf("short %d\n", sizeof(short));
printf("unsigned short %d\n", sizeof(unsigned short));
printf("long %ld\n", sizeof(long));
printf("unsigned long %lu\n", sizeof(unsigned long));
}
