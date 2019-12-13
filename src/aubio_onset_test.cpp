#include <iostream>
#include <math.h>

#include "aubio_onset.hpp"

int main() {

    AubioOnset aubio;
    aubio.setOnsetThreshold(0.7f);
    aubio.setSilenceThreshold(-90.0f);

    std::cout << "This is a test of the AubioOnset class. A buffer of " << aubio.buffersize << " samples long filled with a silent signal is put through the algorithm. We then see the decission of the algorithm. After that we fill the buffer with an exponential function. After that we see the decission of the algorithm about that signal." << std::endl;

    // Test signal initialisation (only one buffer in length)
    float* silentbuffer = new float[aubio.buffersize];
    float* onsetbuffer = new float[aubio.buffersize];
    for(unsigned int i = 0; i < aubio.buffersize; i++) {
        silentbuffer[i] = 0.0f;                             // Buffer that gives no onset

        if ((i >= 0 && i <= 10) || (i > 230 && i <= 512)) { // Buffer that gives an onset
            onsetbuffer[i] = 0.0f;
        } else if (i > 10 && i <= 230) {
            onsetbuffer[i] = fmod(((i - 10) * 0.15f), 2.0f) - 1.0f;
        }
    }

//    for(unsigned int i = 0; i < 512; i++) {
//        std::cout << "buffer[" << i << "] = " << onsetbuffer[i] << std::endl;
//    }

    // Initialize specialized type for Aubio and fill it with the test signal
    fvec_t* anabuffer;
    anabuffer = new_fvec(aubio.buffersize);
    smpl_t is_onset = 0.0f;

    // Run the buffer through Aubio and print the answer
    // First the silent signal
    anabuffer->data = silentbuffer;
    is_onset = aubio.process(anabuffer);
    std::cout << "Onset decission in silent signal: \t \t" << is_onset << std::endl;

    // Now the Exponential signal
    anabuffer->data = onsetbuffer;
    is_onset = aubio.process(anabuffer);
    std::cout << "Onset decission in exponential signal: \t \t" << is_onset << std::endl;

// Onset has weird bug: when the silent process hasn't happend gives the expo process a one (as expected). If the silent buffer was processed before the expo buffer it gives a zero.

    // Garbage collection
    del_fvec(anabuffer);
    //delete [] tempbuffer;

    return 0;
}
