#include <iostream>
#include <math.h>

#include "aubio_module.hpp"
#include "aubio_through.hpp"

#define PI_2 6.28318530717959


int main() {

    AubioModule* aubio;
    AubioThrough none;
    aubio = &none;

    std::cout << "This is a Test of the AubioThrough class. A buffer of " << aubio->getBuffersize() << " samples long filled with a sine is put through the algorithm. We see the input first and then the output. Expected output: -1.0f" << std::endl;

    float sin_freq = 880.0f;
    float sin_Fs = 48000.0f;
    float sin_phase = 0.0f;  //range from 0.0f to 1.0f

    std::cout << "Input: sine " << sin_freq << "Hz @ " << sin_Fs << "Hz" << std::endl;

    // Test signal initialisation (only one buffer in length)
    float* tempbuffer = new float[aubio->getBuffersize()];
    for(unsigned int i = 0; i < aubio->getBuffersize(); i++) {
        sin_phase += sin_freq / sin_Fs;
        if(sin_phase >= 1) {
            sin_phase = sin_phase - 1; //wrap phase from 0 to 1
        }
        tempbuffer[i] = sin(sin_phase * PI_2 );
    }

    // Run the buffer through Aubio and print the answer
    float detected_value = aubio->process(tempbuffer);
    std::cout << "Aubio output: " << detected_value << std::endl;

    // Garbage collection
    delete [] tempbuffer;

    return 0;
}
