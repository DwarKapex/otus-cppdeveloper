/**
 * \file IEditor.h
 * \author Vladislav Kozlov
 * \brief Interface for Editor
 * \version 0.1
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <Editor/WindowsManager/IWindowsManager.h>
#include <Editor/WindowsManager/MicrosoftWindowsManager.h>
#include <Editor/WindowsManager/GnomeWindowsManager.h>
#include <Editor/Document/DocumentType.h>
#include <Editor/Document/IDocument.h>
#include <Editor/Document/Primitives/Circle.h>
#include <Editor/Document/Primitives/Line.h>
#include <Editor/Document/Primitives/PrimitiveConfig.h>

#include <filesystem>
#include <algorithm>


#if !defined(__LINUX__)
#define __LINUX__ 1
#endif

#if !defined(__WINDOWS__)
#define __WINDOWS__ !(__LINUX__)
#endif

template <typename PrimitiveType, typename PrimitiveConfig>
class IEditor {
public:
    IEditor();

    virtual std::shared_ptr<document::IDocument> CreateNewDocument(const std::filesystem::path&, document::DocumentType) = 0;
    virtual void ImportDocument(const std::filesystem::path& path) = 0;
    virtual void ExportDocument(const std::filesystem::path& path, document::DocumentType) = 0;
    void CreatePrimitive(std::shared_ptr<PrimitiveType> new_primitive);
    void RemovePrimitive(std::shared_ptr<PrimitiveType> primitive);
    void SetActiveDocument();
    
    virtual ~IEditor();
protected:
    void Update();

    std::unique_ptr<windows_manager::IWindowsManager> m_windows_manager;
    std::shared_ptr<windows_manager::IWindow> m_active_window;
    std::vector<std::shared_ptr<document::IDocument>> m_documents;
    std::shared_ptr<document::IDocument> m_active_document;

};

template <typename PrimitiveType, typename PrimitiveConfig>
IEditor<PrimitiveType, PrimitiveConfig>::IEditor() {
    if constexpr(__LINUX__) {
        m_windows_manager = std::make_unique<windows_manager::GnomeWindowsManager>();
    } else if constexpr (__WINDOWS__) {
        m_windows_manager = std::make_unique<windows_manager::MicrosoftWindowsManager>();
    } else {
        throw std::runtime_error("No available Windows Manager.");
    }
    m_active_window = m_windows_manager->CreateNewWindow({0,0, {0,0}});
}

template <typename PrimitiveType, typename PrimitiveConfig>
void IEditor<PrimitiveType, PrimitiveConfig>::CreatePrimitive(std::shared_ptr<PrimitiveType> new_primitive) {
    m_active_document->AddPrimitive(new_primitive);
    this->Update();
}

template <typename PrimitiveType, typename PrimitiveConfig>
void IEditor<PrimitiveType, PrimitiveConfig>::RemovePrimitive(std::shared_ptr<PrimitiveType> primitive) {
    std::remove(m_active_document->GetAllPrimitives().begin(), m_active_document->GetAllPrimitives().end(), primitive);
    this->Update();
}

template <typename PrimitiveType, typename PrimitiveConfig>
void IEditor<PrimitiveType, PrimitiveConfig>::SetActiveDocument() {}

template <typename PrimitiveType, typename PrimitiveConfig>
void IEditor<PrimitiveType, PrimitiveConfig>::Update() { 
    m_active_document->Update(); 
    m_active_window->Update();
};

template <typename PrimitiveType, typename PrimitiveConfig>
IEditor<PrimitiveType, PrimitiveConfig>::~IEditor() = default;