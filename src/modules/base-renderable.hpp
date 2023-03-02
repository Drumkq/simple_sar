#pragma once

#include "features/graphics-handler.hpp"

class base_renderable {
protected:
    base_renderable() {
        modules::features::graphics_handler::add_render_callback(this, &base_renderable::render);
    }
    virtual ~base_renderable() = default;

    virtual void render() = 0;
};
