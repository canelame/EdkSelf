#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <ESAT/window.h>
#include <ESAT/draw.h>
#include <ESAT/sprite.h>
#include <ESAT/input.h>
#include <ESAT/time.h>

void RenderFormula() {
  static float offset = 0;
  offset += 0.01f;
  float points[2000];
  for (int i = 0; i < 1000; ++i) {
    points[i*2] = i*640.f/1000.f;
    points[i * 2 + 1] = sinf(-offset*2.f + i / 2.0f)*10.+sinf(offset + i / 20.0f)*40.f + 240.f;
  }
  ESAT::DrawSetStrokeColor(255, 0, 0);
  ESAT::DrawPath(points,1000);
}

void RenderQuad() {
  float p[] = {
    20,20,
    100,20,
    100,100,
    20,100,
    20,20, // last point connects with the first one
  };
  ESAT::DrawSetFillColor(128,64,64,200);
  ESAT::DrawSetStrokeColor(255,255,0,200);
  ESAT::DrawSolidPath(p, 5, true);
}

void RenderText() {
  ESAT::DrawSetFillColor(255, 255, 0, 255);
  ESAT::DrawSetTextSize(50);
  ESAT::DrawSetTextBlur(6);
  ESAT::DrawText(350, 200, "Hi there! ESAT :)");
  ESAT::DrawSetFillColor(200, 200, 200, 255);
  ESAT::DrawSetTextSize(50);
  ESAT::DrawSetTextBlur(0);
  ESAT::DrawText(350, 200, "Hi there! ESAT :)");
}

void RenderFPS() {
  static double last_time = ESAT::Time();
  double current_time = ESAT::Time();
  double fps = 1000.0 / (current_time - last_time);
  std::stringstream ss;
  ss << "FPS = " << std::setprecision(2) << std::fixed << fps;
  ESAT::DrawSetFillColor(0, 255, 255, 255);
  ESAT::DrawSetTextSize(40);
  ESAT::DrawSetTextBlur(0);
  ESAT::DrawText(10, 45, ss.str().c_str());
  last_time = current_time;
}

void RenderDebug() {
  std::stringstream ss;
  ss << "mouse = " << ESAT::MousePositionX() << "," << ESAT::MousePositionY();
  ESAT::DrawSetFillColor(255, 0, 255, 255);
  ESAT::DrawSetTextSize(18);
  ESAT::DrawSetTextBlur(0);
  ESAT::DrawText(10, 10, ss.str().c_str());
  // if F1 is pressed, show the content of the input buffer
  if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_F1)) {
    std::cout << "INPUT BUFFER" << std::endl;
    while (char c = ESAT::GetNextPressedKey()) {
      std::cout << c;
    }
    std::cout << std::endl << "----------------" << std::endl;
  }
}

void UpdateProceduralTexture(ESAT::SpriteHandle s, float t) {
  unsigned char sprite_data[128 * 128 * 4];
  for (int i = 0; i < 128; ++i) {
    for (int j = 0; j < 128; ++j) {
      int p = (i * 128 + j) * 4;
      sprite_data[p+0] = 155*((i/8)%2);
      sprite_data[p+1] = 155 *((j / 8) % 2);
      sprite_data[p + 2] = sinf(t*2+i/8.f)*127+128;
      sprite_data[p + 3] = sinf(t/5.f + j / 10.f) * 100 + 150;
    }
  }
  ESAT::SpriteUpdateFromMemory(s, sprite_data);
}

int ESAT::main(int argc, char **argv) {
  ESAT::WindowInit(640, 480);
  ESAT::DrawSetTextFont("test.ttf");
  ESAT::SpriteHandle sprite = ESAT::SpriteFromFile("texture.png");
  ESAT::SpriteHandle procedural_sprite = ESAT::SpriteFromMemory(128,128, (const unsigned char*)0L);
  float f = 0.f;
  while(ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    ESAT::DrawBegin();
    ESAT::DrawClear(0,0,0);
    // single line...
    ESAT::DrawSetStrokeColor(255,255,255);
    ESAT::DrawLine(0,0,640,480);
    // Draw a Sprite
    ESAT::DrawSprite(sprite, 150+60*cosf(f), 20);
    UpdateProceduralTexture(procedural_sprite, f);
    ESAT::DrawSprite(procedural_sprite, 150 + -60 * cosf(f), 220);
    // Compute a transformation matrix:
    ESAT::Mat3 m;
    ESAT::Mat3SetIdentity(&m);
    ESAT::Mat3Translate(ESAT::MousePositionX(), ESAT::MousePositionY(), &m);
    ESAT::Mat3Rotate(f, &m);
    ESAT::Mat3Scale(0.2, 0.2, &m);
    ESAT::DrawSpriteWithTransform(sprite, m);
    // more complex drawing
    RenderFormula();
    RenderQuad();
    RenderText();
    // debug
    RenderDebug();
    RenderFPS();
    ESAT::DrawEnd();
    // End of current frame
    ESAT::WindowFrame();
    f += 0.1;
  }
  ESAT::SpriteRelease(sprite);
  ESAT::WindowDestroy();
  return 0;
}