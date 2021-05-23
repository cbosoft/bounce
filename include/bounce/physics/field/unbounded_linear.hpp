#include "field.hpp"

class UnboundedLinearForceField : public ForceField {
public:
    UnboundedLinearForceField(double mx, double cx, double my, double cy);

private:
    arma::vec2 f(Rigidbody *obj) const override;
    double mx, cx, my, cy;
};