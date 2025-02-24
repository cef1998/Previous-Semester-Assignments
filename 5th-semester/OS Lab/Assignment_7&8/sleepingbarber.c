#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_CUSTOMERS 25
void *customer(void *num);
void *barber(void *);
void randwait(int secs);


// waitingRoom Limits the no. of customers allowed to enter the waiting room at one time.
sem_t waitingRoom;   

// barberChair ensures mutually exclusive access to the barber chair.
sem_t barberChair;

// barberPillow is used to allow the barber to sleep until a customer arrives.
sem_t barberPillow;

// seatBelt is used to make the customer to wait until the barber is done cutting his/her hair. 
sem_t seatBelt;

// Flag to stop the barber thread when all customers have been serviced.
int allDone = 0;


void *customer(void *number) 
{
    int num = *(int *)number;
    // Leave for the shop and take some random amount of time to arrive.
    printf("Customer %d leaving for barber shop.\n", num);
    randwait(5);
    printf("Customer %d arrived at barber shop.\n", num);
    // Wait for space to open up in the waiting room...
    sem_wait(&waitingRoom);
    printf("Customer %d entering waiting room.\n", num);
    // Wait for the barber chair to become free.
    sem_wait(&barberChair);
    // The chair is free so give up your spot in the waiting room.
    sem_post(&waitingRoom);
    // Wake up the barber...
    printf("Customer %d waking the barber.\n", num);
    sem_post(&barberPillow);
    // Wait for the barber to finish cutting your hair.
    sem_wait(&seatBelt);                           //--------------------->>>>>>>>>>>>>>>>>>>>>>>>
    // Give up the chair.
    sem_post(&barberChair);
    printf("Customer %d leaving barber shop.\n", num);
}

void *barber(void *junk) 
{
    // While there are still customers to be serviced...
    // Our barber is omnicient and can tell if there are 
    // customers still on the way to his shop.
    while (!allDone) 
    {
	    // Sleep until someone arrives and wakes you..
	    printf("The barber is sleeping\n");
	    sem_wait(&barberPillow);
	    // Skip this stuff at the end...
	    if (!allDone) 
	    {
    		// Take a random amount of time to cut the customer's hair.
    		printf("The barber is cutting hair\n");
    		randwait(3);
    		printf("The barber has finished cutting hair.\n");
    		// Release the customer when done cutting...
    		sem_post(&seatBelt);                                     // --------------------->>>>>>>>>>>>>>>>>>>>>
    	}
	    else 
	    {
		    printf("The barber is going home for the day.\n");
	    }
    }
}

void randwait(int secs) 
{
    int len;
    len = (int) ((drand48() * secs) + 1);
    sleep(len);
}
int main(int argc, char *argv[]) 
{
    pthread_t btid;
    pthread_t tid[MAX_CUSTOMERS];
    long RandSeed;
    int i, numCustomers, numChairs;
    int Number[MAX_CUSTOMERS];


    // Check to make sure there are the right number of
    // command line arguments.
    if (argc != 4) 
    {
	    printf("Use: SleepBarber <Num Customers> <Num Chairs> <rand seed>\n");
	    exit(-1);
    }
    numCustomers = atoi(argv[1]);
    numChairs = atoi(argv[2]);
    RandSeed = atol(argv[3]);

    // Make sure the number of threads is less than the number of customers we can support.
    if (numCustomers > MAX_CUSTOMERS) 
    {
	    printf("The maximum number of Customers is %d.\n", MAX_CUSTOMERS);
	    exit(-1);
    }

    printf("\nSleepBarber\n\n");

    srand48(RandSeed);                       //------------------------------------------------>>>>>>>>>>>>>>>>>>>>>>>>

    for (i=0; i<MAX_CUSTOMERS; i++) 
 	   Number[i] = i;

    // Initialize the semaphores with initial values...
    sem_init(&waitingRoom, 0, numChairs);
    sem_init(&barberChair, 0, 1);
    sem_init(&barberPillow, 0, 0);
    sem_init(&seatBelt, 0, 0);

    // Create the barber.
    pthread_create(&btid, NULL, barber, NULL);
    // Create the customers.
    for (i=0; i<numCustomers; i++)
    {
     	pthread_create(&tid[i], NULL, customer, (void *)&Number[i]);
    }

    for (i=0; i<numCustomers; i++)
    	pthread_join(tid[i],NULL);

    allDone = 1;
    sem_post(&barberPillow);  // Wake the barber so he will exit.
    pthread_join(btid,NULL);    
}


