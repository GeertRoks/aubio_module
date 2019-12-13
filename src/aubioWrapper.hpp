#ifndef AUBIOWRAPPER_H
#define AUBIOWRAPPER_H

#include <aubio/aubio.h>
#include <iostream>

#include "hopbuffer.hpp"

class AubioWrapper {
    public:
        AubioWrapper();
        ~AubioWrapper();

        virtual smpl_t process(float* inputbuffer);
        virtual smpl_t aubioDetector(fvec_t* input_fvec) =0;

        void setHopfactor(unsigned int hopfactor);

        unsigned int buffersize = 512;
        unsigned int hopsize = 512;
        unsigned int samplerate = 48000;

    private:
    fvec_t* input_fvec;
    HopBuffer* hopbuffer;
};

#endif //AUBIOWRAPPER_H
