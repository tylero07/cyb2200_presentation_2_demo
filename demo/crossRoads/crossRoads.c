/**
 * @instructions
 *
 * @step1 spatch --sp-file add_lock.cocci crossRoads.c
 * @step2 spatch --sp-file add_lock.cocci crossRoads.c --in-place
 * @step3 gcc -g -Wall crossRoads.c -o CrossRoads -pthread
 * @step4 ./CrossRoads 10 10
 *
 * @description
 * This demo simulates a traffic intersection with two one-way roads.
 * One road has south-bound traffic and the other has west-bound traffic.
 * The cars on each road are represented by a thread.
 * Each thread will move the cars on its road through the intersection.
 * The threads will not use any locks to coordinate their actions,
 * so they may cause crashes if they try to move cars through the intersection at the same time.
 *
 * We have identified the critical section of the code that causes the crashes and added a lock to prevent them.
 * progressThroughIntersection()
 *
 * We will use coccinelle to automatically add the lock to the critical section.
 *
 */

#include <stdio.h>  // printf
#include <unistd.h> // for usleep function
#include <stdlib.h> // exit
#include <pthread.h>
#include <semaphore.h>

#define SLEEP_TIME 300000
#define ENTER_INTERSECTION_POINT 5
#define ENTER_WAITING_POINT 4

// Global variables (accessible to all threads)
pthread_mutex_t printRoad;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int iSouthCars;            // Number of cars left heading south
int iWestCars;             // Number of cars left heading west
int iWaitingSouthCar;      // Position of southern most car that has not entered the intersection.
                           //  0-3. 0 is most south.
int iWaitingWestCar;       // Position of western most car that has not entered the intersection.
                           //  0-3. 0 is most south.
int iIntersectionSouthCar; // Position of southern boud car in the intersection.
                           //  0-3. 0 is most south.  -1 = not entered
int iIntersectionWestCar;  // Position of western bound car in the intersection.
                           //  0-3. 0 is most south. -1 = not entered

int progressThroughIntersection();
void *moveSouth(void *arg);
void *moveWest(void *arg);
void drawRoad();
void usage(char *prog_name);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        usage(argv[0]);
    }

    pthread_mutex_init(&printRoad, NULL);

    // Get initial cars from the command line
    iSouthCars = atoi(argv[1]);
    iWestCars = atoi(argv[2]);

    iIntersectionSouthCar = 0;
    iWaitingSouthCar = 1;
    iIntersectionWestCar = 0;
    iWaitingWestCar = 1;
    drawRoad();

    // Create the threads for each direction
    pthread_t thread_handles[2];
    pthread_create(&thread_handles[0], NULL, moveSouth, NULL);
    pthread_create(&thread_handles[1], NULL, moveWest, NULL);

    // Wait for all of the thread to finish
    pthread_join(thread_handles[0], NULL);
    pthread_join(thread_handles[1], NULL);

    pthread_mutex_destroy(&printRoad); // Destroy the mutex lock

    return 0;
}

/**
 * @brief Once the car enters the intersection it is committed to
 *        going through, even if it will cause a crash.
 *        Progress the cars in both threads through the intersection.
 *
 * @return int  number of cars that passed through the intersection
 */
int progressThroughIntersection()
{
    int returnVal = 0;

    if (iIntersectionSouthCar) // Is there a south-bound car in the intersection? If so, move it south.
    {
        iIntersectionSouthCar--;
        if (iIntersectionSouthCar > (ENTER_INTERSECTION_POINT - 2))
        {
            iWaitingSouthCar--;
            returnVal += 1;
        }
    }

    if (iIntersectionWestCar) // Is there a west-bound car in the intersection? If so, move it west.
    {
        iIntersectionWestCar--;
        if (iIntersectionWestCar > (ENTER_INTERSECTION_POINT - 2))
        {
            iWaitingWestCar--;
            returnVal += 2;
        }
    }
    usleep(1);
    return returnVal;
}

/**
 * @brief This is the thread to move the south bound cars.
 *
 * @param  arg    not used in the thread function
 * @return void*  always returns NULL
 */
void *moveSouth(void *arg)
{
    while (iSouthCars > 0 || iIntersectionSouthCar > 0)
    {
        int returnVal = progressThroughIntersection();

        // If there is a car waiting to enter the intersection let it enter.
        // What could possibly go wrong?
        if (iSouthCars && !iIntersectionSouthCar && !iWaitingSouthCar && !iIntersectionWestCar)
        {
            iSouthCars--;
            iIntersectionSouthCar = ENTER_INTERSECTION_POINT;
            if (iSouthCars)
            {
                iWaitingSouthCar = ENTER_WAITING_POINT;
            }
        }

        if (iWaitingSouthCar && returnVal != 1 && returnVal != 3)
        {
            iWaitingSouthCar--;
        }
        drawRoad();
    }
    return NULL;
}

/**
 * @brief This is the thread to move the west bound cars.
 *
 * @param  arg    not used in the thread function
 * @return void*  always returns NULL
 */
