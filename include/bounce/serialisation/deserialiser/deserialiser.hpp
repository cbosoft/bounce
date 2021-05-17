#pragma once

#include "../json.hpp"
#include "../../transform/transform.hpp"

class Deserialiser {
public:
    [[nodiscard]] virtual Transform *deserialise(json j);
};