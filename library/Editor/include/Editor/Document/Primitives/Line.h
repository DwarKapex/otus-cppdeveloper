#pragma once

#include <Editor/Document/Primitives/IPrimitive.h>
#include <Editor/Document/Primitives/PrimitiveConfig.h>

namespace document {

class Line: public IPrimitive {
public:
    Line(const float width, PrimitiveConfig config):
        IPrimitive(config), m_width(width) {}
private:
    float m_width;
};

} // namespace document {