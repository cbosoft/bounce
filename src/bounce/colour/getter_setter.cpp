#include <bounce/colour/colour.hpp>

/** Return Red component as float in range 0-1. */
float Colour::rf() const { return float(this->r)/255.0f; }

/** Return Green component as float in range 0-1. */
float Colour::gf() const { return float(this->g)/255.0f; }

/** Return Blue component as float in range 0-1. */
float Colour::bf() const { return float(this->b)/255.0f; }

/** Return Alpha component as float in range 0-1. */
float Colour::af() const { return float(this->a)/255.0f; }
