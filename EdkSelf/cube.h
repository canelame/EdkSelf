#ifndef __CUBE_H__
#define __CUBE_H__
#include "EDK3\geometry.h"
#include "EDK3\constants.h"
#include "EDK3\dev\buffer.h"
#include "EDK3\dev\gpumanager.h"


class Cube : public EDK3::Geometry{

public:

  EDK3::ref_ptr< EDK3::dev::Buffer> attributes;
  EDK3::ref_ptr< EDK3::dev::Buffer> normales_;
  EDK3::ref_ptr< EDK3::dev::Buffer> uvs_;
  EDK3::ref_ptr< EDK3::dev::Buffer> indices_;



 
  bool bindAttribute(const EDK3::Attribute a,unsigned int where_to_bind_attribute)const;
  virtual void render() const;
  void init(int size);
  void createQuad();
  Cube();
protected:

  ~Cube(){};
};
#endif