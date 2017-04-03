# context_switch
Assignment2 - Measuring Context Switch Costs in C

@ Included files 
hr-timer.c(commented)
contextSwitchCosts.c
Makefile
readme
A2Report.pdf

@ Measurements
1. To measure the cost of a minimal function call, i made bare_func() that is empty and put it in a functionCall(). I iterated functionCall()to get a more accuate cost(average cost).

2. To measure the cost of a minimal system call, i simply added getpid() in the systemCall() function and iterated the function to get a more accuate cost(average cost).

3.to measure the cost of a process switching,i creates two pipes with a
read file descriptor and a write file descriptor in each pipe.
• The main process spawns a child process. Then one of the pipes is used for communication from the main process to the child process. The other pipe is used for communication in the reverse direction.
• The main process starts with sending the child process a single-byte message and then trying to read back from the child process. The child process starts with trying to read something from the main process and then writing a singe-byte message back. Note that process switches are forced when the main process and the child process alternate executions. This process should be repeated many times to get accurate measurement.

4. To measure the cost of a thread switching, i created two threads alternate using a shared integer num (set to be 0 initially).
For the mutex lock and two condition variables, i created funCLock() that does :
Thread #1 keeps waiting for num to become 1 and then changing it to 0. Thread #2 keeps waiting for num to become 0 and changing it to 1.

5. To draw a plot graph, i added 4 different arrays to store elements during iterations. When compiling, it will print out each array elements in a function format for Microsoft EXCEL graph.



@Example result
The cost of a minimal function call(ms): 196
The cost of a minimal system call(ms): 282
The cost of a process switching(ms): 9638
The cost of a thread switching(ms): 31737

FunctionCallCosts ={419;181;170;173;171;171;168;167;175;174}

SystemCallCosts ={1243;190;184;172;174;174;168;174;169;173}

processCallCosts ={17252;10225;9776;8314;8005;7960;8072;8163;8964;9655}

ThreadCallCosts ={97344;28300;23978;24824;23683;23932;23416;23665;23855;24379}



@References 
pipe.c
lock-example.c
https://linux.die.net/man/3/clock_gettime


@ To compile
1. make run / make clean
2. gcc contextSwitchCosts.c -> ./a.out
