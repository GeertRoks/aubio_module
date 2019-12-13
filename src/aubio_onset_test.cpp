#include <iostream>
#include <math.h>

#include "aubio_onset.hpp"

int main() {

    AubioOnset onset_detector;
    onset_detector.setOnsetThreshold(0.7f);
    onset_detector.setSilenceThreshold(-90.0f);
    smpl_t is_onset = 0.0f;

    std::cout << "This is a test of the AubioOnset class. A buffer of " << onset_detector.buffersize << " samples long filled with a silent signal is put through the algorithm. We then see the decission of the algorithm. After that we fill the buffer with an exponential function. After that we see the decission of the algorithm about that signal." << std::endl;

    // Test signal initialisation (only one buffer in length)
    float* silentbuffer = new float[onset_detector.buffersize];
    float* onsetbuffer = new float[onset_detector.buffersize];
    for(unsigned int i = 0; i < onset_detector.buffersize; i++) {
        silentbuffer[i] = 0.0f;                             // Buffer that gives no onset

        if ((i >= 0 && i <= 10) || (i > 230 && i <= 512)) { // Buffer that gives an onset
            onsetbuffer[i] = 0.0f;
        } else if (i > 10 && i <= 230) {
            onsetbuffer[i] = fmod(((i - 10) * 0.15f), 2.0f) - 1.0f;
        }
    }

    // Run the buffer through Aubio and print the answer
    // First the silent signal
    is_onset = onset_detector.process(silentbuffer);
    std::cout << "Onset decission in silent signal: \t \t" << is_onset << std::endl;

    // Now the signal with an onset
    is_onset = onset_detector.process(onsetbuffer);
    std::cout << "Onset decission in exponential signal: \t \t" << is_onset << std::endl;

// Onset has weird bug: when the silent process hasn't happend gives the expo process a one (as expected). If the silent buffer was processed before the expo buffer it gives a zero.

    // Garbage collection
    delete [] silentbuffer;
    delete [] onsetbuffer;

    return 0;
}
