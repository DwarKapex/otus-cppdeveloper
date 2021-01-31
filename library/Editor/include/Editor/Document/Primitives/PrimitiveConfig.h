#pragma once

#include <Editor/Document/Tools/ITool.h>
#include <Editor/Document/Color/Color.h>

#include <memory>

namespace document {

struct Position {
    float x;
    float y;
};

enum class LineStyle {
    Dash,
    Solid
};

struct PrimitiveConfig {
    Color color;
    LineStyle line_style;
    Position position;
    std::shared_ptr<ITool> tool;
};

enum class PrimitiveType {
    Circle,
    Line
};

} // namespace document
