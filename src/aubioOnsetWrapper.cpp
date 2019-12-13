#include "aubioOnsetWrapper.hpp"
#include <iostream>

AubioOnsetWrapper::AubioOnsetWrapper() : AubioWrapper() {
    this->onset_detector = new_aubio_onset((char *)this->onset_method,this->buffersize,this->hopsize,this->samplerate);

    this->onset = new_fvec(1);
    setSilenceThreshold(this->silence_threshold);
    setOnsetThreshold(this->onset_threshold);
}

AubioOnsetWrapper::~AubioOnsetWrapper() {
    del_fvec(this->onset);
    del_aubio_onset(this->onset_detector);
}

smpl_t AubioOnsetWrapper::aubioDetector(fvec_t* input_fvec) {
    aubio_onset_do(onset_detector, input_fvec, onset);
    return fvec_get_sample(onset,0);
}

void AubioOnsetWrapper::setSilenceThreshold(smpl_t silence_threshold) {
    aubio_onset_set_silence(this->onset_detector, silence_threshold);
}

void AubioOnsetWrapper::setOnsetThreshold(smpl_t onset_threshold) {
    aubio_onset_set_threshold(this->onset_detector, onset_threshold);
}
