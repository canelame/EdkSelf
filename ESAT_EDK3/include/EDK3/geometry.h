#ifndef INCLUDE_EDK3_GEOMETRY_H_
#define INCLUDE_EDK3_GEOMETRY_H_ 1

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// Geometry Class.
// ----------------------------------------------------------------------------

#include "referenced.h"
#include "ref_ptr.h"
#include "constants.h"

namespace EDK3 {

  class Geometry : public Referenced {
  public:
    virtual bool bindAttribute(
          const Attribute a,
          unsigned int where_to_bind_attribute) const = 0;
    virtual void render() const = 0;
  protected:
    Geometry() {}
    virtual ~Geometry() {}

  private:
    Geometry(const Geometry&);
    Geometry& operator=(const Geometry &);
  };

  void CreateCube(
      ref_ptr<Geometry> *output,
      const float cube_size = 1.0f,
      const bool build_normals = true,
      const bool build_tex_coords = true);

  void CreateQuad(
      ref_ptr<Geometry> *output, 
      const float width = 1.0f,
      const float height = 1.0f,
      const bool build_normals = true,
      const bool build_tex_coords = true);

} /* end of EDK Namespace */

#endif
