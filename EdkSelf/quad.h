#ifndef __QUAD_H__
#define __QUAD_H__
#include "EDK3\geometry.h"
#include "EDK3\constants.h"
#include "EDK3\dev\buffer.h"
#include "EDK3\dev\gpumanager.h"

class Quad : public EDK3::Geometry{

public:

 EDK3::ref_ptr< EDK3::dev::Buffer> attributes;
  
  bool bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute)const;
  virtual void render() const;
  void init(int size);
  void createQuad();
  Quad();
protected:

  ~Quad(){};
};
#endif