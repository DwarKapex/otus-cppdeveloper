/**
 * @file WindowsManager for Linux (Gnome)
 * @brief Interface for Window Managers
 * @version 0.1
 * @date 2021-01-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <Editor/WindowsManager/IWindowsManager.h>
#include <memory>

namespace windows_manager {

class GnomeWindow: public IWindow {
public:
    GnomeWindow(const WindowConfig& config);
    bool Update() override;
};

class GnomeWindowsManager: public IWindowsManager {
public:
    GnomeWindowsManager() = default;

    // Movable only
    GnomeWindowsManager(const GnomeWindowsManager&) = delete;
    GnomeWindowsManager& operator=(const GnomeWindowsManager&) = delete;

    GnomeWindowsManager(GnomeWindowsManager&&) = default;
    GnomeWindowsManager& operator=(GnomeWindowsManager&&) = default;

    bool Update(IWindow&) override final;
    std::shared_ptr<IWindow> CreateNewWindow(const WindowConfig& config) override final;
};

} // namespace windows_manager
