#include <aubio/aubio.h>
#include <stdio.h>
#include <string>

#include "aubio_module.hpp"

class AubioPitch : public AubioModule {
    public:
        AubioPitch();
        ~AubioPitch();

        float aubioDetector(fvec_t* input_fvec) override;

        void updateDetector() override;

        void setSilenceThreshold(float silence_threshold);

        void setPitchMethod(std::string pitch_method);
        void setPitchMethod(unsigned int num_pitch_method);

        void setPitchOutput(std::string unit);
        void setPitchOutput(unsigned int num_unit);

        float getPitchConfidence();

//        void setOnsetThreshold(smpl_t onset_threshold);

    private:
        //output buffer
        fvec_t* detected_pitch;

        //pitch detector
        aubio_pitch_t* pitch_detector;

        //pitch detection settings
        const char* pitch_method = "default";

};

