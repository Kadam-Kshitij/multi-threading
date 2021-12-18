#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t zs1, zs2;
pthread_t th1, th2;

void* printEven( void* v )
{
	int num = 2;

	while( num < 21 )
	{
		sem_wait( &zs1 );
		printf( "%d\n", num );
		num += 2;
		sem_post( &zs2 );
	}
}

void* printOdd( void* v )
{
	int num = 1;

	while( num < 21 )
	{
		printf( "%d\n", num );
		num += 2;
		sem_post( &zs1 );
		sem_wait( &zs2 );
	}
}

int main()
{
	sem_init( &zs1, 0, 0 );
	sem_init( &zs2, 0, 0 );

	pthread_create( &th1, NULL, printEven, NULL );
	pthread_create( &th2, NULL, printOdd, NULL );

	pthread_join( th1, NULL );
	pthread_join( th2, NULL );

	sem_destroy( &zs1 );
	sem_destroy( &zs2 );
	
	printf( "%s\n", "End of program" );
}