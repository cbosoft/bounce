#pragma once

#include "../transform.hpp"

class RectTransform : public Transform {
public:
    RectTransform(Transform *parent, const arma::vec2 &size);
    explicit RectTransform(json j);

    void set_diagonal_preserve_aspect(double diagonal);
    void set_aspect_preserve_diagonal(double aspect);
    void set_diagonal_and_aspect(double diagonal, double aspect);
    void set_size(const arma::vec2 &size);
    [[nodiscard]] const arma::vec2 &get_size() const;

    Transform *get_bl();
    Transform *get_br();
    Transform *get_tl();
    Transform *get_tr();

    json serialise() override;

private:
    arma::vec2 _size;
    Transform *_bl, *_br, *_tl, *_tr;
};