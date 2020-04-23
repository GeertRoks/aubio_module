#include <iostream>

#include "hopbuffer.hpp"

int main() {

    int hopfactor = 4;
    int hopsize = 4;
    float* signal1 = new float[hopsize];
    float* signal2 = new float[hopsize];
    float* signal3 = new float[hopsize];
    float* signal4 = new float[hopsize];
    float* output = new float[hopsize * hopfactor];

    for(int i = 0; i < hopsize; i++) {
        signal1[i] = i + 1;
        signal2[i] = i + hopsize + 1;
        signal3[i] = i + 2 * hopsize + 1;
        signal4[i] = i + 3 * hopsize + 1;
    }

    HopBuffer buf(hopsize, hopfactor);

    buf.write(signal1);
    output = buf.getData();
    std::cout << "Signal 1: ";
    for (int i = 0; i < hopsize * hopfactor; i++) {
        std::cout << output[i] << ", ";
    }
    std::cout << std::endl;

    buf.write(signal2);
    output = buf.getData();
    std::cout << "Signal 2: ";
    for (int i = 0; i < hopsize * hopfactor; i++) {
        std::cout << output[i] << ", ";
    }
    std::cout << std::endl;

    buf.write(signal3);
    output = buf.getData();
    std::cout << "Signal 3: ";
    for (int i = 0; i < hopsize * hopfactor; i++) {
        std::cout << output[i] << ", ";
    }
    std::cout << std::endl;

    buf.write(signal4);
    output = buf.getData();
    std::cout << "Signal 4: ";
    for (int i = 0; i < hopsize * hopfactor; i++) {
        std::cout << output[i] << ", ";
    }
    std::cout << std::endl;


    delete[] signal1;
    delete[] signal2;
    delete[] signal3;
    delete[] signal4;
//    delete[] output;

    return 0;
}
