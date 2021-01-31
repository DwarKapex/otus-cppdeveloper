/**
 * @file WindowConfig.h
 * @brief Configuration for a newly created Window
 * @version 0.1
 * @date 2021-01-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <stddef.h>

namespace windows_manager {

struct Position {
    float x;
    float y;
};

struct WindowConfig {
    size_t width;
    size_t height;
    Position position;
};

} // namespace windows_manager