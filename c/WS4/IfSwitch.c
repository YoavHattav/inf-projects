#include <stdio.h>
#include <stdlib.h>


void IfElse()
{
	char ch=0;

	system("stty -icanon -echo");
	printf("If Else, Pls press A/T/esc-botton:\n");
	scanf("%c", &ch);

	if ('A' == ch)
	{
		printf("A was pressed\n");
	}
	else if ('T' == ch)
	{
		printf("T was pressed\n");
	}
	else if (27 == ch)
	{
		printf("exit program..\n");
		system("stty icanon echo");
		exit(0);
	}
	else
	{
		printf("Press A/T/esc next time.. bye!\n");
	}
	system("stty icanon echo");
}

void Switch()
{
	char ch=0;

	system("stty -icanon -echo");
	printf("Switch, Pls press A/T/esc-botton:\n");
	scanf("%c", &ch);

	switch (ch)
	{
		case 'A':
			printf("A was pressed\n");
			break;
		case 'T':
			printf("T was pressed\n");
			break;
		case (27):
			system("stty icanon echo");
			exit(0);
		default:
			printf("Press A/T/esc next time.. bye!\n");	
	}
	system("stty icanon echo");
}

int main()
{
	IfElse();
	Switch();
	return 0;
}