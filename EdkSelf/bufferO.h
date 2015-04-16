#include <EDK3\dev\buffer.h>
#include <EDK3\dev\gpumanager.h>
#include <EDK3\dev\opengl.h>

class BufferO : public EDK3::dev::Buffer{

  virtual void init(unsigned int size);
  virtual void bind(const Target t)const;
  virtual unsigned int size()const;
  virtual void uploadData(
    const void *data,
    unsigned int size,
    unsigned int offset = 0);
  virtual void realease();
  GLuint *buffers_;


};