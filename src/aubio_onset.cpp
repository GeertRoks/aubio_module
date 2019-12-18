#include "aubio_onset.hpp"
#include <iostream>

AubioOnset::AubioOnset() : AubioModule() {
    this->onset_detector = new_aubio_onset((char *)this->onset_method,this->buffersize,this->hopsize,this->samplerate);

    this->detected_onset = new_fvec(1);
    setSilenceThreshold(this->silence_threshold);
    setOnsetThreshold(this->onset_threshold);
}

AubioOnset::~AubioOnset() {
    del_fvec(this->detected_onset);
    del_aubio_onset(this->onset_detector);
}

smpl_t AubioOnset::aubioDetector(fvec_t* input_fvec) {
    aubio_onset_do(onset_detector, input_fvec, detected_onset);
    return fvec_get_sample(detected_onset, 0);
}

void AubioOnset::setSilenceThreshold(smpl_t silence_threshold) {
    aubio_onset_set_silence(this->onset_detector, silence_threshold);
}

void AubioOnset::setOnsetThreshold(smpl_t onset_threshold) {
    aubio_onset_set_threshold(this->onset_detector, onset_threshold);
}
