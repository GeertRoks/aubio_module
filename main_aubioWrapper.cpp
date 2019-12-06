#include <iostream>
#include "aubioWrapper.hpp"
#include <math.h>

#define PI_2 6.28318530717959

int main() {

    AubioWrapper aubio;

    float frequency = 740.0;
    float samplerate = 48000.0;
    float phase = 0.0;
    // Test signal initialisation (only one buffer in length)
    float* tempbuffer = new float[aubio.buffersize];
    for(unsigned int i = 0; i < aubio.buffersize; i++) {
        phase += frequency / samplerate;
        //wrap phase from 0 to 1
        if(phase >= 1) phase = phase - 1;
        tempbuffer[i] = sin(phase * PI_2 );  // Buffer that gives an onset
    }

    // Initialize specialized type for Aubio and fill it with the test signal
    fvec_t* anabuffer;
    anabuffer = new_fvec(aubio.buffersize);


    //run function
    anabuffer->data = tempbuffer;
    // Run the buffer through Aubio and print the answer
    float pitch = aubio.process(anabuffer);
    std::cout << "pitch: " << pitch << std::endl;

    // Garbage collection
    del_fvec(anabuffer);
    //delete [] tempbuffer;

    return 0;
}
