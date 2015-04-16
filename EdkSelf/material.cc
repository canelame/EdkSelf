#include "material.h"

EDK3::Attribute MaterialOwn::attribute_at_index(const unsigned int attribute_index)const{
  switch (attribute_index)
  {
  case 0: return EDK3::Attribute::A_POSITION;
  case 1: return EDK3::Attribute::A_NORMAL;
 
  }
  return EDK3::Attribute::A_NONE;
}

EDK3::Type MaterialOwn::attribute_type_at_index(const unsigned int attrib_index)const{


  switch (attrib_index)
  {
  case 0: return EDK3::T_FLOAT_3;
  case 1: return EDK3::T_FLOAT_3;
  }
  return EDK3::T_NONE;
}

unsigned int MaterialOwn::num_attributes_required()const{
 
  return 2;
}
MaterialOwn::MaterialOwn(){
  EDK3::dev::GPUManager::Instance()->newShader(&shader_f_);
  EDK3::dev::GPUManager::Instance()->newShader(&shader_v_);
  EDK3::dev::GPUManager::Instance()->newProgram(&program_);

 

  std::string line;
  std::stringstream vertex_string;
  std::ifstream vertex("diffuse.sha");
  if (vertex.is_open()){
    vertex_string << vertex.rdbuf();
    vertex.close();
    line = vertex_string.str();
  }

  std::string fragment_text;
  std::stringstream fragment_string;
  std::ifstream fragmet("diffuse.frag");
  if (fragmet.is_open()){
    fragment_string << fragmet.rdbuf();
    fragmet.close();
    fragment_text = fragment_string.str();
  }






  shader_v_->loadSource(EDK3::dev::Shader::kType_Vertex, line.c_str(), strlen(line.c_str()));
  shader_f_->loadSource(EDK3::dev::Shader::kType_Fragment, fragment_text.c_str(), strlen(fragment_text.c_str()));
  shader_v_->compile();
  shader_f_->compile();

  log.memClear();

  

  program_->attach(shader_v_.get());
  program_->attach(shader_f_.get());


  //log.memClear();
  if (program_->link(&log)){
    printf("linked");
  }
  else{
    printf("%s", log);

  }

 


}

bool MaterialOwn::enable(const EDK3::MaterialSettings *)const{
  program_->use();
  return true;

  //const MAterialOwn::Settings settings = dynamyc_cast<>
  /*
  Texturas
  texture->bind(posicion en la cual se bindia la texutra)
  int index=7;
  set_uniform("texture_diffse",&index,UINT_1);

  El en shader tenemos un uniform sample2d text_diffuse -> recibios la texutra
  texturea(textdifusse, uv)-> debuellve un vec4 de color.


  int t_index=0;
  settings->texture()->bind(t_inde);
  int texture_i = program->set_uniform("u_texture");
  if(texture_i>=0){
  program->set_uniform(texture_i,EDK3::T_INT1,&t_index);
  }
  */
}


void MaterialOwn::setupCamera(const EDK3::Camera *cam)const{

  int view = program_->get_uniform_position("u_view_matrix");
  int projection = program_->get_uniform_position("u_projection_matrix");


  
  program_->set_uniform_value(view, EDK3::T_MAT_4x4, cam->view_matrix());
  program_->set_uniform_value(projection, EDK3::T_MAT_4x4, cam->projection_matrix());

}

void MaterialOwn::setupModel(const float m[16])const{
  int model = program_->get_uniform_position("u_model_matrix");
  program_->set_uniform_value(model, EDK3::T_MAT_4x4, m);
}