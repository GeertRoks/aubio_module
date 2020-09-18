#include <aubio/aubio.h>
#include "hopbuffer.hpp"

int main() {
    HopBuffer hopbuffer(16, 2);
    fvec_t* fvec = nullptr;

    float* input1 = new float[16];
    float* input2 = new float[16];
    //float* input3 = new float[16];
    //float* input4 = new float[16];
    for(int i = 0; i < 16; i++) {
        input1[i] = i;
        input2[i] = i + 16;
        //input3[i] = i + 32;
        //input4[i] = i + 48;
    }

    fvec = hopbuffer.processFvec(input1);
    fvec_print(fvec);

    fvec = hopbuffer.processFvec(input2);
    fvec_print(fvec);

    //del_fvec(fvec);
    delete[] input1;
    delete[] input2;
    //delete[] input3;
    //delete[] input4;
    return 0;
}
