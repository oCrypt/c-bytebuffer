#include<stdlib.h>
#include<stdio.h>
#include "bytebuffer.h"

struct ByteBuffer {
    char* byteSet;
    int readerIndex;
    int writerIndex;
    int currentSize;
    int maxSize;
};

ByteBuffer* createBuffer(int maxSize) {
    ByteBuffer* buffer = (ByteBuffer*) malloc(sizeof(ByteBuffer));
    buffer->byteSet = (char*) malloc(maxSize);
    buffer->readerIndex = 0;
    buffer->writerIndex = 0;
    buffer->currentSize = 0;
    buffer->maxSize = maxSize;

    return buffer;
}

bool writeByte(char value, ByteBuffer* buffer) {
    if (buffer->writerIndex >= buffer->maxSize) {
        return false;
    }

    buffer->byteSet[buffer->writerIndex] = value;
    buffer->writerIndex++;
    buffer->currentSize++;
    return true;
}

bool writeInt(int value, ByteBuffer* buffer) {
    while (true) {
        char c = value & 0x7F;

        if ((value = value >> 7) == 0) {
            writeByte(c, buffer);
            break;
        }

        if (!writeByte(c | ~0x7F, buffer)) {
            return false;
        }

    }

    return true;
}

char read(ByteBuffer* buffer) {
    if (buffer->readerIndex >= buffer->currentSize) {
        return '\0';
    }

    char value = buffer->byteSet[buffer->readerIndex];
    buffer->readerIndex++;
    return value;
}

int readInt(ByteBuffer* buffer) {
    int index = 0;
    int value = 0;
    while (index < 4) {
        char c = read(buffer);

        if (c == '\0') {
            break;
        }

        if ((c & ~0x7F) == 0) {
            value |= c << (index * 7);
            break;
        }

        value |= (c & 0x7F) << (index * 7);
        index++;
    }

    return value;
}

bool setWriterIndex(int index, ByteBuffer* buffer) {
    if (index > buffer->currentSize || index < 0) {
        return false;
    }

    buffer->writerIndex = index;
}

bool resetWriterIndex(int index, ByteBuffer* buffer) {
    return setWriterIndex(0, buffer);
}

bool setReaderIndex(int index, ByteBuffer* buffer) {
    if (index >= buffer->currentSize || index < 0) {
        return false;
    }

    buffer->readerIndex = index;
}

bool resetReaderIndex(int index, ByteBuffer* buffer) {
    return setReaderIndex(0, buffer);
}

bool canRead(ByteBuffer* buffer) {
    return buffer->readerIndex < buffer->currentSize;
}

bool canWrite(ByteBuffer* buffer) {
    return buffer->writerIndex < buffer->maxSize;
}

bool free(ByteBuffer* buffer) {
    free(buffer->byteSet);
    free(buffer);
}