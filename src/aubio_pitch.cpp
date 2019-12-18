#include "aubio_pitch.hpp"
#include <iostream>

AubioPitch::AubioPitch() : AubioModule() {
    this->detected_pitch = new_fvec (1);
    this->pitch_detector = new_aubio_pitch (this->pitch_method, this->buffersize, this->hopsize, this->samplerate);
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

void AubioPitch::setSilenceThreshold(smpl_t silence_threshold) {
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

        del_aubio_pitch (this->pitch_detector);
        aubio_cleanup();
        this->pitch_detector = new_aubio_pitch(this->pitch_method, this->buffersize, this->hopsize, this->samplerate);
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
}

//uint8_t AubioPitch::getMidiPitch() {

    ////size of the buffer with detected pitches
    //int detectSize = 200;

    //for (int i = 0; i <detectSize; i++){
    //    detectedPitches[i] = pitchdetected;
    //}

    ////look for number(pitch) that appears the most in the array of detected pitches
    //int max_count = 0;

    //for (int i=0;i<detectSize;i++)
    //{
    //    int count=1;
    //    for (int j=i+1;j<detectSize;j++)
    //        if (detectedPitches[i]==detectedPitches[j])
    //            count++;
    //    if (count>max_count)
    //        max_count = count;
    //}

    //for (int i=0;i<detectSize;i++)
    //{
    //    int count=1;
    //    for (int j=i+1;j<detectSize;j++)
    //        if (detectedPitches[i]==detectedPitches[j])
    //            count++;
    //    if (count==max_count)
    //        mostDetected = detectedPitches[i];
    //}

    ////convert hertz to closest MIDI-value
    //fmFrequency = (round(12*log2( mostDetected / 440 ) + 69));
//}

