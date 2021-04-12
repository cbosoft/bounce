#include "menuitem.hpp"

constexpr static double highlight_dr = 5.0;

void MenuItem::highlight()
{
    double r = this->get_radius();
    this->set_radius(r + highlight_dr);
}

void MenuItem::unhighlight()
{
    double r = this->get_radius();
    this->set_radius(r - highlight_dr);
}