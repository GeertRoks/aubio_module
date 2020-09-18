#ifndef HOPBUFFER_H
#define HOPBUFFER_H

extern "C" {
#include <aubio/aubio.h>
}

class HopBuffer{
    public:
        HopBuffer(unsigned int step_size, unsigned int hop_factor);
        ~HopBuffer();

        float* process(const float* input);
        fvec_t* processFvec(const float* input);

    private:
        float* buffer;
        float* output;
        fvec_t* output_fvec;

        unsigned int buffer_read_head = 0;
        unsigned int buffer_size = 0;
        unsigned int output_size;
        unsigned int hop_factor;
        unsigned int step_size;

        void writeToBuffer(const float* input);
        void setBufferReadHead(unsigned int index);
        unsigned int getIndexFromBufferReadHead(unsigned int index);
};

#endif
