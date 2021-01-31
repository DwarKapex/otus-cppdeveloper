#pragma once

#include <Editor/Document/Primitives/PrimitiveConfig.h>

namespace document {

class IPrimitive {
public:
    IPrimitive(const PrimitiveConfig& config):
        m_config(config) {}
protected:
    PrimitiveConfig m_config;
};

} // namespace document {