//
//  Platform.h
//  train-station
//
//  Created by Ania on 12.05.2018.
//  Copyright © 2018 ankanna. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "StaticWrapper.h"
#include "Train.h"
#include <vector>
#include <unistd.h>

class Platform
{
public:
    
    // platform number
    int number;
    
    Platform(int number);
    
    Platform();
    
    void work(std::vector<Train> trains);
};

