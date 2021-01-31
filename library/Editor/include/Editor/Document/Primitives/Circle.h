#pragma once

#include <Editor/Document/Primitives/IPrimitive.h>
#include <Editor/Document/Primitives/PrimitiveConfig.h>

namespace document {

class Circle: public IPrimitive {
public:
    Circle(const float radius, PrimitiveConfig config):
        IPrimitive(config), m_radius(radius) {}
private:
    float m_radius;
};

} // namespace document {