#include "aubio_onset.hpp"
#include <iostream>

AubioOnset::AubioOnset() : AubioModule() {
    this->onset_detector = new_aubio_onset(this->onset_method,this->buffersize,this->hopsize,this->samplerate);

    this->detected_onset = new_fvec(1);
    setSilenceThreshold(this->silence_threshold);
    setOnsetThreshold(this->onset_threshold);
}

AubioOnset::~AubioOnset() {
    del_fvec(this->detected_onset);
    del_aubio_onset(this->onset_detector);
}

smpl_t AubioOnset::aubioDetector(fvec_t* input_fvec) {
    aubio_onset_do(onset_detector, input_fvec, detected_onset);
    return fvec_get_sample(detected_onset, 0);
}

void AubioOnset::setSilenceThreshold(smpl_t silence_threshold) {
    aubio_onset_set_silence(this->onset_detector, silence_threshold);
}

void AubioOnset::setOnsetThreshold(smpl_t onset_threshold) {
    aubio_onset_set_threshold(this->onset_detector, onset_threshold);
}

void AubioOnset::setOnsetMethod(std::string onset_method) {
    // Set the onset detection method
    if (onset_method == "energy"   ||
        onset_method == "hfc"      ||
        onset_method == "complex"  ||
        onset_method == "phase"    ||
        onset_method == "wphase"   ||
        onset_method == "specdiff" ||
        onset_method == "kl"       ||
        onset_method == "mkl"      ||
        onset_method == "specflux") {
        this->onset_method = onset_method.c_str();

        del_aubio_onset (this->onset_detector);
        aubio_cleanup();
        this->onset_detector = new_aubio_onset(this->onset_method, this->buffersize, this->hopsize, this->samplerate);
    } else {
        std::cout << "Error setPitchMethod: " << onset_method << " is not a valid onset detection method. Choose either schmitt, fcomb, mcomb, yin, yinfast or yinfft." << std::endl;
    }

}
void AubioOnset::setOnsetMethod(unsigned int num_onset_method) {
    switch(num_onset_method) {
        case 0:
            this->onset_method = "hfc";
            break;
        case 1:
            this->onset_method = "energy";
            break;
        case 2:
            this->onset_method = "complex";
            break;
        case 3:
            this->onset_method = "phase";
            break;
        case 4:
            this->onset_method = "wphase";
            break;
        case 5:
            this->onset_method = "specdiff";
            break;
        case 6:
            this->onset_method = "specflux";
            break;
        case 7:
            this->onset_method = "kl";
            break;
        case 8:
            this->onset_method = "mkl";
            break;
        default:
            std::cout << "Error setPitchMethod: " << num_onset_method << " is not an option. Set to default. Options are from 0 to 8." << std::endl;
            this->onset_method = "default";
            break;
    }
}

