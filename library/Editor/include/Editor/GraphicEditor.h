/**
 * \file Editor.h
 * \brief Declaration of Simple Vector Graphics Editor
 * \version 0.1
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <Editor/IEditor.h>
#include <Editor/Document/IDocument.h>
#include <Editor/Document/DocumentType.h>
#include <filesystem>

class GraphicEditor: public IEditor<document::IPrimitive, document::PrimitiveConfig> {
public:
    std::shared_ptr<document::IDocument> CreateNewDocument(const std::filesystem::path& path, document::DocumentType) override;
    void ImportDocument(const std::filesystem::path& path) override;
    void ExportDocument(const std::filesystem::path& path, document::DocumentType) override;

private:
    document::DocumentType GetDocumentType(const std::filesystem::path& path);
};