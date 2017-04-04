#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


unsigned long long timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)  //define the function timespecdiff
{
  return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -						//in oder to return the time difference
           ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}

int function_call ( )
{
    return 0;
}

pthread_t t1, t2;
int rt1, rt2;
pthread_mutex_t lock;

void* Fnc() 
	{
		int c = 0;
		pthread_mutex_lock(&lock);
		if (c==1)
		{
			c = 0;
		}
		pthread_mutex_unlock(&lock);	
		if (c==0)
		{
			c = 1;
		}
	}






int main()
{
	int i = 0;
	int sum = 0;
	int avg = 0;
	struct timespec start;
	struct timespec stop;
	unsigned long long result; //64 bit integer

	// for (i = 0; i < 100; ++i)
	// {
	// 	clock_gettime(CLOCK_MONOTONIC, &start);		//get the monotonic time when the system call started
	// 	function_call();
	// 	clock_gettime(CLOCK_MONOTONIC, &stop);		//get the monotonic time when the system call ended

	// 	result=timespecDiff(&stop,&start);			//get the monotonic time difference of the system call
	// 	printf("CLOCK_MONOTONIC Measured for the function call: %llu\n",result);		//print out the result
	// }

	clock_gettime(CLOCK_MONOTONIC, &start);		//get the monotonic time when the system call started
	function_call();
	clock_gettime(CLOCK_MONOTONIC, &stop);		//get the monotonic time when the system call ended

	result=timespecDiff(&stop,&start);			//get the monotonic time difference of the system call
												//the monotonic time represents the absolute elapsed wall-clock time since some arbitrary or
												//fixed point in the past. It is not affected by changes in the system time-of-day clock.
	printf("CLOCK_MONOTONIC Measured for the function call: %llu\n",result);		//print out the result

// for (i = 0; i < 100; ++i)
// 	{
// 		clock_gettime(CLOCK_MONOTONIC, &start);		//get the monotonic time when the system call started
// 		getpid();
// 		clock_gettime(CLOCK_MONOTONIC, &stop);		//get the monotonic time when the system call ended

// 		result=timespecDiff(&stop,&start);			//get the monotonic time difference of the system call
// 		printf("CLOCK_MONOTONIC Measured for the system call getpid: %llu\n",result);		//print out the result
// 	}



	clock_gettime(CLOCK_MONOTONIC, &start);		//get the monotonic time when the system call started
	getpid();
	clock_gettime(CLOCK_MONOTONIC, &stop);		//get the monotonic time when the system call ended

	result=timespecDiff(&stop,&start);			//get the monotonic time difference of the system call
												//the monotonic time represents the absolute elapsed wall-clock time since some arbitrary or
												//fixed point in the past. It is not affected by changes in the system time-of-day clock.
	printf("CLOCK_MONOTONIC Measured for the system call getpid: %llu\n",result);		//print out the result




	//Measure the cost of a process switching

	

	int     fdP[2]; //Pipe child uses to contact parent
	int 	fdC[2]; //Pipe parent uses to contact child
	int nbytes;
	pid_t   childpid;
	char returnString[1];
	char readbuffer[10];
	char inputBuffer[10];

	for (i = 0; i < 100; ++i)
	{
		pipe(fdP); // Child >> Parent
		pipe(fdC); // Parent >> Child
			 
		if((childpid = fork()) == -1)
		{
		        perror("fork");
		        exit(1);
		}
		clock_gettime(CLOCK_MONOTONIC, &start);
		if(childpid == 0)
		{
		        
		    close(fdC[0]); // The Child closes the output side of its pipe

			close(fdP[1]); // The Child also closes the parents input side
				
			bzero((char *) &readbuffer, sizeof(readbuffer)); //Clear buffer

			nbytes = read(fdP[0], readbuffer, sizeof(readbuffer)); // Child blocks on read
			
			returnString[0] = 'x';
			
			write(fdC[1], returnString, (strlen(returnString))); // Send an ACK
				

		    exit(0);
		}
		else
		{
		    
		    close(fdC[1]);
			close(fdP[0]);		
			
			bzero((char *) &inputBuffer, sizeof(inputBuffer));			
			
			inputBuffer[0] = 'x';
			
			    
			write(fdP[1], inputBuffer, (strlen(inputBuffer)));

			nbytes = read(fdC[0], readbuffer, sizeof(readbuffer));

			wait(NULL);
		}
		clock_gettime(CLOCK_MONOTONIC, &stop);
		
		result=timespecDiff(&stop,&start);
		sum = sum + result;			//get the monotonic time difference of the system call
		//printf("%llu\n",result);
		
	}


	avg = sum/100;
	printf("CLOCK_MONOTONIC Average time measured for the process switching: %d\n",avg);


	sum = 0;
	avg = 0;

	//Measure the cost of a thread switching
	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

	for (i = 0; i < 100; ++i)
	{
		 clock_gettime(CLOCK_MONOTONIC, &start);

		if( (rt1=pthread_create( &t1, NULL, &Fnc, NULL)) )
	        printf("Thread creation failed: %d\n", rt1);
	 	if( (rt2=pthread_create( &t2, NULL, &Fnc, NULL)) )
	        printf("Thread creation failed: %d\n", rt2);

	    pthread_join( t1, NULL);
	    pthread_join( t2, NULL);

	    clock_gettime(CLOCK_MONOTONIC, &stop);
	    result=timespecDiff(&stop,&start);
	    sum = sum + result;
	    //printf("%llu\n",result);
	}
	avg = sum/100;
	printf("CLOCK_MONOTONIC Average time measured for the thread switching: %d\n",avg);


}