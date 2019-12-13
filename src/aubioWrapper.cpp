#include "aubioWrapper.hpp"

AubioWrapper::AubioWrapper() {
    hopbuffer = new HopBuffer(this->buffersize, this->buffersize/this->hopsize);
    input_fvec = new_fvec(this->buffersize);
}

AubioWrapper::~AubioWrapper() {
    del_fvec(input_fvec);
}

smpl_t AubioWrapper::process(float* inputbuffer) {
    hopbuffer->write(inputbuffer);
    input_fvec->data = hopbuffer->getData();

    return aubioDetector(input_fvec);
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

