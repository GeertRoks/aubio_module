#ifndef HOPBUFFER_H
#define HOPBUFFER_H

class HopBuffer
{
public:
  HopBuffer(unsigned long chunksize,unsigned long hopfactor);
  ~HopBuffer();
  void write(float *data);
  float *getData();
private:
  void pointerFlip();
  bool oneIsCurrent;
  float *hopbuffer1;
  float *hopbuffer2;
  float *current_hopbuffer;
  float *next_hopbuffer;
  unsigned long chunksize;
  unsigned long hopfactor;
  unsigned long hopsize;
};

#endif //HOPBUFFER_H
