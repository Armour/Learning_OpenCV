//
//  GPU.cpp
//  OpenCV
//
//  Created by Armour on 2/25/15.
//  Copyright (c) 2015 ZJU. All rights reserved.
//

#include "my_cv.h"

using namespace cv::gpu;

struct Worker {void operator()(int device_id) const;};

void GPU(void) {
    int num_devices = getCudaEnabledDeviceCount();
    if (num_devices < 2) {
        std::cout << "Two or more GPUs are required\n";
    }
    for (int i = 0; i < num_devices; ++i) {
        DeviceInfo dev_info(i);
        if (!dev_info.isCompatible()) {
            std::cout << "GPU module isn't built for GPU #" << i << " ("
            << dev_info.name() << ", CC " << dev_info.majorVersion()
            << dev_info.minorVersion() << "\n";
        }
    }
    
    // Execute calculation in two threads using two GPUs
    int devices[] = {0, 1};
    parallel_do(devices, devices + 2, Worker());
}


void Worker::operator()(int device_id) const {
    setDevice(device_id);
    
    Mat src(1000, 1000, CV_32F);
    Mat dst;
    
    RNG rng(0);
    rng.fill(src, RNG::UNIFORM, 0, 1);
    
    // CPU works
    transpose(src, dst);
    
    // GPU works
    GpuMat d_src(src);
    GpuMat d_dst;
    transpose(d_src, d_dst);
    
    // Check results
    bool passed = norm(dst - Mat(d_dst), NORM_INF) < 1e-3;
    std::cout << "GPU #" << device_id << " (" << DeviceInfo().name() << "): " << (passed ? "passed" : "FAILED") << endl;
    
    // Deallocate data here, otherwise deallocation will be performed
    // after context is extracted from the stack
    d_src.release();
    d_dst.release();
}
