#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int*a = malloc(10);
	free(a);
	free(a);	// invalid memory free
	return 0;
}
