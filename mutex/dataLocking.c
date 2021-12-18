#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

struct Demo
{
	int val;
	pthread_mutex_t mu;
};

void* foo( void* x )
{
	struct Demo* d = ( struct Demo* )x;

	pthread_mutex_lock( &( d->mu ) );
	printf( "Inside lock\n" );
	++( d->val );
	printf( "Value = %d\n", d->val );
	sleep(4);
	printf( "Sleep over\n" );
	pthread_mutex_unlock( &( d->mu ) );
}

int main()
{
	struct Demo* d1 = malloc( sizeof( struct Demo ) );
	struct Demo* d2 = malloc( sizeof( struct Demo ) );;
	d1->val = 0;
	pthread_mutex_init( &( d1->mu ), NULL );
	d2->val = 10;
	pthread_mutex_init( &( d2->mu ), NULL );

	pthread_t th[4];
	pthread_create( &th[0], NULL, foo, ( void* )d1 );
	pthread_create( &th[1], NULL, foo, ( void* )d2 );

	pthread_join( th[0], NULL );
	pthread_join( th[1], NULL );

	pthread_create( &th[2], NULL, foo, ( void* )d1 );
	pthread_create( &th[3], NULL, foo, ( void* )d1 );

	pthread_join( th[2], NULL );
	pthread_join( th[3], NULL );

	pthread_mutex_destroy( &( d1->mu ) );
	pthread_mutex_destroy( &( d2->mu ) );
}