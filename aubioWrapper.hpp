#include <aubio/aubio.h>

class AubioWrapper {
    public:
        AubioWrapper();
        ~AubioWrapper();

        bool process(fvec_t* inputBuffer);
        unsigned int getBuffersize() const;

    private:
        //audio proccessing settings
        unsigned int buffersize = 512;
        unsigned int hopsize = 512;
        unsigned int samplerate = 48000;

        //input/output buffers
        fvec_t *onset;

        //onset specific
        aubio_onset_t* onset_detector;
        const char_t* onset_method = "default";
        smpl_t silence_threshold = -90.0f;
        smpl_t onset_threshold = 0.5f;

};

