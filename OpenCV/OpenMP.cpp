//
//  OpenMP.cpp
//  OpenCV
//
//  Created by Armour on 2/25/15.
//  Copyright (c) 2015 ZJU. All rights reserved.
//

#include "my_cv.h"
//#include <omp.h>

void Test (int n) {
    for (int i = 0; i < 10000; i++) {
        for (int j=0; j<10000; j++) {
            //do nothing, just waste time
        }
    }
    printf("%d, ", n);
}

void OpenMP(void) {
    double t = (double)getTickCount();
    
    for(int i = 0; i < 10; i++) {
        Test(i);
    }
    
    t = ((double)getTickCount() - t)/getTickFrequency();
    printf("time without OpenMP: %.3fs\n", t);
    t = (double)getTickCount();
    
#pragma omp parallel for
    
    for (int i = 0; i < 10; i++) {
        Test(i);
    }
    
    t = ((double)getTickCount() - t)/getTickFrequency();
    printf("time with OpenMP: %.3fs\n", t);
}