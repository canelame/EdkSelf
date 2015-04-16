#include "quad.h"

Quad::Quad(){}

void Quad::init(int size){

  const float quad_positions[32]{
    1 * size, 1 * size, 0,
      1 * size, -1 * size, 0,
      -1 * size, -1 * size, 0,
      -1 * size, 1 * size, 0,

      //UVS
      1, 1,
      1, 0,
      0, 0,
      0, 1,
      //normales
      0, 0, 1,
      0, 0, 1,
      0, 0, 1,
      0, 0, 1
  };
  unsigned int quad_indexes[6]{
  0,1,2,
  0,2,3
  };
 // EDK3::dev::GPUManager * gpu = EDK3::dev::GPUManager::Instance();
  EDK3::dev::GPUManager::Instance()->newBuffer(&attributes);

  
  attributes->init(sizeof(float) * 32 + sizeof(unsigned int) * 6);
  
  attributes->uploadData(quad_positions, sizeof(float)*32, 0);
  attributes->uploadData(quad_indexes, sizeof(unsigned int) * 6, sizeof(float) * 32);

}

bool Quad::bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute)const{
  switch (a)  {
  case EDK3::Attribute::A_POSITION:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(attributes.get(),
      where_to_bind_attribute, EDK3::T_FLOAT_3,
      false, 0, 0
      );
    return true;

  case EDK3::Attribute::A_NORMAL:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(attributes.get(),
      where_to_bind_attribute, EDK3::T_FLOAT_3,
      true, sizeof(float) * 20, 0
      );

    return true;

  case EDK3::Attribute::A_UV:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(attributes.get(),
      where_to_bind_attribute, EDK3::T_FLOAT_2,
      false, sizeof(float) * 12, 0
      );
    return true;
  default:
    return false;
  }
  return false;
}

  void Quad::render()const {
    EDK3::dev::GPUManager::Instance()->drawElements(EDK3::dev::GPUManager::kDrawMode_Triangles, 6, attributes.get(), EDK3::T_UINT, sizeof(float) * 32);

}

