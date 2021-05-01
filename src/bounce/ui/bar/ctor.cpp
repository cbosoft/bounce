#include <bounce/ui/bar/bar.hpp>

BarGraph::BarGraph(double w, double h)
:   RectangleMeshRenderable(w, h)
{
    this->set_alignment(MR_HA_LEFT, MR_VA_CENTRE);
}