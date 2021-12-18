#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t cv;
pthread_mutex_t mu;
int global = 1;

void* goo( void* x )
{
	int* id = ( int* )x;

	pthread_mutex_lock( &mu );
	while( 1 == global )
	{
		pthread_cond_wait( &cv, &mu );
	}

	printf( "GOO %d condition satisfied\n", *id );
	sleep(1);
	printf( "GOO %d exit\n", *id );
	pthread_mutex_unlock( &mu );
}

void* foo( void* x )
{
	sleep(1);
	pthread_mutex_lock( &mu );
	printf( "FOO\n" );
	sleep(2);
	global = 20;
	//pthread_cond_broadcast( &cv );
	pthread_cond_signal( &cv );
	pthread_cond_signal( &cv );
	pthread_mutex_unlock( &mu );
}

int main()
{
	pthread_cond_init( &cv, NULL );
	pthread_mutex_init( &mu, NULL );
	
	pthread_t th1, th2, th3;
	int id[2] = {1,2};
	pthread_create( &th1, NULL, foo, NULL );
	pthread_create( &th2, NULL, goo, &id[0] );
	pthread_create( &th3, NULL, goo, &id[1] );

	pthread_join( th1, NULL );
	pthread_join( th2, NULL );
	pthread_join( th3, NULL );
}