/**
 * @file MicrosoftWindowsManager.cpp
 * @brief  Implementation for Windows Manager from Microsoft
 * @version 0.1
 * @date 2021-01-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <Editor/WindowsManager/MicrosoftWindowsManager.h>

#include <iostream>

namespace windows_manager {

MicrosoftWindow::MicrosoftWindow(const WindowConfig& config):
    IWindow(config) {}

bool MicrosoftWindow::Update() {
    std::cout << "Updated Microsoft Window\n";
    return true;
}

bool MicrosoftWindowsManager::Update(IWindow&) {
    for (auto& window: m_windows) {
        window->Update();
    }
    return true;
}

std::shared_ptr<IWindow> MicrosoftWindowsManager::CreateNewWindow(const WindowConfig& config) {
    auto new_window = std::make_shared<MicrosoftWindow>(config);
    m_windows.push_back(new_window);
    return new_window;
}

} // namespace windows_manager