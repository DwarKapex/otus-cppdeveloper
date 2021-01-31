/**
 * @file WindowsManager for Microsoft
 * @brief Interface for Window Managers
 * @version 0.1
 * @date 2021-01-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <Editor/WindowsManager/IWindowsManager.h>

namespace windows_manager {

class MicrosoftWindow: public IWindow {
public:

    MicrosoftWindow(const WindowConfig& config);
    bool Update() override;
};

class MicrosoftWindowsManager: public IWindowsManager {
public:
    MicrosoftWindowsManager() = default;

    // Movable only
    MicrosoftWindowsManager(const MicrosoftWindowsManager&) = delete;
    MicrosoftWindowsManager& operator=(const MicrosoftWindowsManager&) = delete;

    MicrosoftWindowsManager(MicrosoftWindowsManager&&) = default;
    MicrosoftWindowsManager& operator=(MicrosoftWindowsManager&&) = default;

    bool Update(IWindow&) override final;
    std::shared_ptr<IWindow> CreateNewWindow(const WindowConfig& config) override final;
};

} // namespace windows_manager
