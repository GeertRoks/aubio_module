#include "aubio_module.hpp"

AubioModule::AubioModule() {
    hopbuffer = new HopBuffer(this->buffersize, this->buffersize/this->hopsize);
    input_fvec = new_fvec(this->buffersize);
}

AubioModule::~AubioModule() {
    del_fvec(input_fvec);
}

float AubioModule::process(float* inputbuffer) {
    hopbuffer->write(inputbuffer);
    input_fvec->data = hopbuffer->getData();

    return aubioDetector(input_fvec);
}


void AubioModule::setBuffersize(unsigned int buffersize) {
    if (buffersize >= 8 && buffersize <= 8192) {
        if ((buffersize & (buffersize - 1)) == 0) {
            this->buffersize = buffersize;
        } else {
            std::cout << "Error setBuffersize: " << buffersize << " is not a valid buffersize. Choose either 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 or 8192 samples." << std::endl;
        }
    } else {
        std::cout << "Error setBuffersize: " << buffersize << " is not a valid buffersize. Choose either 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 or 8192 samples." << std::endl;
    }
}
unsigned int AubioModule::getBuffersize() {
    return this->buffersize;
}

void AubioModule::setHopsize(unsigned int hopsize) {
    if (hopsize >= 8 && hopsize <= 8192) {
        if ((hopsize & (hopsize - 1)) == 0) {
            this->hopsize = hopsize;
        } else {
            std::cout << "Error setHopsize: " << hopsize << " is not a valid hopsize. Choose either 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 or 8192 samples." << std::endl;
        }
    } else {
        std::cout << "Error setHopsize: " << hopsize << " is not a valid hopsize. Choose either 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 or 8192 samples." << std::endl;
    }
}
void AubioModule::setHopfactor(unsigned int hopfactor) {
    if (hopfactor <= 16 && hopfactor >= 1) {
        if (((hopfactor & (hopfactor - 1)) == 0) || hopfactor == 1 ) {
            this->hopsize = this->buffersize/hopfactor;
        } else {
            std::cout << "Error setHopfactor: " << hopfactor << " is not a valid hopfactor. Choose either 1, 2, 4, 8 or 16." << std::endl;
        }
    } else {
        std::cout << "Error setHopfactor: " << hopfactor << " is not a valid hopfactor. Choose either 1, 2, 4, 8 or 16." << std::endl;
    }
}
unsigned int AubioModule::getHopsize() {
    return this->hopsize;
}

void AubioModule::setSamplerate(unsigned int samplerate) {
    if (samplerate == 44100 ||
        samplerate == 48000 ||
        samplerate == 96000 ) {
        this->samplerate = samplerate;
    } else {
        std::cout << "Error setSamplerate: " << samplerate << " is not a valid samplerate. Choose either 44100, 48000 or 96000 Hz." << std::endl;
    }
}
unsigned int AubioModule::getSamplerate() {
    return this->samplerate;
}

