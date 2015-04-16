#include "objloader.h"
unsigned int face3(std::string line){
  unsigned int type = 0;
  bool hash_find = false;
  for (int i = 0; i < line.length(); i++){
    if ((line[i] == '/' && line[i + 1] == '/')){
      type = 2;
      hash_find = true;
    }
    else if (line[i] == '/' && line[i + 1] != '/'){

      type = 3;
      hash_find = true;
    }
    else if(hash_find!=true) {
      type = 1;
    }
  }
  return type;
}

void ObjReader::loadObjF(char *filename){


  std::string line;


  float temp_vert;
  float temp_uv;
  int temp_index;
  int count_line = 0;
  bool faces = false;

  Vector3 vertex_indexes[3];
  Vector3 vertices_temp;
  Vector2 normales_temp;
  std::string x, y, z;
  std::string i1, i2, i3;

  std::ifstream myobj("cube.obj");
  if (myobj.is_open()){
    while (!myobj.eof()){
     
        count_line++;
        printf("Reading file..\n %d", count_line);
        std::getline(myobj, line);
        std::istringstream iss(line);
        if (line[0] == 'v' && line[1] == ' '){
          std::istringstream iss(line.substr(2));
          iss >> x >> y >> z;
          temp_vert = atof(x.c_str());
          vertices_temp.v[0] = temp_vert;

          temp_vert = atof(y.c_str());
          vertices_temp.v[1] = temp_vert;

          temp_vert = atof(z.c_str());
          vertices_temp.v[2] = temp_vert;

          vertices.push_back(vertices_temp);


        }
        else if (line[0] == 'v' && line[1] == 'n'){

          std::istringstream iss(line.substr(2));
          iss >> x >> y >> z;

          temp_vert = atof(x.c_str());
          vertices_temp.v[0] = temp_vert;

          temp_vert = atof(y.c_str());
          vertices_temp.v[1] = temp_vert;

          temp_vert = atof(z.c_str());
          vertices_temp.v[2] = temp_vert;

          normales.push_back(vertices_temp);

        }
        else if (line[0] == 'v' && line[1] == 't'){
          std::istringstream iss(line.substr(2));
          iss >> x >> y;
          temp_uv = atof(x.c_str());
          normales_temp.v[0] = temp_uv;

          temp_uv = atof(y.c_str());
          normales_temp.v[1] = temp_uv;
          uvs.push_back(normales_temp);
        }
        else if (line[0] == 'f'){
          if (!faces){
            
            //normales_list.reserve();

          }
            std::istringstream iss(line.substr(2));
            unsigned int type_f = face3(iss.str());
            std::string temp_iv;
            std::string temp_in;
            std::string temp_iu;         
            //Normal form
            switch (type_f)
            {
            case 1:
            iss >> i1 >> i2 >> i3;
            // = atoi(i1.c_str()));
            indexes.push_back(temp_index = atoi(i2.c_str()));
            indexes.push_back(temp_index = atoi(i3.c_str()));
            break;
            case 2:
            //iss >> i1 >> i2 >> i3;


            break;
            case 3:
            iss >> x >> y >> z;

            //V
            for (int i = 0; i < x.size(); i++){
              if (i == 0){
              temp_iv = x.at(i);
              vertex_indexes[0].v[0] = atoi(temp_iv.c_str());
              }

              if (i == 2){
              temp_iu = x.at(i);
              vertex_indexes[0].v[1] = atoi(temp_iu.c_str());
          
              }

              if (i == 4){
              temp_in = x.at(i);
              vertex_indexes[0].v[2] = atoi(temp_iu.c_str());;
              }

            }

            //UV

            for (int i = 0; i < y.size(); i++){
              if (i == 0){
              temp_iv = y.at(i);
              vertex_indexes[1].v[0] = atoi(temp_iv.c_str());
              }

              if (i == 2){
              temp_iu = y.at(i);

              vertex_indexes[1].v[1] = atoi(temp_iu.c_str());
              }

              if (i == 4){
              temp_in = y.at(i);
              vertex_indexes[1].v[2] = atoi(temp_in.c_str());
              }

            }
           //NORMAL
            for (int i = 0; i < z.size(); i++){
              if (i == 0){
              temp_iv = z.at(i);
              vertex_indexes[2].v[0] = atoi(temp_iv.c_str());
              }

              if (i == 2){
              temp_iu = z.at(i);
              vertex_indexes[2].v[1] = atoi(temp_iu.c_str());
              }

              if (i == 4){
              temp_in = z.at(i);
              vertex_indexes[2].v[2] = atoi(temp_in.c_str());
              }
            }



            break;

            default:
            break;
            }


            //TODO: Process vertexs
            createGeo(vertex_indexes[0], normales, uvs, indexes,normales_list,uvs_list);
            createGeo(vertex_indexes[1], normales, uvs, indexes, normales_list, uvs_list);
            createGeo(vertex_indexes[2], normales, uvs, indexes, normales_list, uvs_list);

        }
      

    }
    
    myobj.close();

    int vertexPointer = 0;
    for (std::vector<Vector3 >::iterator cit = vertices.begin(); cit != vertices.end(); ++cit){
    
      vertices_list.push_back(cit->v[0]);
      vertices_list.push_back( cit->v[1]);
      vertices_list.push_back( cit->v[2]);

    }

    for (int i = 0; i < indexes.size(); i++){
      indexes_list.push_back( indexes.at(i));
    }

  }
  else{ printf("Error to open file"); }

 
    // Get the attributes thanks to the index



    /* vertexIndex *= 3;
     

    
     temp_indexes.push_back(count);

     //std::vector<float> uv = texture_indexes[uvIndex - 1];
     //std::vector<float> normal = normal_indexes[normalIndex - 1];

     // Put the attributes in buffers
     //out_vertices.push_back(vertex);
     //.push_back(uv);
     //out_normals.push_back(normal);

     }
     indexes = temp_indexes;
     vertices.clear();
     vertices = temp_vertex;
     normales.clear();
     normales = temp_normal;
     uvs.clear();
     uvs = temp_uv_in;
     indexes.clear();
     indexes = temp_indexes;

     printf("Vertices\n");
     for (int i = 0; i < vertices.size(); i+=3){
     std::cout << vertices[i] << "\t" << vertices[i+1] << "\t" << vertices[i+2] << std::endl;
     }

     printf("Normales\n");
     for (int i = 0; i < normales.size(); i+=3){
     std::cout  << normales.i] << "\t" << normales[i+1] << "\t" << normales[i+2] << std::endl;
     }

     printf("CAras\n");
     for (int i = 0; i < indexes.size(); i++){
     std::cout << indexes[i];
     if (i % 3 == 0 && i!=0) printf("\n");
     }*/


  }


