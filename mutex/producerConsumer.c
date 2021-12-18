#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int size = 5;
struct Data
{
	int arr[5];
	int pointer;
	pthread_mutex_t mu;
};

void initData( struct Data* d )
{
	d->pointer = -1;
	pthread_mutex_init( &( d->mu ), NULL );
}

void* consumer( void* x )
{
	struct Data* d = ( struct Data* )x;
	while(1)
	{
		pthread_mutex_lock( &( d->mu ) );
		if ( -1 != d->pointer )
		{
			int i = 0;
			printf( "Elements - " );
			while ( i != d->pointer + 1 )
			{
				printf( "%d ", d->arr[i] );
				++i;
			}
			d->pointer = -1;
			printf( "\n" );
		}
		pthread_mutex_unlock( &( d->mu ) );

	}
}

void* producer( void* x )
{
	struct Data* d = ( struct Data* )x;
	while(1)
	{
		pthread_mutex_lock( &( d->mu ) );
		int val;
		while( ( size - 1 ) != d->pointer )
		{
			printf( "Enter number : " );
			scanf( "%d", &val );
			d->arr[d->pointer+1] = val;
			++( d->pointer );
		}
		pthread_mutex_unlock( &( d->mu ) );
	}
}


int main()
{
	struct Data* d = malloc( sizeof( struct Data ) );
	initData( d );

	pthread_t thp, thc;

	pthread_create( &thp, NULL, producer, ( void* )d );
	pthread_create( &thc, NULL, consumer, ( void* )d );

	pthread_exit(0);
}