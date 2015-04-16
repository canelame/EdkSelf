#include "bufferO.h"

 void BufferO::init(unsigned int size){
   glGenBuffers(size, buffers_);
   glBindBuffer(GL_ARRAY_BUFFER,*buffers_);
   glBufferData(GL_, );

}

 void BufferO::bind(const Target t)const{
 
 }