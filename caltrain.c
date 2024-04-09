#include <pthread.h>
#include "caltrain.h"
#include <stdio.h>
void
station_init(struct station *station)
{
    station->numberOfEmptySeats = 0;
    station->numberOfWaitingPassengers = 0;
    station->numberOfPassengersWalkingOnTrain = 0;
    pthread_mutex_init(&station->mutex, NULL);
    pthread_cond_init(&station->trainArrive, NULL);
    pthread_cond_init(&station->trainReady, NULL);
}

void
station_load_train(struct station *station, int countOfEmptySeatsOnTheArrivedTrain)
{
    pthread_mutex_lock(&station->mutex);                                                                                //printf("line 18 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    station->numberOfEmptySeats = countOfEmptySeatsOnTheArrivedTrain;                                                   //printf("line 19 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    while(station->numberOfEmptySeats > 0 && station->numberOfWaitingPassengers > 0){                                   //printf("line 20 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
        pthread_cond_broadcast(&station->trainArrive);                                                             //printf("line 21 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
        pthread_cond_wait(&station->trainReady, &station->mutex);                                                  //printf("line 22 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    }                                                                                                                   //printf("line 23 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    station->numberOfEmptySeats = 0;                                                                                    //printf("line 24 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    pthread_mutex_unlock(&station->mutex);                                                                              //printf("line 25 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
}

void
station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&station->mutex);                                                                                //printf("line 31 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    station->numberOfWaitingPassengers++;                                                                               //printf("line 32 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    while(station->numberOfPassengersWalkingOnTrain == station->numberOfEmptySeats){                                    //printf("line 33 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
        pthread_cond_wait(&station->trainArrive,&station->mutex);                                                  //printf("line 34 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    }                                                                                                                   //printf("line 35 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    station->numberOfPassengersWalkingOnTrain++;                                                                        //printf("line 36 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    station->numberOfWaitingPassengers--;                                                                               //printf("line 37 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    pthread_mutex_unlock(&station->mutex);                                                                              //printf("line 38 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
}

void
station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->mutex);                                                                                //printf("line 44 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
        station->numberOfEmptySeats--;                                                                                  //printf("line 45 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
        station->numberOfPassengersWalkingOnTrain--;                                                                    //printf("line 46 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
        if(       (station->numberOfEmptySeats == 0 || station->numberOfWaitingPassengers == 0)
                                                        && station->numberOfPassengersWalkingOnTrain == 0){             //printf("line 47 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
            pthread_cond_signal(&station->trainReady);                                                             //printf("line 48 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
        }                                                                                                               //printf("line 49 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
    pthread_mutex_unlock(&station->mutex);                                                                              //printf("line 50 , numberOfEmptySeats = %d, numberOfWaitingPassengers = %d, numberOfPassengersWalkingOnTrain = %d \n",station->numberOfEmptySeats, station->numberOfWaitingPassengers, station->numberOfPassengersWalkingOnTrain);
}

