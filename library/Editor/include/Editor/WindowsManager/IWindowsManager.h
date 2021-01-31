/**
 * @file IWindowsManager.h
 * @brief Interface for Window Managers. Of caurse, it's better to move it to a seperate
 * library, but for educational purposes let's leave it here.
 * @version 0.1
 * @date 2021-01-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <Editor/WindowsManager/WindowConfig.h>

#include <vector>
#include <memory>

namespace windows_manager {

class IWindow {
public:
    IWindow(const WindowConfig& config): m_config(config) {}
    virtual bool Update() = 0;

    virtual ~IWindow() = default;
protected:
    WindowConfig m_config;
};

class IWindowsManager {
public:
    IWindowsManager() = default;

    // movable only. There should be only 1 WindowManager in a system
    IWindowsManager(const IWindowsManager&) = delete;
    IWindowsManager& operator=(const IWindowsManager&) = delete;
    IWindowsManager(IWindowsManager&&) = default;
    IWindowsManager& operator=(IWindowsManager&&) = default;

    virtual bool Update(IWindow&) = 0;
    virtual std::shared_ptr<IWindow> CreateNewWindow(const WindowConfig& config) = 0;

    virtual ~IWindowsManager() = default;

protected:
    std::vector<std::shared_ptr<IWindow>> m_windows;
};

} // namespace windows_manager
