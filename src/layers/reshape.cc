//
// Created by rozhin on 17.08.2023.
// Copyright (c) 2021-2023 xsdnn. All rights reserved.
//

#include <layers/reshape.h>

namespace xsdnn {

    void reshape::set_in_shape(const xsdnn::shape3d in_shape) {
        in_shape_ = in_shape;
    }

    std::vector<shape3d> reshape::in_shape() const {
        return { in_shape_ };
    }

    std::vector<shape3d> reshape::out_shape() const {
        return { out_shape_ };
    }

    std::string reshape::layer_type() const {
        return "reshape";
    }

    void reshape::forward_propagation(const std::vector<BTensor *> &in_data,
                                      std::vector<BTensor *> &out_data) {
        *out_data[0] = *in_data[0];
    }

} // xsdnn