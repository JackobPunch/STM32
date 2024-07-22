#include <stdio.h>

int main ()
{
	char a=100;
	printf("Address of a is %p\n", &a);
	char* p_a=&a;
	printf("%d\n",*p_a);
	*p_a=65;
	printf("%d\n",a);
}

