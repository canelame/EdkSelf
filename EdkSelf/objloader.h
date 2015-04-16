#include "vector3.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class ObjReader {
public:

  std::vector<Vector3> vertices;
  std::vector<Vector3> normales;
  std::vector<Vector2> uvs;

  std::vector<Vector3> vertices_list;
  std::vector<Vector3> normales_list;
  std::vector<Vector2> uvs_list;
  std::vector<unsigned int> indexes_list;

  std::vector<unsigned int> indexes;
  std::vector<unsigned int>normal_indexes;
  std::vector<unsigned int >texture_indexes;

  void loadObjF(char *filename);

  void createGeo(Vector3 vertex_data, std::vector<Vector3> normales, std::vector<Vector2> uvs, std::vector<unsigned int> &indices,
    std::vector<Vector3> &normales_out, std::vector<Vector2> &uvs_out);

  ObjReader::ObjReader();

};