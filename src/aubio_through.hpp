#include "aubio_module.hpp"

class AubioThrough : public AubioModule {
    public:
        AubioThrough();
        ~AubioThrough();

        float aubioDetector(fvec_t* input_fvec) override;
};
