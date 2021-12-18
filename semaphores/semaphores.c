#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

sem_t sem;
pthread_t th[10];

void* foo( void* x )
{
	int* id = ( int* )x;
	sem_wait( &sem );
	printf( "Thread %d created ++++++++++++\n", *id );
	for ( int i = 0; i < 3; ++i )
	{
		printf("Thread %d : %d\n", *id, i );
		sleep(1);
	}
	printf( "Thread %d destroyed ------------\n", *id );
	sem_post( &sem );
}

int main()
{
	sem_init( &sem, 0, 4 );

	int* id = malloc( 10 * sizeof( int ) );

	for( int i = 0; i < 10; ++i )
	{
		*( id + i ) = i;
		pthread_create( &th[i], NULL, foo, ( void* )( id + i ) );
	}

	pthread_join( th[9], NULL );

	sem_destroy( &sem );
	free( id );
}