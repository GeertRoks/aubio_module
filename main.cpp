#include <iostream>
#include <cmath>
#include "src/aubio_onset.hpp"
#include "src/aubio_pitch.hpp"

#define PI_2 6.28318530718


int main() {

    AubioModule *aubio;
    AubioOnset onset;
    AubioPitch pitch;
    aubio = &pitch;

   // Test signal initialisation (only one buffer in length)
//    float* tempbuffer = new float[aubio->getBuffersize()];
//    for(unsigned int i = 0; i < aubio->getBuffersize(); i++) {
//        tempbuffer[i] = (i * pow(2,i) + i*3)/ (0.5*i);  // Buffer that gives an onset
//        //tempbuffer[i] = 0.0f;                         // Buffer that gives no onset
//    }

    pitch.setPitchMethod("yin");
    float sin_freq = 880.0f;
    float sin_Fs = 48000.0f;
    float sin_phase = 0.0f;  //range from 0.0f to 1.0f

    std::cout << "Input: sine " << sin_freq << "Hz @ " << sin_Fs << "Hz" << std::endl;

    // Test signal initialisation (only one buffer in length)
    float* tempbuffer = new float[pitch.getBuffersize()];
    for(unsigned int i = 0; i < pitch.getBuffersize(); i++) {
        sin_phase += sin_freq / sin_Fs;
        if(sin_phase >= 1) {
            sin_phase = sin_phase - 1; //wrap phase from 0 to 1
        }
        tempbuffer[i] = sin(sin_phase * PI_2 );
    }

    pitch.setPitchOutput("hz");
    float detected_pitch = aubio->process(tempbuffer);
    std::cout << "detected pitch " << detected_pitch << std::endl;
    float confidence = pitch.getPitchConfidence();
    std::cout << "confidence " << confidence << std::endl;

    // Initialize specialized type for Aubio and fill it with the test signal
//    fvec_t* anabuffer;
//    anabuffer = new_fvec(aubio->getBuffersize());
//    anabuffer->data = tempbuffer;

    // Run the buffer through Aubio and print the answer
//    bool is_onset = aubio->process(tempbuffer);
//    std::cout << "is_onset: " << is_onset << std::endl;

    // Garbage collection
    //del_fvec(anabuffer);
    delete [] tempbuffer;

    return 0;
}

