//
// Created by rozhin on 27.07.2023.
// Copyright (c) 2021-2023 xsdnn. All rights reserved.
//

#ifndef XSDNN_AND_H
#define XSDNN_AND_H

#include "layer.h"

namespace xsdnn {

class and_layer : public layer {
public:
    explicit and_layer()
            : layer({TypeHolder(tensor_type::data, XsDtype::F32),
                     TypeHolder(tensor_type::data, XsDtype::F32)},
                    {TypeHolder(tensor_type::data, XsDtype::F32)}),
              shape_() {}

    explicit and_layer(shape3d shape)
    : layer({TypeHolder(tensor_type::data, XsDtype::F32),
             TypeHolder(tensor_type::data, XsDtype::F32)},
            {TypeHolder(tensor_type::data, XsDtype::F32)}),
    shape_(shape) {}

    explicit and_layer(size_t dim)
    : layer({TypeHolder(tensor_type::data, XsDtype::F32),
             TypeHolder(tensor_type::data, XsDtype::F32)},
            {TypeHolder(tensor_type::data, XsDtype::F32)}),

      shape_(1, 1, dim) {}

public:
    void set_in_shape(const xsdnn::shape3d in_shape);
    std::vector<shape3d> in_shape() const;
    std::vector<shape3d> out_shape() const;
    std::string layer_type() const;

    void
    forward_propagation(const std::vector<BTensor *>& in_data,
                        std::vector<BTensor *>& out_data);

private:
    bool contains_only_one_zero(const BTensor & mat);

private:
    shape3d shape_;
};

} // xsdnn

#endif //XSDNN_AND_H
