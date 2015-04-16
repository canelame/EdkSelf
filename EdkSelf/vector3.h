#ifndef __H_VECTOR__
#define __H_VECTOR__


struct Vector4{
  float v[4];
  Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f){
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
  }
};
struct Vector3{
  float v[3];
  Vector3(float x = 0.0f, float y = 0.0f, float z = 1.0f){
    v[0] = x;
    v[1] = y;
    v[2] = z;

  }
};

struct Vector2{
  float v[2];
  Vector2(float x = 0.0f, float y = 0.0f){
    v[0] = x;
    
    v[1] = y;

  }
};
#endif