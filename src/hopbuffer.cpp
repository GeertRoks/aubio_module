#include <iostream>
#include "hopbuffer.hpp"
#include "string.h" // memcpy

HopBuffer::HopBuffer(unsigned long chunksize,unsigned long hopfactor)
{
  this->chunksize=chunksize;
  this->hopfactor=hopfactor;
  hopbuffer1=new float[chunksize];
  hopbuffer2=new float[chunksize];
  oneIsCurrent=true;
  current_hopbuffer=hopbuffer1;
  next_hopbuffer=hopbuffer2;

  for(unsigned long i=0; i<chunksize; i++) current_hopbuffer[i]=0; // clear buffer

  switch(hopfactor) {
    case 1:
      hopsize = chunksize;
    break;
    case 2:
      hopsize = chunksize/2;
    break;
    case 4:
      hopsize = chunksize/4;
    break;
    default:
      hopfactor=1; // force default
      hopsize = chunksize;
  } // switch
} // HopBuffer()


HopBuffer::~HopBuffer()
{
  delete [] hopbuffer1;
  delete [] hopbuffer2;
} // ~HopBuffer()


void HopBuffer::pointerFlip()
{
  oneIsCurrent=!oneIsCurrent;

  if(oneIsCurrent){
    current_hopbuffer=hopbuffer1;
    next_hopbuffer=hopbuffer2;
  }
  else{
    current_hopbuffer=hopbuffer2;
    next_hopbuffer=hopbuffer1;
  }
} // pointerFlip()


void HopBuffer::write(float *data)
{
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
  } // switch

  pointerFlip();
} // write()


float *HopBuffer::getData()
{
  return current_hopbuffer;
} // getData()