ObjReader::ObjReader(){

}



void ObjReader::createGeo(Vector3 vertex_data, std::vector<Vector3> normales, std::vector<Vector2> uvs, std::vector<unsigned int> &indices,
                          std::vector<Vector3> &normales_out,std::vector<Vector2> &uvs_out){

  std::vector<float> temp_vertex;
  std::vector<float> temp_normal;
  std::vector<float>temp_uv_in;
  //Triangles for each vertex
  std::vector<unsigned int> temp_indexes;
  int count = 0;
 

    // Get the indices of its attributes
    unsigned int vertexIndex = vertex_data.v[0] - 1;
   
    indices.push_back(vertexIndex);


    Vector2 currentTexture = uvs.at(vertex_data.v[1] - 1);
  
    
   // uvs_out[vertexIndex * 2] = currentTexture.v[0];
    uvs_out.push_back(currentTexture);
   // uvs_out[vertexIndex * 2+1] = currentTexture.v[1];

    Vector3 currentNorm = normales.at(vertex_data.v[2] - 1);

   // normales_out[vertexIndex * 3] = currentNorm.v[0];
    //normales_out[vertexIndex * 3+1] = currentNorm.v[1];
   // normales_out[vertexIndex * 3+2] = currentNorm.v[2];
    normales_out.push_back (currentNorm);
  
  }
  