#include "aubioWrapper.hpp"

AubioWrapper::AubioWrapper() {
    this->onset_detector = new_aubio_onset((char *)this->onset_method,this->buffersize,this->hopsize,this->samplerate);

    this->onset = new_fvec(1);
}

AubioWrapper::~AubioWrapper() {
    del_fvec(this->onset);
    del_aubio_onset(this->onset_detector);
}

bool AubioWrapper::process(fvec_t* anabuffer) {
    aubio_onset_do(onset_detector, anabuffer, onset);
    return fvec_get_sample(onset,0);
}

unsigned int AubioWrapper::getBuffersize() const{
    return this->buffersize;
}
