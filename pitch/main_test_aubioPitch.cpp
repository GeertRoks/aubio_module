#include <iostream>
#include <math.h>

#include "aubioPitchWrapper.hpp"

#define PI_2 6.28318530717959

int main() {

    AubioWrapper aubio;

    std::cout << "This is a Test of the AubioPitchWrapper class. A buffer of " << aubio.buffersize << " samples long filled with a sine is put through the algorithm. We see the input first and then the output." << std::endl;

    float sin_freq = 740.0f;
    float sin_Fs = 48000.0f;
    float sin_phase = 0.0f;  //range from 0.0f to 1.0f

    std::cout << "Input: sine " << sin_freq << "Hz @ " << sin_Fs << "Hz" << std::endl;

    // Test signal initialisation (only one buffer in length)
    float* tempbuffer = new float[aubio.buffersize];
    for(unsigned int i = 0; i < aubio.buffersize; i++) {
        sin_phase += sin_freq / sin_Fs;
        if(sin_phase >= 1) {
            sin_phase = sin_phase - 1; //wrap phase from 0 to 1
        }
        tempbuffer[i] = sin(sin_phase * PI_2 );
    }


    // Initialize specialized type for Aubio and fill it with the test signal
    fvec_t* anabuffer;
    anabuffer = new_fvec(aubio.buffersize);


    //run function
    anabuffer->data = tempbuffer;
    // Run the buffer through Aubio and print the answer
    float pitch = aubio.process(anabuffer);
    std::cout << "Detected pitch: " << pitch << "Hz" << std::endl;

    // Garbage collection
    del_fvec(anabuffer);
    //delete [] tempbuffer;

    return 0;
}

