#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t readmutex, resource, queue;
int readerscount = 0;
int data = 1;

void *reader(void *id){
	// Entry section
	sem_wait(&queue); // Wait in the queue
	sem_wait(&readmutex); // Lock the entry section for this reader thus not allowing other readers.
	readerscount++;// Increment the number of readers.
	
    // If it is the first reader block the critical section for writers
	if(readerscount==1){
		sem_wait(&resource);
	}
	sem_post(&queue); // release queue allowing next process to be serviced
	sem_post(&readmutex); // Release the entry section for the readers
	
	// Critical Section i.e., perform reading
	printf("Data read by Reader%d is %d\n", *((int *) id), data);
	
	// Exit critical section
	sem_wait(&readmutex);// Lock the exit section 
	readerscount--;
	// If there is no reader, it releases the critical section for writers.
	if(readerscount==0){
		sem_post(&resource);
	}
	sem_post(&readmutex); // Release exit section
	return id;
}

void *writer(void *id){
	// Request for critical section
	sem_wait(&queue); //puts the blocked process in fifo queue 
	sem_wait(&resource);
	sem_post(&queue); // release the semaphore to allow next reader/ writer to be serviced
	
	// modify data value 
	data++;
	
	// Exit critical section
	printf("Data modified by the writer%d is %d\n", *((int *) id), data);
	sem_post(&resource);
	return id;
}

int main(){
	pthread_t readers[5], writers[5];
	sem_init(&readmutex, 0, 1);
	sem_init(&resource, 0, 1);
	sem_init(&queue, 0, 1);
	//create new threads for readers and writers using pthread_create()
	for(int i=0;i<5;i++){
		pthread_create(&writers[i], NULL, writer, (void *)&i);
		pthread_create(&readers[i], NULL, reader, (void *)&i);
	}
	
	for(int i=0;i<5;i++){
		pthread_join(writers[i], NULL);
		pthread_join(readers[i], NULL);
	}
}