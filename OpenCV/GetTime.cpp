//
//  GetTime.cpp
//  OpenCV
//
//  Created by Armour on 2/24/15.
//  Copyright (c) 2015 ZJU. All rights reserved.
//

#include "my_cv.h"

void GetTime(void) {
    double duration;
    duration = static_cast<double>(getTickCount());
    // do something;
    duration = static_cast<double>(getTickCount()) - duration;
    duration /= getTickFrequency();
}
