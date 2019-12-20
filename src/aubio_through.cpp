#include "aubio_through.hpp"
#include <iostream>

AubioThrough::AubioThrough() : AubioModule() {

}

AubioThrough::~AubioThrough() {

}

smpl_t AubioThrough::aubioDetector(fvec_t* input_fvec) {
    return -1.0f;
}
