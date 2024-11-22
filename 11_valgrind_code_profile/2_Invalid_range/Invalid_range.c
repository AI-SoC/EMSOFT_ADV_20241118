#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
	fprintf( stderr, "OK!\n" );
	int* a = malloc(10);
	a[10] = 3;	// Memory pointed out of range
	free(a);
	return 0;
}

