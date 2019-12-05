#include "aubioWrapper.hpp"
#include <math.h>
#include <iostream>

int main() {

    AubioWrapper aubio;

    float* tempbuffer = new float[aubio.getBuffersize()];
    for(unsigned int i = 0; i < aubio.getBuffersize(); i++) {
        tempbuffer[i] = (i * pow(2,i) + i*3)/ (0.5*i);
        //tempbuffer[i] = 0.0f;
    }
    fvec_t* anabuffer;
    anabuffer = new_fvec(aubio.getBuffersize());

    anabuffer->data = tempbuffer;

    bool is_onset = aubio.process(anabuffer);
    std::cout << "is_onset: " << is_onset << std::endl;

    del_fvec(anabuffer);
    delete[] tempbuffer;
    return 0;
}
