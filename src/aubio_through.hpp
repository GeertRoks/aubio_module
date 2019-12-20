#include "aubio_module.hpp"

class AubioThrough : public AubioModule {
    public:
        AubioThrough();
        ~AubioThrough();

        smpl_t aubioDetector(fvec_t* input_fvec) override;
};
