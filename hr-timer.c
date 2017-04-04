#include <stdio.h>
#include <stdint.h>
#include <time.h>

unsigned long long timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)  //define the function timespecdiff
{
  return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -						//in oder to return the time difference
           ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}


int main()
{
struct timespec start;
struct timespec stop;
unsigned long long result; //64 bit integer

clock_gettime(CLOCK_REALTIME, &start);		//get the real time when the system call started
sleep(1);
clock_gettime(CLOCK_REALTIME, &stop);		//get the real time when the system call ended

result=timespecDiff(&stop,&start);  		//get the real time difference of the system call
											//the real time represents the machine's best-guess as to the current wall-clock,
											//it can jump forwards and backwards as the system time-of-day clock is changed, including by NTP

printf("CLOCK_REALTIME Measured: %llu\n",result);	//print out the result

clock_gettime(CLOCK_MONOTONIC, &start);		//get the monotonic time when the system call started
sleep(1);
clock_gettime(CLOCK_MONOTONIC, &stop);		//get the monotonic time when the system call ended

result=timespecDiff(&stop,&start);			//get the monotonic time difference of the system call
											//the monotonic time represents the absolute elapsed wall-clock time since some arbitrary or
											//fixed point in the past. It is not affected by changes in the system time-of-day clock.

printf("CLOCK_MONOTONIC Measured: %llu\n",result);		//print out the result

clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);	    //get the high-resolution per-process time when the system call started
sleep(1);
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);         //get the high-resolution per-process time when the system call ended

result=timespecDiff(&stop,&start);

printf("CLOCK_PROCESS_CPUTIME_ID Measured: %llu\n",result);		//print out the result

clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);                 //get the thread-specific CPU-time time when the system call started
sleep(1);
clock_gettime(CLOCK_THREAD_CPUTIME_ID, &stop);                  //get the thread-specific CPU-time time when the system call ended

result=timespecDiff(&stop,&start);

printf("CLOCK_THREAD_CPUTIME_ID Measured: %llu\n",result);		//print out the result


}
