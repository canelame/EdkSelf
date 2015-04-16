#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffusetexture.h>
#include <EDK3/texture.h>
#include <EDK3/dev/gpumanager.h>
#include "quad.h"
#include "cube.h"
#include "material.h"


#include <iostream>
#include <cmath>
#include "objloader.h"
class BufferO : public EDK3::dev::Buffer{
  //EL INIT SE PUEDE LLAMAR MAS DE UNA VEZ
  virtual void init(unsigned int size){
   
    
    
  }



};

class GPUManager : public EDK3::dev::GPUManager{

  virtual void newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer>*B){
    B->allocT<BufferO>();
  }

};

struct {
  EDK3::ref_ptr<EDK3::Camera> camera;
  EDK3::ref_ptr<EDK3::Node> root;
} GameState;

void prepare() {
  EDK3::dev::GPUManager::CheckGLError("Prepare Start");
  // Create a cube
  EDK3::scoped_array<char> log;
  //EDK3::scoped_array<EDK3::ref_ptr < EDK3::Geometry >> geo;

// bool objR= EDK3::LoadObj("heart.obj", &geo, &log);
  
 EDK3::ref_ptr< EDK3::Geometry >cube;
 //cube = *geo.get();

 EDK3::CreateCube(&cube, 40, true, true);
  //EDK3::ref_ptr<Cube> cube;
 
  //cube.alloc();
// cube->init(40);

  
  

  //EDK3::ref_ptr<EDK3::MatDiffuseTexture> myMaterial;
  EDK3::ref_ptr<EDK3::MatDiffuseTexture::Settings> mat_settings;
  EDK3::ref_ptr<MaterialOwn> myMaterial;
  // Load Texture
  EDK3::ref_ptr<EDK3::Texture> texture;
  EDK3::Texture::Load("texture.png", &texture);
  if (!texture) {
    std::cerr << "Can't load texture.png" << std::endl;
    exit(-2);
  }

  myMaterial.alloc();
  mat_settings.alloc();
  float color[] = { 1.0, 1.0, 1.0, 1.0 };
  mat_settings->set_color(color);

  EDK3::Node *root = GameState.root.alloc();

  // Create a Drawable Node (Geometry+Material+Settings)
  EDK3::ref_ptr<EDK3::Drawable> drawable;

      mat_settings.alloc();
      float color1[] = { rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0 };
      mat_settings->set_color(color1);
      mat_settings->set_texture(texture.get());
      drawable.alloc();
      drawable->set_geometry(cube.get());
      drawable->set_material(myMaterial.get());
      drawable->set_material_settings(mat_settings.get());
      drawable->set_position(0, 0,-100);
      drawable->set_HPR(360.0f*rand() / RAND_MAX, 360.0f*rand() / RAND_MAX, 360.0f*rand() / RAND_MAX);
      root->addChild(drawable.get());
  // Create a Camera
  GameState.camera.alloc();
  float pos[] = { 0, 0, 120 };
  float view[] = { 0, 0, -120 };
  GameState.camera->set_position(pos);
  GameState.camera->set_view_direction(view);
  GameState.camera->setupPerspective(70, 8.0 / 6.0, 1.0f, 1500.0f);
  EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void render_function() {
  // Update
  GameState.root->set_rotation_y(20 * ESAT::Time() / 1000.0);


  // For Every frame... determine what's visible:
  GameState.camera->doCull(GameState.root.get());
  // Render
  EDK3::dev::GPUManager::CheckGLError("begin Render-->");
  GameState.camera->doRender();
  EDK3::dev::GPUManager::CheckGLError("end Render-->");

  // -- Orbital camera:
 double mx = ESAT::MousePositionX();
  double my = ESAT::MousePositionY();
  double p = sin(-my / 200) * 220;
  float pos[] = { p*cos(mx / 100), cos(-my / 200) * 220, p*sin(mx / 100) };
  float view[] = { -pos[0], -pos[1], -pos[2] };
  GameState.camera->set_position(pos);
  GameState.camera->set_view_direction(view);
}

int ESAT::main(int argc, char **argv) {
  ESAT::WindowInit(1200, 860);
  ESAT::DrawSetTextFont("test.ttf");
  ESAT::DrawSetTextSize(18);
  ESAT::DrawSetFillColor(255, 255, 255, 128);

 prepare();
 
  while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    
    render_function();
    ESAT::DrawText(10, 20, "EDK3 Test");
    ESAT::WindowFrame();
  }

  return 0;
}