#ifndef BYTE_BUFFER_H
#define BYTE_BUFFER_H

struct ByteBuffer;

ByteBuffer* createBuffer(int maxSize);

bool writeByte(char value, ByteBuffer* buffer);

bool writeVarInt(int value, ByteBuffer* buffer);

char read(ByteBuffer* buffer);

int readVarInt(ByteBuffer* buffer);

bool setWriterIndex(int index, ByteBuffer* buffer);

bool resetWriterIndex(ByteBuffer* buffer);

bool setReaderIndex(int index, ByteBuffer* buffer);

bool resetReaderIndex(ByteBuffer* buffer);

bool canRead(ByteBuffer* buffer);

bool canWrite(ByteBuffer* buffer);

bool free(ByteBuffer* buffer);

#endif