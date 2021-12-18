#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t cv;
pthread_mutex_t mu;
int global = 0;

void* goo( void* x )
{
	int* id = ( int* )x;
	while(1)
	{
		pthread_mutex_lock( &mu );
		while( global == 0 )
		{
			pthread_cond_wait( &cv, &mu );
		}

		global -= 15;
		printf( "GOO %d - %d\n", *id, global );
		sleep(1);
		pthread_mutex_unlock( &mu );
	}
}

void* foo( void* x )
{
	while(1)
	{
		pthread_mutex_lock( &mu );
		global += 15;
		printf( "FOO - %d\n", global );
		sleep(1);
		pthread_cond_signal( &cv );
		pthread_mutex_unlock( &mu );
		sleep(1);
	}
}

int main()
{
	pthread_mutex_init( &mu, NULL );
	pthread_cond_init( &cv, NULL );

	pthread_t th1, th2, th3, th4;	
	int id[3] = { 1, 2, 3 };
	pthread_create( &th1, NULL, foo, NULL );
	pthread_create( &th2, NULL, goo, &id[0] );
	pthread_create( &th3, NULL, goo, &id[1] );
	pthread_create( &th4, NULL, goo, &id[2] );	

	pthread_join( th1, NULL );
	pthread_join( th2, NULL );

	pthread_cond_destroy( &cv );
}