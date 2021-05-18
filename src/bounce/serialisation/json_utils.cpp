#include <bounce/serialisation/json.hpp>

json vec2json(const arma::vec2 &vec)
{
    double x = vec[0];
    double y = vec[1];
    return {x, y};
}

arma::vec2 jsonvec2(json j)
{
    double x = j[0];
    double y = j[1];
    return {x, y};
}