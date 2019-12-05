#include "aubioWrapper.hpp"
#include <iostream>

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

void AubioWrapper::setHopfactor(unsigned int hopfactor) {
    if (hopfactor <= 16 && hopfactor >= 1) {
        if (((hopfactor & (hopfactor - 1)) == 0) || hopfactor == 1 ) {
            this->hopsize = this->buffersize/hopfactor;
        } else {
            std::cout << "Error setHopfactor: " << hopfactor << " is not a power of 2 or equal to 1." << std::endl;
        }
    } else {
        std::cout << "Error setHopfactor: " << hopfactor << " is not equal to 1, 2, 4, 8 or 16." << std::endl;
    }
}
