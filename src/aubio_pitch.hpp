#include <aubio/aubio.h>
#include <stdio.h>

class AubioPitch {
    public:
        AubioPitch();
        ~AubioPitch();

        float process(fvec_t* inputBuffer);

        void setHopfactor(unsigned int hopfactor);

        void setSilenceThreshold(smpl_t silence_threshold);
        void setOnsetThreshold(smpl_t onset_threshold);

        //audio proccessing settings
        unsigned int buffersize = 512;
        //unsigned int hopsize = 512;
        unsigned int samplerate = 48000;


        //variables
        uint_t win_s = 4096.0; // window size
        uint_t hop_s = win_s / 4.0; // hop size
        smpl_t pitchdetected = 0.0;
    private:
        //vectors for aubio
        fvec_t *input;
        fvec_t *out;
        // create pitch object
        aubio_pitch_t *o;

};

