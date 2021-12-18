Multi-Threading C/C++

============== Pthreads ==============
API -
pthread_t 
pthread_create( pthread_t*, const pthread_attr_t*, <function>, (void*) );
pthread_join( pthread_t, void** );

Function handeling the thread - void* foo( void* )
Need to convert pointers to void type before sending and getting.



============== Semaphores ==============
API -
sem_t
sem_init( sem_t*, int pshared, unsigned int count ); 	// Here pshread = 0. If not zero then semaphore can
														// be shared between processes.
sem_wait( sem_t* );
sem_post( sem_t* );
sem_destroy( sem_t* );

Zero-semaphores -
Here count is initialized to zero. ( sem_init( &s, 0, 0 ); )
Use for strict alteration between two threads.

Binary semaphores -
Count = 1. So it allows only one thread to execute the critical section at a time.
So it can be called as a mutex.

Counting semaphores -
Here count > 1. Allows multiple threads to eecute within the critical section.




============== Thread Barrier ==============
API -
pthread_barrier_t
pthread_barrier_init( pthread_barrier_t*, , unsigned int count );
pthread_barrier_wait( pthread_barrier_t* );
pthread_barrier_destroy( pthread_barrier_t* );

Waits till specified number of threads dont reach the barrier point.
Eg - Internet download manager.



============== Thread Termination ==============
pthread_exit( void* retval );


		
============== Mutex ==============
API -
pthread_mutex_t 
pthread_mutex_init( pthread_mutex_t*, const pthread_mutexattr_t* );
pthread_mutex_lock( pthread_mutex_t* );
pthread_mutex_unlock( pthread_mutex_t* );
pthread_mutex_destroy( pthread_mutex_t* );

Code Locking -
In this a part of code is allowed to be executed only by one thread at a time.

Data Locking -
In this the data structure contains a mutex. Only one thread can modify the data at a time.
Two threads may be modifying the same data structure, but if objects are sperate then they can modify the two different objects at the same time.



============== Condition Variable ==============
API -
pthread_cond_t
pthread_init( pthread_cond_t* , pthread_cond_attr_t* );
pthread_cond_wait( pthread_cond_t*, pthread_mutex_t* );
pthread_cond_signal( pthread_cond_t* );
pthread_cond_broadcast( pthread_cond_t* );
pthread_destroy( pthread_cond_t* );

When wait signal is triggered, the mutex ownership is changed to be acquired by other thread. The current thread is blocked.
pthread_cond_signal will unlock one thread that are blocked on the specified cv.
pthread_cond_broadcast will unlock all threads that are blocked on the specified cv.

============== ==============
============== ==============