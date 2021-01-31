#pragma once

#include <Editor/Document/IDocument.h>

#include <filesystem>

namespace document {

class PNG : public IDocument {
public:
    PNG(const std::filesystem::path& path): IDocument(path) {}
    bool SaveAs(const std::filesystem::path& new_path, DocumentType) override {
        return true;    
    }
};

class JPG : public IDocument {
public:
    JPG(const std::filesystem::path& path): IDocument(path) {}
    bool SaveAs(const std::filesystem::path& new_path, DocumentType) override {
        return true;
    }
};

} // namespace document