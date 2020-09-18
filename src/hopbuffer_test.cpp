#include <iostream>

#include "hopbuffer.hpp"

int main() {

    HopBuffer window(256, 4);

    //window.setBufferReadHead(window.getIndexFromBufferReadHead(128));
    float* arr1 = new float[256];
    float* arr2 = new float[256];
    float* arr3 = new float[256];
    float* arr4 = new float[256];
    for (int i = 0; i < 256; i++) {
        arr1[i] = i;
        arr2[i] = i + 256;
        arr3[i] = i + 512;
        arr4[i] = i + 768;
    }


    std::cout << "process(arr1): [" << std::endl;
    float* result1 = window.process(arr1);
    for (int i = 0; i < 1024; i += 8) {
        if (i % (32*8) == 0) {
            std::cout << std::endl;
        }

        std::cout << result1[i] << ", " << result1[i+1] << ", " << result1[i+2] << ", " << result1[i+3] << ", " << result1[i+4] << ", " << result1[i+5] << ", " << result1[i+6] << ", " << result1[i+7] << ", " << std::endl;
    }
    std::cout << "]" << std::endl;


    float* result2 = window.process(arr2);
    std::cout << "process(arr2): [" << std::endl;
    for (int i = 0; i < 1024; i += 8) {
        if (i % (32*8) == 0) {
            std::cout << std::endl;
        }
        std::cout << result2[i] << ", " << result2[i+1] << ", " << result2[i+2] << ", " << result2[i+3] << ", " << result2[i+4] << ", " << result2[i+5] << ", " << result2[i+6] << ", " << result2[i+7] << ", " << std::endl;
    }
    std::cout << "]" << std::endl;

    float* result3 = window.process(arr3);
    std::cout << "process(arr3): [" << std::endl;
    for (int i = 0; i < 1024; i += 8) {
        if (i % (32*8) == 0) {
            std::cout << std::endl;
        }
        std::cout << result3[i] << ", " << result3[i+1] << ", " << result3[i+2] << ", " << result3[i+3] << ", " << result3[i+4] << ", " << result3[i+5] << ", " << result3[i+6] << ", " << result3[i+7] << ", " << std::endl;
    }
    std::cout << "]" << std::endl;

    float* result4 = window.process(arr4);
    std::cout << "process(arr4): [" << std::endl;
    for (int i = 0; i < 1024; i += 8) {
        if (i % (32*8) == 0) {
            std::cout << std::endl;
        }
        std::cout << result4[i] << ", " << result4[i+1] << ", " << result4[i+2] << ", " << result4[i+3] << ", " << result4[i+4] << ", " << result4[i+5] << ", " << result4[i+6] << ", " << result4[i+7] << ", " << std::endl;
    }
    std::cout << "]" << std::endl;

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    arr1 = nullptr;
    arr2 = nullptr;
    arr3 = nullptr;
    arr4 = nullptr;
    return 0;
}
