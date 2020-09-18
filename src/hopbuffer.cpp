#include "hopbuffer.hpp"

HopBuffer::HopBuffer(unsigned int step_size, unsigned int hop_factor) {
    if (hop_factor > 1) {
        this->buffer_size = step_size * (hop_factor -1);
        this->buffer = new float[buffer_size]();
    }

    this->output_size = step_size * hop_factor;
    this->output = new float[this->output_size]();

    this->output_fvec = new_fvec(output_size);

    this->step_size = step_size;
    this->hop_factor = hop_factor;
}
HopBuffer::~HopBuffer() {
    if (this->hop_factor > 1) {
        delete[] buffer;
    }
    buffer = nullptr;

    delete[] output;
    output = nullptr;

    del_fvec(output_fvec);
    output_fvec = nullptr;
}

float* HopBuffer::process(const float* input) {
    //fill the first part of the output with previous samples that overlap with previous outputs
    if (this->hop_factor > 1) {
        for (unsigned int i = 0; i < this->buffer_size; i++) {
            output[i] = buffer[getIndexFromBufferReadHead(i)];
        }
        writeToBuffer(input);
    }
    //fill the last part of the output with the incomming samples
    for (unsigned int i = 0; i < this->step_size; i++) {
        output[this->buffer_size + i] = input[i];
    }
    return output;
}

fvec_t* HopBuffer::processFvec(const float* input) {
    if (this->hop_factor > 1) {
        for (unsigned int i = 0; i < this->buffer_size; i++) {
            output_fvec->data[i] = buffer[getIndexFromBufferReadHead(i)];
        }
        writeToBuffer(input);
    }
    //fill the last part of the output with the incomming samples
    for (unsigned int i = 0; i < this->step_size; i++) {
        output_fvec->data[this->buffer_size + i] = input[i];
    }
    return output_fvec;
}

void HopBuffer::writeToBuffer(const float* input) {
    for (unsigned int i = 0; i < this->step_size; i++) {
        buffer[getIndexFromBufferReadHead(i)] = input[i];
    }
    setBufferReadHead(getIndexFromBufferReadHead(this->step_size));
}

void HopBuffer::setBufferReadHead(unsigned int index) {
    if (index >= 0 && index < buffer_size) {
        this->buffer_read_head = index;
    } else {
        index = (index + buffer_size) % buffer_size;
        this->buffer_read_head = index;
    }
}

unsigned int HopBuffer::getIndexFromBufferReadHead(unsigned int index) {
    unsigned int index_from_read_head = this->buffer_read_head + index;
    if (index_from_read_head < 0 || index_from_read_head >= this->buffer_size) {
        index_from_read_head = (index_from_read_head + this->buffer_size) % this->buffer_size;
    }
    return index_from_read_head;
}
