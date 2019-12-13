#include "aubio_module.hpp"

class AubioOnset : public AubioModule {
    public:
        AubioOnset();
        ~AubioOnset();

        smpl_t aubioDetector(fvec_t* input_fvec) override;

        void setSilenceThreshold(smpl_t silence_threshold);
        void setOnsetThreshold(smpl_t onset_threshold);

    private:
        //output buffer
        fvec_t *onset;

        //onset detector
        aubio_onset_t* onset_detector;

        //onset detection settings
        const char_t* onset_method = "default";
        smpl_t silence_threshold = -90.0f;
        smpl_t onset_threshold = 0.5f;

};
