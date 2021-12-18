#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* foo( void* x )
{
	int* num = ( int* )x;
	int* sum = malloc( sizeof( int ) );
	*sum = 0;
	while( *num > 0 )
	{
		*sum += *num;
		*num -= 1;
	}
	printf( "Return\n" );
	printf( "%d\n", *sum );
	return ( void* )sum;
}

int main()
{
	pthread_t th;

	int* num = malloc( sizeof( int ) );
	*num = 10;
	pthread_create( &th, NULL, foo, ( void* )num );

	int** ret;
	pthread_join( th, ( void* )ret );
	printf( "Answer = %d \n", **( ret ) );

	free( *ret );
}