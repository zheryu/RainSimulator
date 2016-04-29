#include "sampler.h"

namespace CGL {

// Uniform Sampler2D Implementation //

Vector2D UniformGridSampler2D::get_sample() const {

  return Vector2D(random_uniform(), random_uniform());

}

JitteredGridSampler2D::JitteredGridSampler2D(int n){
  if(n <= 1){
    n = 1;
  }
  this->n = n;
  this->subpixel_width = 1.0/n;

}

Vector2D JitteredGridSampler2D::get_sample() const {

  return Vector2D(random_uniform(), random_uniform());

}

Vector2D JitteredGridSampler2D::get_sample(int box_num) const {
  int sub_x = box_num%n;
  int sub_y = box_num/n;
  double  randx = random_uniform()/n,
          randy = random_uniform()/n;
  Vector2D retVec = Vector2D(randx + (subpixel_width * sub_x), randy + (subpixel_width * sub_y));
}


// Uniform Hemisphere Sampler3D Implementation //

Vector3D UniformHemisphereSampler3D::get_sample() const {

  double Xi1 = random_uniform();
  double Xi2 = random_uniform();

  double theta = acos(Xi1);
  double phi = 2.0 * PI * Xi2;

  double xs = sinf(theta) * cosf(phi);
  double ys = sinf(theta) * sinf(phi);
  double zs = cosf(theta);

  return Vector3D(xs, ys, zs);

}

Vector3D CosineWeightedHemisphereSampler3D::get_sample() const {
  float f;
  return get_sample(&f);
}

Vector3D CosineWeightedHemisphereSampler3D::get_sample(float *pdf) const {

  double Xi1 = random_uniform();
  double Xi2 = random_uniform();

  double r = sqrt(Xi1);
  double theta = 2. * PI * Xi2;
  *pdf = sqrt(1-Xi1) / PI;
  return Vector3D(r*cos(theta), r*sin(theta), sqrt(1-Xi1));
}


} // namespace CGL
