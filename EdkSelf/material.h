
#include "EDK3\constants.h"
#include "EDK3\dev\shader.h"
#include "EDK3\dev\program.h"
#include "EDK3\ref_ptr.h"
#include "EDK3\dev\gpumanager.h"
#include "EDK3\material.h"
#include "EDK3\camera.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
class MaterialOwn : public EDK3::Material{


public:
  EDK3::scoped_array<char, unsigned int> log;
  EDK3::ref_ptr<EDK3::dev::Shader> shader_v_;
  EDK3::ref_ptr<EDK3::dev::Shader> shader_f_;
  EDK3::ref_ptr<EDK3::dev::Program> program_;
  EDK3::Attribute attribute_at_index(const unsigned int attribute_index)const ;
  EDK3::Type attribute_type_at_index(const unsigned int attrib_index)const;

   bool enable(const EDK3::MaterialSettings *) const;
  // called after enable to setup the camera matrix
    void setupCamera(const EDK3::Camera*) const;
  // called after enable to setup the model matrix
    void setupModel(const float m[16]) const;

   unsigned int num_attributes_required() const;
   MaterialOwn();


 




  

};