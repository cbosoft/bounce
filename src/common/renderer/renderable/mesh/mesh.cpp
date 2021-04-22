#include "mesh.hpp"

void MeshRenderable::set_alignment(MeshRenderable_HorizontalAnchor ha, MeshRenderable_VerticalAnchor va)
{
    const double f = .5;
    switch (ha)
    {
        case MR_HA_CENTRE:
            this->_anchor[0] = 0.0;
            break;

        case MR_HA_LEFT:
            this->_anchor[0] = f;
            break;

        case MR_HA_RIGHT:
            this->_anchor[0] = -f;
            break;
    }
    switch (va)
    {
        case MR_VA_CENTRE:
            this->_anchor[1] = 0.0;
            break;

        case MR_VA_BOTTOM:
            this->_anchor[1] = f;
            break;

        case MR_VA_TOP:
            this->_anchor[1] = -f;
            break;
    }
}
