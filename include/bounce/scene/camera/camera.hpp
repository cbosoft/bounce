#pragma once

#include "../../transform/rect/rect.hpp"

class Camera : public RectTransform {
public:
    explicit Camera(Transform *parent, const arma::vec2& size, const std::string &name);
    explicit Camera(json j);

    json serialise() override;

    [[nodiscard]] const std::string &get_name() const;

private:
    const std::string _name;
};