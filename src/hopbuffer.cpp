#include <iostream>
#include "hopbuffer.hpp"
#include "string.h" // memcpy

HopBuffer::HopBuffer(unsigned long hopsize, unsigned long hopfactor) {
  this->hopsize = hopsize;
  this->hopfactor = hopfactor;

  switch(hopfactor) {
    case 1:
      buffersize = hopsize;
    break;
    case 2:
      buffersize = hopsize * 2;
    break;
    case 4:
      buffersize = hopsize * 4;
    break;
    case 8:
      buffersize = hopsize * 8;
    break;
    case 16:
      buffersize = hopsize * 16;
    break;
    default:
      hopfactor = 1; // force default
      buffersize = hopsize;
  } // switch

  hopbuffer1 = new float[buffersize];
  hopbuffer2 = new float[buffersize];
  oneIsCurrent = true;
  current_hopbuffer = hopbuffer1;
  next_hopbuffer = hopbuffer2;

  for(unsigned long i = 0; i<buffersize; i++) {
      current_hopbuffer[i] = 0; // clear buffer
  }

} // HopBuffer()


HopBuffer::~HopBuffer() {
  delete [] hopbuffer1;
  delete [] hopbuffer2;
} // ~HopBuffer()


void HopBuffer::pointerFlip() {
  oneIsCurrent = !oneIsCurrent;

  if(oneIsCurrent) {
    current_hopbuffer = hopbuffer1;
    next_hopbuffer = hopbuffer2;
  } else {
    current_hopbuffer = hopbuffer2;
    next_hopbuffer = hopbuffer1;
  }
} // pointerFlip()


void HopBuffer::write(float *data) {
  switch(hopfactor) {
    //#if DEBUG // find a trick to not have to copy
    case 1:
      memcpy(next_hopbuffer,data,hopsize*sizeof(float));
    break;
    //#endif
    case 2:
      memcpy(next_hopbuffer,current_hopbuffer+hopsize,hopsize*sizeof(float));
      memcpy(next_hopbuffer+hopsize,data,hopsize*sizeof(float));
    break;
    case 4:
      memcpy(next_hopbuffer,current_hopbuffer+hopsize,3*hopsize*sizeof(float));
      memcpy(next_hopbuffer+3*hopsize,data,hopsize*sizeof(float));
    break;
    case 8:
      memcpy(next_hopbuffer,current_hopbuffer+hopsize,7*hopsize*sizeof(float));
      memcpy(next_hopbuffer+7*hopsize,data,hopsize*sizeof(float));
    break;
    case 16:
      memcpy(next_hopbuffer, current_hopbuffer+hopsize,16*hopsize*sizeof(float));
      memcpy(next_hopbuffer+15*hopsize,data,hopsize*sizeof(float));
    break;
  } // switch

  pointerFlip();
} // write()


float *HopBuffer::getData() {
  return current_hopbuffer;
} // getData()

