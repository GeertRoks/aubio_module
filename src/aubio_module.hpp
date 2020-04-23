#ifndef AUBIOMODULE_H
#define AUBIOMODULE_H

extern "C" {
#include <aubio/aubio.h>
}
#include <iostream>

#include "hopbuffer.hpp"

class AubioModule {
    public:
        AubioModule();
        ~AubioModule();

        virtual float process(const float* inputbuffer);
        virtual float aubioDetector(fvec_t* input_fvec) =0;

        void updateAudioHandling();
        virtual void updateDetector() =0;

        void setBuffersize(unsigned int buffersize);
        unsigned int getBuffersize();

        void setHopsize(unsigned int hopsize);
        void setHopfactor(unsigned int hopfactor);
        unsigned int getHopsize();

        void setSamplerate(unsigned int samplerate);
        unsigned int getSamplerate();

    protected:
        unsigned int buffersize = 512;
        unsigned int hopsize = 512;
        unsigned int hopfactor = 1;
        unsigned int samplerate = 48000;

    private:
        fvec_t* input_fvec;
        HopBuffer* hopbuffer;
};

#endif //AUBIOMODULE_H
