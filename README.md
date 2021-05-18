Starve-free-Reader-writer-problem

The aim of repository is to provide a starvation free solution for reader-writer problem.

Problem Statement :
 
Reader writer problem is a classic problem of synchronization. 
A database is to be shared among several concurrent processes. Some of these processes may only read the database(referred as readers), whereas others may want to write (referred as writers) to the database.If two readers access the shared data simultaneously, no adverse effects will result. However, if a writer and some other process (either a reader or a writer) access the database simultaneously results in adverse effects.

It can be solved by </br>
1.First readers-writers problem : No reader be kept waiting unless a writer has already obtained permission to use the shared object.</br>
2.Second readers-writers problem : Once a writer is ready, that writer performs its write as soon as possible.</br>

But these both lead to starvation of either the readers or the writers.
So we need to find a starvation free reader writer problem solution.



The detailed description and solution is in documentation. </br>
The code is written in c and present in the file starvefree.c 
