#include "aubio_pitch.hpp"
#include <iostream>

AubioPitch::AubioPitch() : AubioModule() {
    this->detected_pitch = new_fvec (1);
    this->pitch_detector = new_aubio_pitch(this->pitch_method, this->buffersize, this->hopsize, this->samplerate);
    setPitchOutput("midi");
}

AubioPitch::~AubioPitch() {
    del_aubio_pitch(this->pitch_detector);
    del_fvec(this->detected_pitch);
    aubio_cleanup();
    this->pitch_detector = nullptr;
    this->detected_pitch = nullptr;
}

float AubioPitch::aubioDetector(fvec_t* input_fvec) {
    aubio_pitch_do (pitch_detector, input_fvec, detected_pitch);

    return fvec_get_sample(detected_pitch, 0);
}

void AubioPitch::updateDetector() {
    del_aubio_pitch(this->pitch_detector);
    aubio_cleanup();
    this->pitch_detector = new_aubio_pitch(this->pitch_method, this->buffersize, this->hopsize, this->samplerate);
    std::cout << "pitch buf: " << this->buffersize << ", hop: " << this->hopsize << ", hopf: " << this->buffersize/this->hopsize << ", method: " << this->pitch_method << std::endl;
    setPitchOutput("midi");
}



void AubioPitch::setSilenceThreshold(float silence_threshold) {
    // Set the silence threshold of the pitch detection object, in dB
    aubio_pitch_set_silence(this->pitch_detector, silence_threshold);
}

void AubioPitch::setPitchMethod(std::string pitch_method) {
    // Set the pitch detection method
    if (pitch_method == "schmitt" ||
        pitch_method == "fcomb"   ||
        pitch_method == "mcomb"   ||
        pitch_method == "yin"     ||
        pitch_method == "yinfast" ||
        pitch_method == "yinfft") {
        this->pitch_method = pitch_method.c_str();

        updateDetector();

    } else {
        std::cout << "Error setPitchMethod: " << pitch_method << " is not a valid pitch detection method. Choose either schmitt, fcomb, mcomb, yin, yinfast or yinfft." << std::endl;
    }

}

void AubioPitch::setPitchMethod(unsigned int num_pitch_method) {
    switch(num_pitch_method) {
        case 0:
            this->pitch_method = "yinfft";
            break;
        case 1:
            this->pitch_method = "yin";
            break;
        case 2:
            this->pitch_method = "yinfast";
            break;
        case 3:
            this->pitch_method = "schmitt";
            break;
        case 4:
            this->pitch_method = "fcomb";
            break;
        case 5:
            this->pitch_method = "mcomb";
            break;
        default:
            std::cout << "Error setPitchMethod: " << num_pitch_method << " is not an option. Set to default. Options are from 0 to 5." << std::endl;
            this->pitch_method = "default";
            break;
    }
    updateDetector();
}

void AubioPitch::setPitchOutput(std::string unit) {
    if (unit == "hz" || unit == "Hz" || unit == "HZ") {
        aubio_pitch_set_unit(this->pitch_detector, "Hz");
    } else if (unit == "midi" || unit == "Midi" || unit == "MIDI") {
        aubio_pitch_set_unit(this->pitch_detector, "midi");
    } else {
        std::cout << "Error setPitchOutput: " << unit << " is not a valid pitch output unit. Choose either Hz of midi.";
    }
}
void AubioPitch::setPitchOutput(unsigned int num_unit) {
    switch(num_unit) {
        case 0:
            aubio_pitch_set_unit(this->pitch_detector, "midi");
            break;
        case 1:
            aubio_pitch_set_unit(this->pitch_detector, "Hz");
            break;
        default:
            std::cout << "Error setPitchOutput: " << num_unit << " is not an option. Set to default. Options are 0 or 1.";
    }
}
