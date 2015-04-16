#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/dev/gpumanager.h>

#include <iostream>
#include <cmath>

struct {
  EDK3::ref_ptr<EDK3::Camera> camera;
  EDK3::ref_ptr<EDK3::Node> root;
} GameState;

void prepare() {
  EDK3::dev::GPUManager::CheckGLError("Prepare Start");
  EDK3::ref_ptr<EDK3::MatDiffuse> mat;
  EDK3::ref_ptr<EDK3::MatDiffuse::Settings> mat_settings;

  mat.alloc();
  mat_settings.alloc();
  float color[] = { 1.0, 0.0, 0.0, 1.0 };
  mat_settings->set_color(color);

  EDK3::Node *root = GameState.root.alloc();
  EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry> > geometries;
  EDK3::scoped_array<char> output;
  if (!EDK3::LoadObj("Cube.obj", &geometries, &output)) {
	  std::cerr << "Error loading model " << output.get() << std::endl;
	  exit(-3);
  }
  // Create a Drawable Node (Geometry+Material+Settings)
  EDK3::ref_ptr<EDK3::Drawable> drawable;
  for(int i = 0; i < geometries.size(); ++i){
    mat_settings.alloc();
    float color[] = { rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, 1.0 };
    mat_settings->set_color(color);
    drawable.alloc();
    drawable->set_geometry(geometries[i].get());
    drawable->set_material(mat.get());
    drawable->set_material_settings(mat_settings.get());
    root->addChild(drawable.get());
  }

  // Create a Camera
  GameState.camera.alloc();
  GameState.camera->setupPerspective(70, 8.0/6.0, 1.0f, 1500.0f);
  EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void render_function() {
  // Update
  GameState.root->set_rotation_y(5*ESAT::Time()/1000.0);
  

  // For Every frame... determine what's visible:
  GameState.camera->doCull(GameState.root.get());
  // Render
  EDK3::dev::GPUManager::CheckGLError("begin Render-->");
  GameState.camera->doRender();
  EDK3::dev::GPUManager::CheckGLError("end Render-->");

  // -- Orbital camera:
  double mx = ESAT::MousePositionX();
  double my = ESAT::MousePositionY();
  double p = sin(-my/200)*120;
  float pos[] = {p*cos(mx/100),cos(-my/200)*220, p*sin(mx/100)};
  float view[] = {-pos[0],-pos[1],-pos[2]};
  GameState.camera->set_position(pos);
  GameState.camera->set_view_direction(view);
}

int ESAT::main(int argc, char **argv) {
  ESAT::WindowInit(640, 480);
  ESAT::DrawSetTextFont("test.ttf");
  ESAT::DrawSetTextSize(18);
  ESAT::DrawSetFillColor(255,255,255,128);
  prepare();
  int c = 0; 
  while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    render_function();
    ESAT::DrawBegin();
    ESAT::DrawText(10, 20, "EDK3 Test");
    if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Alt)) { std::cout << "Alt" << c++<<std::endl; }
    if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Shift)) { std::cout << "Shift" << c++<<std::endl; }
    if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Control)) { std::cout << "Control" << c++<<std::endl; }
    ESAT::DrawEnd();
    ESAT::WindowFrame();
  }
  
  return 0;
}
