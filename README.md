# Starve-free-Reader-writer-problem #

The aim of repository is to provide a starvation free solution for reader-writer problem.

## Problem Statement : ##
 
Reader writer problem is a classic problem of synchronization. 
A database is to be shared among several concurrent processes. Some of these processes may only read the database(referred as readers), whereas others may want to write (referred as writers) to the database.If two readers access the shared data simultaneously, no adverse effects will result. However, if a writer and some other process (either a reader or a writer) access the database simultaneously results in adverse effects.

It can be solved by </br>
1.First readers-writers problem : No reader be kept waiting unless a writer has already obtained permission to use the shared object.</br>
2.Second readers-writers problem : Once a writer is ready, that writer performs its write as soon as possible.</br>

But these both lead to starvation of either the readers or the writers.
So we need to find a starvation free reader writer problem solution.



The detailed description and solution is in documentation. </br>
The code is written in c and present in the file starvefree.c </br>
## Implementation : ##
```
Variables used for implementation are 
Int Readerscount = 0; // number of reader processes in critical section initialized to 0;
Resource = Semaphore(1); //used for requesting access to CS
Queue = Semaphore(1); //used for maintaining FIFO order of processes for using critical section
Readmutex = Semaphore(1); //used for avoiding race conditions in entry section and exit section
```


## Pseudo Code: ##
### Reader : ###
```
Do{
wait(Queue); //put blocked process in the queue to be processed 
wait(Readmutex);
Readerscount = Readerscount +1; 
if(Readerscount ==1 ) wait(Resource); // if it is first reader lock the resource for writers
signal(Queue);  // let next process in queue to be serviced
signal(Readmutex);

Critical section


wait(Readmutex);
Readerscount = Readerscount -1;
if(Readerscount == 0)  signal(Resource); // If no readers are left release the resource so it can be used by other writer in queue 
signal(Readmutex);
}while(true);
```
### Writer : ###
```
Do{
wait(Queue); //put blocked process in the queue to be processed
wait(Resource); //lock the resource as no writer or reader can enter if writer is in CS
signal(Queue);   // let next process in queue to be serviced

Critical section


Signal(Resource);  //release resource for next reader/writer
}while(true);
```
## Explanation : ##
It is satisfied if semaphores preserve first-in first-out ordering while blocking and releasing threads.
A reader will first wait in queue after it gets access it enters entry section .
If it is first reader then it locks the resource stopping writers from accessing it.
Then it gives access to the next process in queue .
If there are no readers left then it unlocks the resource giving access to other writers.
A writer will first wait in queue after it gets access it enters entry section .
It then locks the resource avoiding other readers from accessing it.
After it writes in critical section it then unlocks the resource giving access for next reader/writer.


## Correctness : ##
### Mutual exclusion :   </br>
If there is a writer in critical section no other process can access .This is ensured by
resource semaphore .If there is reader in critical section no writer is allowed .It is ensured 
by the step ‘wait(resource)’ as writer needs to unlock the resource to enter critical 
section.So mutual exclusion is followed.

### Progress : </br>
Both reader and writer processes take finite time in critical section and also release the 
semaphores while leaving the critical section thus there is no possibility of deadlock here.

### Bounded Wait : </br>
The processes wait in FIFO queue.The queue semaphore ensures that it is done in FIFO 
sequence so all are executed after a finite time and therefore no starvation.
