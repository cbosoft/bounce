#include "colour.hpp"

float Colour::rf() const { return float(this->r)/255.0f; }
float Colour::gf() const { return float(this->g)/255.0f; }
float Colour::bf() const { return float(this->b)/255.0f; }
