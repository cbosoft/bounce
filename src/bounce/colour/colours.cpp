#include <bounce/colour/colour.hpp>

const Colour Colours::red     = Colour::from_rgb(255,   0,   0);
const Colour Colours::green   = Colour::from_rgb(  0, 255,   0);
const Colour Colours::blue    = Colour::from_rgb(  0,   0, 255);
const Colour Colours::yellow  = Colour::from_rgb(255, 255,   0);
const Colour Colours::magenta = Colour::from_rgb(255,   0, 255);
const Colour Colours::cyan    = Colour::from_rgb(  0, 255, 255);

const Colour Colours::white      = Colour::from_grayscale_f(1.00);
const Colour Colours::light_gray = Colour::from_grayscale_f(0.75);
const Colour Colours::gray       = Colour::from_grayscale_f(0.50);
const Colour Colours::dark_gray  = Colour::from_grayscale_f(0.25);
const Colour Colours::black      = Colour::from_grayscale_f(0.00);

const Colour Colours::clear      = Colour::from_grayscale(255, 0);