void *moveWest(void *arg)
{
    while (iWestCars > 0 || iIntersectionWestCar > 0)
    {
        int returnVal = progressThroughIntersection();

        // If there is a car waiting to enter the intersection let it enter.
        // What could possibly go wrong?
        if (iWestCars && !iIntersectionWestCar && !iWaitingWestCar && !iIntersectionSouthCar)
        {
            iWestCars--;
            iIntersectionWestCar = ENTER_INTERSECTION_POINT;
            if (iWestCars)
            {
                iWaitingWestCar = ENTER_WAITING_POINT;
            }
        }

        if (iWaitingWestCar && returnVal != 2 && returnVal != 3)
        {
            iWaitingWestCar--;
        }
        drawRoad();
    }

    return NULL;
}

/**
 * @brief Draw the road at the end of each cycle.
 *        DO NOT MODIFY THIS CODE!
 */
void drawRoad()
{
    static int crashes = 0; // The number of crashes so far.
    int bSouth = 0;         // A boolean set to 2 if there is a southbound car in the cross point.
    int iEmptySpot;         // a temporary variable to define the space between two cars

    pthread_mutex_lock(&printRoad); // Ensure that we are not in the middle of a print.
    for (int i = 0; i < 50; i++)
    {
        printf("\n"); // jump to bottom of console
    }

    if (iSouthCars > 1)
    {
        printf("and %d more.", iSouthCars - 1);
    }

    if (iSouthCars == 0)
    {
        for (int i = 0; i < 2; i++)
        {
            printf("\n   #");
        }

        if (iIntersectionSouthCar > (ENTER_INTERSECTION_POINT - 1))
        {
            printf("\n | #");
        }
        else
        {
            printf("\n   #");
        }

        if (iIntersectionSouthCar > (ENTER_INTERSECTION_POINT - 2))
        {
            printf("\n | #");
        }
        else
        {
            printf("\n   #");
        }
    }
    else
    {
        iEmptySpot = 4 - iWaitingSouthCar;
        if (iEmptySpot == 4)
        {
            iEmptySpot = 0;
        }

        for (int j = 0; j < 4; j++)
        {
            if (j == iEmptySpot)
            {
                printf("\n   #");
            }
            else
            {
                printf("\n | #");
            }
        }
    }
    printf("###\n");

    if (iIntersectionSouthCar > (ENTER_INTERSECTION_POINT - 3) && iIntersectionSouthCar < (ENTER_INTERSECTION_POINT + 1))
    {
        printf(" | \n");
    }
    else
    {
        printf("\n");
    }

    if (iIntersectionSouthCar > (ENTER_INTERSECTION_POINT - 4) && iIntersectionSouthCar < (ENTER_INTERSECTION_POINT + 0))
    {
        bSouth = 1;
    }
    else
    {
        bSouth = 0;
    }

    ///////////////Print West/////////////////////////////////

    if (iIntersectionWestCar > 0 && iIntersectionWestCar < (ENTER_INTERSECTION_POINT - 1))
    {
        printf("-");
    }
    else
    {
        printf(" ");
    }

    if (iIntersectionWestCar > 1 && iIntersectionWestCar < (ENTER_INTERSECTION_POINT - 0))
    {
        if (bSouth)
        {
            printf("+");
            crashes++;
        }
        else
        {
            printf("-");
        }
    }
    else
    {
        if (bSouth)
        {
            printf("|");
        }
        else
        {
            printf(" ");
        }
    }

    if (iIntersectionWestCar > 2 && iIntersectionWestCar < (ENTER_INTERSECTION_POINT + 1))
    {
        printf("-");
    }
    else
    {
        printf(" ");
    }

    if (iWestCars == 0)
    {
        if (iIntersectionWestCar > (ENTER_INTERSECTION_POINT - 2))
        {
            printf("-");
        }
        else
        {
            printf(" ");
        }

        if (iIntersectionWestCar > (ENTER_INTERSECTION_POINT - 1))
        {
            printf("-");
        }
        else
        {
            printf(" ");
        }
    }
    else
    {
        iEmptySpot = iWaitingWestCar - 1;

        if (iEmptySpot == -1)
        {
            iEmptySpot = 3;
        }

        for (int j = 0; j < 3; j++)
        {
            if (j == iEmptySpot)
            {
                printf(" ");
            }
            else
            {
                printf("-");
            }
        }
    }

    if (iWestCars > 1)
    {
        printf(" and %d more.", iWestCars - 1);
    }

    printf("\n");

    ///////////////////////////////////////////////////////////////

    if (iIntersectionSouthCar > ENTER_INTERSECTION_POINT - 5 && iIntersectionSouthCar < (ENTER_INTERSECTION_POINT - 1))
    {
        printf(" | \n");
    }
    else
    {
        printf("\n");
    }

    printf("Crashes %d \n", crashes);
    pthread_mutex_unlock(&printRoad);
    usleep(SLEEP_TIME);
    // getchar();
}

/**
 * @brief If the user gets the input parameters wrong, print a
 *        friendly message explaining how to run the program.
 *
 * @param prog_name name of the program
 */
void usage(char *prog_name)
{
    fprintf(stderr, "usage: %s <South Cars> <West Cars>\n", prog_name);
    fprintf(stderr, "usage: %s 20 15\n", prog_name);
    exit(0);
}