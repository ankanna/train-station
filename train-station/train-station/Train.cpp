//
//  Train.cpp
//  train-station
//
//  Created by Szymon Kuras on 23.04.2018.
//  Copyright © 2018 ankanna. All rights reserved.
//

#include <pthread.h>
#include <time.h>
#include <stdlib.h>

class Train
{
    pthread_t thread;
    pthread_cond_t granted;
    
    int train_number;
    int loading_time;
    int max_waiting_time;
    
    int priority;
    char state;
    
    
public: Train(int train_number)
    {
        srand(time(NULL));
        
        this->thread = *new pthread_t();
        this->granted = PTHREAD_COND_INITIALIZER;
        
        this->train_number = train_number;
        this->loading_time = (rand() % 7) + 1;
        this->max_waiting_time = (rand() % 20) + 20;
        
        this->priority = (rand() % 10) + 1;
        this->state = 'w'; //waiting (also possible: a - approaching, l - loading)
    }
};
