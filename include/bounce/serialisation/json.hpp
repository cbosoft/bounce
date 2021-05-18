#pragma once

#include <armadillo>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json vec2json(const arma::vec2 &vec);
arma::vec2 jsonvec2(json j);