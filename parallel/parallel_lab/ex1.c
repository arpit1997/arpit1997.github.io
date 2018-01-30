#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>

int increment_counter(int *counter)
 {
 (*counter)++;
 return *counter;
 }
 
 
 void *counter_thread(void *ctr)
{ printf("In thread: running...\n");
 sleep(1);
 printf("[_THREAD_1]Counter is %d \n", increment_counter((int*)ctr) );
 printf("In thread: exiting .............\n");
 pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
 int int_counter=0;
 pthread_t threads[1];
 int rc=0;
 printf("(log) In main: creating thread %i\n", 1);
 rc = pthread_create(&threads[0], NULL, counter_thread, (void *)&int_counter);
 if (rc){
 printf("ERROR; return code from pthread_create() is %d\n", rc);
 exit(-1);
 }
 sleep(1);
 int res_counter=increment_counter(&int_counter);
 pthread_join(threads[0],NULL); 
 printf("[_MAIN___] Counter is %i \n", res_counter);
 return 0;
}