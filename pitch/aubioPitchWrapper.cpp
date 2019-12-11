#include "aubioPitchWrapper.hpp"
#include <iostream>

AubioWrapper::AubioWrapper() {
    input = new_fvec (hop_s); // input buffer
    out = new_fvec (1); // output candidates
    // create pitch object
    o = new_aubio_pitch ("default", win_s, hop_s, samplerate);
}

AubioWrapper::~AubioWrapper() {
    del_aubio_pitch (o);
    del_fvec (out);
    del_fvec (input);
    aubio_cleanup ();
}

float AubioWrapper::process(fvec_t* anabuffer) {
    //exectute pitch detection
    aubio_pitch_do (o, anabuffer, out);

    return fvec_get_sample(out, 0);
}

//uint8_t AubioWrapper::getMidiPitch() {

    ////size of the buffer with detected pitches
    //int detectSize = 200;

    //for (int i = 0; i <detectSize; i++){
    //    detectedPitches[i] = pitchdetected;
    //}

    ////look for number(pitch) that appears the most in the array of detected pitches
    //int max_count = 0;

    //for (int i=0;i<detectSize;i++)
    //{
    //    int count=1;
    //    for (int j=i+1;j<detectSize;j++)
    //        if (detectedPitches[i]==detectedPitches[j])
    //            count++;
    //    if (count>max_count)
    //        max_count = count;
    //}

    //for (int i=0;i<detectSize;i++)
    //{
    //    int count=1;
    //    for (int j=i+1;j<detectSize;j++)
    //        if (detectedPitches[i]==detectedPitches[j])
    //            count++;
    //    if (count==max_count)
    //        mostDetected = detectedPitches[i];
    //}

    ////convert hertz to closest MIDI-value
    //fmFrequency = (round(12*log2( mostDetected / 440 ) + 69));
//}

void AubioWrapper::setHopfactor(unsigned int hopfactor) {
//    if (hopfactor <= 16 && hopfactor >= 1) {
//        if (((hopfactor & (hopfactor - 1)) == 0) || hopfactor == 1 ) {
//            this->hopsize = this->buffersize/hopfactor;
//        } else {
//            std::cout << "Error setHopfactor: " << hopfactor << " is not a power of 2 or equal to 1." << std::endl;
//        }
//    } else {
//        std::cout << "Error setHopfactor: " << hopfactor << " is not equal to 1, 2, 4, 8 or 16." << std::endl;
//    }
}

