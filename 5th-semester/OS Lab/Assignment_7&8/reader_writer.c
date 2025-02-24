#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t mutex,writeblock;
int data = 0,rcount = 0;

void *reader(void *arg)
{
  int f;
  f = *((int *)arg);
  sem_wait(&mutex);         // reader wants to enter the critical section
  rcount = rcount + 1;
  
  if(rcount==1)
   sem_wait(&writeblock);    // if even one reader , wait the writer
   
  sem_post(&mutex); // other readers can enter
  printf("Data read by the reader[%d] is %d\n",f,data);
  sleep(1);
  
  sem_wait(&mutex);      // reader may want to leave
  rcount = rcount - 1;
  
  if(rcount==0)
   sem_post(&writeblock);      // if no reader, writer can enter
   
  sem_post(&mutex);    // reader leaves
}

void *writer(void *arg)
{
  int f;
  f = *((int *) arg);
  sem_wait(&writeblock);
  data++;
  printf("Data writen by the writer[%d] is %d\n",f,data);
  sleep(2);
  sem_post(&writeblock);
}

int main()
{
  int i,b; 
  pthread_t rtid[5],wtid[5];
  sem_init(&mutex,0,1);
  sem_init(&writeblock,0,1);
  for(i=0;i<=4;i++)
  {
    pthread_create(&wtid[i],NULL,writer,&i);
    pthread_create(&rtid[i],NULL,reader,&i);
  }
  for(i=0;i<=4;i++)
  {
    pthread_join(wtid[i],NULL);
    pthread_join(rtid[i],NULL);
  }
  return 0;
}

