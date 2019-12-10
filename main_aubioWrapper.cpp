#include <iostream>
#include "onset/aubioOnsetWrapper.hpp"
#include <math.h>

int main() {

    AubioWrapper aubio;

    // Test signal initialisation (only one buffer in length)
    float* tempbuffer = new float[aubio.buffersize];
    for(unsigned int i = 0; i < aubio.buffersize; i++) {
        tempbuffer[i] = (i * pow(2,i) + i*3)/ (0.5*i);  // Buffer that gives an onset
        //tempbuffer[i] = 0.0f;                         // Buffer that gives no onset
    }

    // Initialize specialized type for Aubio and fill it with the test signal
    fvec_t* anabuffer;
    anabuffer = new_fvec(aubio.buffersize);
    anabuffer->data = tempbuffer;

    // Run the buffer through Aubio and print the answer
    bool is_onset = aubio.process(anabuffer);
    std::cout << "is_onset: " << is_onset << std::endl;

    // Garbage collection
    del_fvec(anabuffer);
    //delete [] tempbuffer;

    return 0;
}
