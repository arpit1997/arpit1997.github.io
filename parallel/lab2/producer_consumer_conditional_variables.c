#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
 
pthread_mutex_t queue_mutex=PTHREAD_COND_INITIALIZER;
pthread_cond_t Queue_Not_Full=PTHREAD_COND_INITIALIZER;
pthread_cond_t Queue_Not_Empty=PTHREAD_COND_INITIALIZER;

// A linked list (LL) node to store a queue entry
struct QNode
{
    int key;
    struct QNode *next;
};
 
// The queue, front stores the front node of LL and rear stores ths
// last node of LL
struct Queue
{
    struct QNode *front, *rear;
    int size;
};
struct Queue *q; 
// A utility function to create a new linked list node.
struct QNode* newNode(int k)
{
    struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->key = k;
    temp->next = NULL;
    return temp; 
}
 
// A utility function to create an empty queue
struct Queue *createQueue()
{
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}
 
// The function to add a key k to q
void enQueue(struct Queue *q, int k)
{
    // Create a new LL node
    struct QNode *temp = newNode(k);
 
    // If queue is empty, then new node is front and rear both
    if (q->rear == NULL)
    {
       q->front = q->rear = temp;
       return;
    }
 
    // Add the new node at the end of queue and change rear

    q->rear->next = temp;
    q->rear = temp;
    q->size++;
}
 
// Function to remove a key from given queue q
struct QNode *deQueue(struct Queue *q)
{
    // If queue is empty, return NULL.
    if (q->front == NULL){
       return NULL;
    }
    
    // Store previous front and move front one node ahead
    struct QNode *temp = q->front;
    q->front = q->front->next;
 
    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
       q->rear = NULL;
    q->size--;
    return temp;
}
void* producer(void* n){
    int i= 0;
    for (i = 0; i < 1000; ++i)
    {
        // if queue is full wait for consumer to consume
            if(q->size>=200){
            pthread_cond_wait(&Queue_Not_Full,&queue_mutex); 
            }
        // acquire lock before enqueuing to queue
            pthread_mutex_lock(&queue_mutex);
            enQueue(q,i);
        // release lock after succesful enqueue 
            pthread_mutex_unlock(&queue_mutex);
        // signal that queue is not empty    
            pthread_cond_signal(&Queue_Not_Empty);
        // }
        /* code */
    }
}

void* consumer(void* n){
    int i=0;
    for (i = 0; i < 1000; ++i)
    {   
    // if queue is empty wait for producer to produce    
        if(q->size==0){
            pthread_cond_wait(&Queue_Not_Empty,&queue_mutex);
            }
            // acquire lock before dequeue
            pthread_mutex_lock(&queue_mutex);
            deQueue(q);
            // release lock after succesful dequeue
            pthread_mutex_unlock(&queue_mutex);
        // signal that queue is not empty    
            pthread_cond_signal(&Queue_Not_Full); 
        /* code */
    }
}
int main()
{
    q = createQueue();
    pthread_t *threads = (pthread_t*)calloc(8, sizeof(pthread_t));
    int i;
    for (i = 0; i < 8; ++i)
    {
        if (i%2 == 0)//even threads would act as producer
        pthread_create(&threads[i], NULL, producer, (void *)&i);
        else //odd threads would act as consumer
        pthread_create(&threads[i], NULL, consumer, (void *)&i);
    }
    return 0;
}