#include <aubio/aubio.h>
#include <stdio.h>
#include <string>

#include "aubio_module.hpp"

class AubioPitch : public AubioModule {
    public:
        AubioPitch();
        ~AubioPitch();

        smpl_t aubioDetector(fvec_t* input_fvec) override;

        void setSilenceThreshold(smpl_t silence_threshold);

        void setPitchMethod(std::string pitch_method);
        void setPitchMethod(unsigned int num_pitch_method);

        void setPitchOutput(std::string unit);
        void setPitchOutput(unsigned int num_unit);

//        void setOnsetThreshold(smpl_t onset_threshold);

    private:
        //output buffer
        fvec_t* detected_pitch;

        //pitch detector
        aubio_pitch_t* pitch_detector;

        //pitch detection settings
        const char* pitch_method = "default";

};

