#ifndef AUBIOMODULE_H
#define AUBIOMODULE_H

#include <aubio/aubio.h>
#include <iostream>

#include "hopbuffer.hpp"

class AubioModule {
    public:
        AubioModule();
        ~AubioModule();

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

#endif //AUBIOMODULE_H
