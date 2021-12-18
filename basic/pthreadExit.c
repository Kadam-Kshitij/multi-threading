#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* hoo( void* x )
{
	printf("Starting thread 3 +++++++ %d\n", getpid() );

	int i = 40;
	while( i > 0 )
	{
		sleep(1);
		printf( "Thread 3 running\n" );
		--i;
	}

	printf("Ending thread 3 --------\n");
}


void* goo( void* x )
{
	printf("Starting thread 2 +++++++ %d\n", getpid() );
	pthread_t th2;
	pthread_create( &th2, NULL, hoo, NULL );

	int i = 30;
	while( i > 0 )
	{
		sleep(1);
		printf( "Thread 2 running\n" );
		--i;
	}

	printf("Ending thread 2 --------\n");
}

void* foo( void* x )
{
	printf("Starting thread 1 +++++++ %d\n", getpid() );
	pthread_t th1;
	pthread_create( &th1, NULL, goo, NULL );

	int i = 20;
	while( i > 0 )
	{
		sleep(1);
		printf( "Thread 1 running\n" );
		--i;
	}

	printf("Ending thread 1 --------\n");
	pthread_exit(0);
}

int main()
{
	printf("Starting thread main +++++++ %d\n", getpid() );
	pthread_t th;

	pthread_create( &th, NULL, foo, NULL );

	sleep(10);
	printf("Ending thread main --------\n");
	pthread_exit(0);
}