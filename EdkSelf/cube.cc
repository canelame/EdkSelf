#include "cube.h"
#include <vector>
#include "vector3.h"
#include "objloader.h"
Cube::Cube(){





}


const std::vector<Vector2> uvs;

ObjReader *ojLoader;
int vertex_size = 0;
int normal_size = 0;
int uv_size = 0;
int index_size = 0;
int total_index = 0;


/*void Cube::init(int size){

  ojLoader = new ObjReader();
  ojLoader->loadObjF("quad.obj");

   std::vector<Vector3> *vertices = &ojLoader->vertices_list;
   std::vector<Vector3> *normales = &ojLoader->normales_list;
   std::vector<Vector2> *uvs = &ojLoader->uvs_list;
   std::vector<unsigned int> *indexes = &ojLoader->indexes_list;

   const int vertices_size = sizeof(Vector3)*vertices->size() + sizeof(vertices);
   const int normales_size = sizeof(Vector3)*normales->size() + sizeof(normales);
   const int uv_size = sizeof(Vector2)*uvs->size() + sizeof(uvs);
   const int indexes_size = sizeof(unsigned int)*indexes->size() + sizeof(indexes);
   //int temp_index = 5;

   

   

  EDK3::dev::GPUManager::Instance()->newBuffer(&vertices_);
  EDK3::dev::GPUManager::Instance()->newBuffer(&normales_);
  EDK3::dev::GPUManager::Instance()->newBuffer(&uvs_);
  EDK3::dev::GPUManager::Instance()->newBuffer(&indices_);

  for (std::vector<Vector3 >::iterator cit = vertices->begin(); cit != vertices->end(); ++cit){
    cit->v[0]*=size;
    cit->v[1] *= size;
    cit->v[2] *= size;
  }




  total_index = indexes->size();



  vertices_->init(vertices_size);
 normales_->init(normales_size);
  uvs_->init(uv_size);
  indices_->init(indexes_size);


  vertices_->uploadData(vertices, vertices_size, 0);

  normales_->uploadData(normales, normales_size, 0);

  uvs_->uploadData(uvs, uv_size, 0);

  indices_->uploadData(indexes, indexes_size, 0);

  //delete ojLoader; ojLoader = NULL;
}*/

void Cube::init(int size){
    
  const float cube_positions[216]{
    //Cara 0
    -1 * size, -1 * size, 1 * size,
      1 * size, -1 * size, 1 * size,
      1 * size, 1 * size, 1 * size,
      -1 * size, 1 * size, 1 * size,

      //cara 1

      -1 * size, -1 * size, -1 * size,
      1 * size, -1 * size, -1 * size,
      1 * size, -1 * size, 1 * size,
      -1 * size, -1 * size, 1 * size,

      //cara 2

      -1 * size, -1 * size, -1 * size,
      -1 * size, -1 * size, 1 * size,
      -1 * size, 1 * size, 1 * size,
      -1 * size, 1 * size, -1 * size,

      //cara 3

      1 * size, -1 * size, 1 * size,
      1 * size, -1 * size, -1 * size,
      1 * size, 1 * size, -1 * size,
      1 * size, 1 * size, 1 * size,

      //cara 4

      -1 * size, 1 * size, 1 * size,
      1 * size, 1 * size, 1 * size,
      1 * size, 1 * size, -1 * size,
      -1 * size, 1 * size, -1 * size,

      //cara 5

      -1 * size, 1 * size, -1 * size,
      1 * size, 1 * size, -1 * size,
      1 * size, -1 * size, -1 * size,
      -1 * size, -1 * size, -1 * size,

      //UVS
      0, 0,
      0, 1,
      1, 1,
      1, 0,

      0, 0,
      0, 1,
      1, 1,
      1, 0,

      0, 0,
      0, 1,
      1, 1,
      1, 0,

      0, 0,
      0, 1,
      1, 1,
      1, 0,

      0, 0,
      0, 1,
      1, 1,
      1, 0,

      0, 0,
      0, 1,
      1, 1,
      1, 0,

      //Normales

      0, 0, 1,
      0, 0, 1,
      0, 0, 1,
      0, 0, 1,

      0, -1, 0,
      0, -1, 0,
      0, -1, 0,
      0, -1, 0,

      -1, 0, 0,
      -1, 0, 0,
      -1, 0, 0,
      -1, 0, 0,

      1, 0, 0,
      1, 0, 0,
      1, 0, 0,
      1, 0, 0,

      0, 1, 0,
      0, 1, 0,
      0, 1, 0,
      0, 1, 0,

      0, 0, -1,
      0, 0, -1,
      0, 0, -1,
      0, 0, -1
  };

  unsigned int indexes_cube[36]{


    //indices
     0, 1, 2, 
     0, 2, 3,

      4, 5, 6,
      4, 6, 7,

      8, 9, 10,
      8, 10, 11,

      12, 13, 14,
      12, 14, 15,

      16, 17, 18,
      16, 18, 19,

      20, 21, 22,
      20, 22, 23 };


  EDK3::dev::GPUManager::Instance()->newBuffer(&attributes);
  attributes->init(sizeof(float) * 216 + sizeof(unsigned int) * 36);

  attributes->uploadData(cube_positions, sizeof(float) * 216, 0);
  attributes->uploadData(indexes_cube, sizeof(unsigned int) * 36, sizeof(float) * 216);
}

bool Cube::bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute)const{
  switch (a)  {
  case EDK3::Attribute::A_POSITION:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(attributes.get(),
      where_to_bind_attribute, EDK3::T_FLOAT_3,
      false,0 , 0
      );
    return true;

  case EDK3::Attribute::A_NORMAL:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(attributes.get(),
      where_to_bind_attribute, EDK3::T_FLOAT_3,
      true, sizeof(float) * 72, 0
      );

    return true;

  case EDK3::Attribute::A_UV:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(attributes.get(),
      where_to_bind_attribute, EDK3::T_FLOAT_2,
      false, sizeof(float) * 120, 0
      );
    return true;
  default:
    return false;
  }
  return false;
}

void Cube::render()const {
  EDK3::dev::GPUManager::Instance()->drawElements(EDK3::dev::GPUManager::kDrawMode_Triangles, 36, attributes.get(),EDK3::T_UINT_1, sizeof(float)*216);
  
}

