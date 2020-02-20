#include <string>

#include "aubio_module.hpp"

class AubioOnset : public AubioModule {
    public:
        AubioOnset();
        ~AubioOnset();

        float aubioDetector(fvec_t* input_fvec) override;

        void updateDetector() override;

        void setSilenceThreshold(float silence_threshold);
        void setOnsetThreshold(float onset_threshold);

        void setOnsetMethod(std::string onset_method);
        void setOnsetMethod(unsigned int num_onset_method);

    private:
        //output buffer
        fvec_t* detected_onset;

        //onset detector
        aubio_onset_t* onset_detector;

        //onset detection settings
        const char_t* onset_method = "default";
        float silence_threshold = -90.0f;
        float onset_threshold = 0.5f;

};
