#include "aubioWrapper.hpp"

AubioWrapper::AubioWrapper() {
    this->onset_detector = new_aubio_onset((char *)this->onset_method,this->buffersize,this->hopsize,this->samplerate);

    this->onset = new_fvec(1);
    this->anabuffer = new_fvec(this->buffersize);
}

AubioWrapper::~AubioWrapper() {
    del_fvec(this->onset);
    del_fvec(this->anabuffer);
    del_aubio_onset(this->onset_detector);
}
