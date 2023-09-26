//
// Created by rozhin on 01.05.23.
// Copyright (c) 2021-2023 xsdnn. All rights reserved.
//

#include <common/node.h>

namespace xsdnn {

    node::~node() {}

    std::vector<edgeptr_t> &node::prev() {
        return prev_;
    }

    const std::vector<edgeptr_t> &node::prev() const {
        return prev_;
    }

    std::vector<edgeptr_t> &node::next() {
        return next_;
    }

    const std::vector<edgeptr_t> &node::next() const {
        return next_;
    }

    std::vector<node *> node::prev_nodes() const {
        std::vector<node *> vecs;
        for (auto &e : prev_) {
            if (e && e->prev()) {
                vecs.insert(vecs.end(), e->prev());
            }
        }
        return vecs;
    }

    std::vector<node *> node::next_nodes() const {
        std::vector<node *> vecs;
        for (auto &e : next_) {
            if (e) {
                auto n = e->next();
                vecs.insert(vecs.end(), n.begin(), n.end());
            }
        }
        return vecs;
    }

    BTensor* edge::get_data() {
        return &data_;
    }

    const BTensor* edge::get_data() const {
        return &data_;
    }

    tensor_type edge::ttype() const {
        return ttype_;
    }

    const shape3d &edge::shape() const {
        return shape_;
    }

    node *edge::prev() {
        return prev_;
    }

    const node *edge::prev() const {
        return prev_;
    }

    std::vector<node *> edge::next() {
        return next_;
    }

    const std::vector<node *> edge::next() const {
        return next_;
    }

    void edge::add_next_node(node *nd) {
        next_.push_back(nd);
    }
}