/**
 * @file GnomeWindowsManager.cpp
 * @brief  Implementation for GNU Linux (Gnome)
 * @version 0.1
 * @date 2021-01-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <Editor/WindowsManager/GnomeWindowsManager.h>

#include <iostream>

namespace windows_manager {

GnomeWindow::GnomeWindow(const WindowConfig& config):
    IWindow(config) {}

bool GnomeWindow::Update() {
    return true;
}

bool GnomeWindowsManager::Update(IWindow&) {
    for (auto& window: m_windows) {
        window->Update();
    }
    return true;
}

std::shared_ptr<IWindow> GnomeWindowsManager::CreateNewWindow(const WindowConfig& config) {
    auto new_window = std::make_shared<GnomeWindow>(config);
    m_windows.push_back(new_window);
    return new_window;
}

} // namespace windows_manager