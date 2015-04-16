/* Copyright 2015 ESAT. All rights reserved.    #####  #####      #     #####
 * Author: Jose L. Hidalgo <jlhidalgo@esat.es>  #      #         # #      #
 *                                              ###     ###     #   #     #
 * Math reference methods                       #          #   #     #    #
 *                                              #####  #####  #       #   #
 */

#ifndef ESAT_MATH_H
#define ESAT_MATH_H 1

namespace ESAT {

  struct Mat3 { float d[9]; };
  void Mat3Multiply(const Mat3 &a, const Mat3 &b, Mat3 *output);

  void Mat3SetIdentity(Mat3 *output);
  void Mat3SetTranslate(float translate_x, float translate_y, Mat3 *output);
  void Mat3SetRotate(float radians, Mat3 *output);
  void Mat3SetScale(float scale_x, float scale_y, Mat3 *output);

  void Mat3Translate(float translate_x, float translate_y, Mat3 *in_out);
  void Mat3Rotate(float radians, Mat3 *in_out);
  void Mat3Scale(float scale_x, float scale_y, Mat3 *in_out);

  void Mat3Copy(const Mat3 &origin, Mat3 *dst);
  void Mat3Transform(const Mat3 &a, const float v[3], float v_output[3]);

} /* ESAT */

#endif
