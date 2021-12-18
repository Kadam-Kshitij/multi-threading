#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

const int count = 12;
pthread_barrier_t tb;
pthread_t th[12];

void* foo( void* x )
{
	int* id = ( int* )x;
	printf( "Thread %d started ++++++++++++\n", *id );
	sleep( *id );
	printf( "Thread %d done with sleep ------------\n", *id );
	pthread_barrier_wait( &tb );
	printf( "Thread %d crossed the barrier ===============\n", *id );
}

int main()
{
	pthread_barrier_init( &tb, NULL, 4 );

	int* id = malloc( count * sizeof( int ) );

	for( int i = 0; i < count; ++i )
	{
		*( id + i ) = i;
		pthread_create( &th[i], NULL, foo, ( void* )( id + i ) );
	}

	pthread_join( th[count -1], NULL );

	pthread_barrier_destroy( &tb );
	free( id );
}