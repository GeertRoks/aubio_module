#include "aubio_pitch.hpp"
#include <iostream>

AubioPitch::AubioPitch() : AubioModule() {
    this->detected_pitch = new_fvec (1);
    pitch_detector = new_aubio_pitch (this->pitch_method, this->buffersize, this->hopsize, samplerate);
}

AubioPitch::~AubioPitch() {
    del_aubio_pitch (pitch_detector);
    del_fvec (detected_pitch);
    aubio_cleanup ();
}

float AubioPitch::aubioDetector(fvec_t* input_fvec) {
    aubio_pitch_do (pitch_detector, input_fvec, detected_pitch);

    return fvec_get_sample(detected_pitch, 0);
}

//uint8_t AubioPitch::getMidiPitch() {

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

