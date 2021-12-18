#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mu;

void* foo( void* x )
{
	pthread_mutex_lock( &mu );
	int i = 10;
	while( i > 0 )
	{
		sleep(1);
		printf( "%d\n", i );
		--i;
	}
	pthread_mutex_unlock( &mu );
}

int main()
{
	pthread_mutex_init( &mu, NULL );
	pthread_t th[2];

	pthread_create( &th[0], NULL, foo, NULL );
	pthread_create( &th[1], NULL, foo, NULL );

	pthread_join( th[0], NULL );
	pthread_join( th[1], NULL );

	pthread_mutex_destroy( &mu );
}