#include <Editor/GraphicEditor.h>
#include <Editor/Document/Document.h>

namespace fs = std::filesystem;
using namespace document;

std::shared_ptr<IDocument> GraphicEditor::CreateNewDocument(const fs::path& path, DocumentType type) {
    std::shared_ptr<IDocument> new_doc = nullptr;
    switch (type) {
        case DocumentType::JPG:
            new_doc = std::make_shared<JPG>(path);
            break;
        case DocumentType::PNG:
            new_doc = std::make_shared<PNG>(path);
    }

    m_documents.push_back(new_doc);
    return new_doc;    
}

DocumentType GraphicEditor::GetDocumentType(const fs::path& path) {
    return DocumentType::JPG;
}

void GraphicEditor::ImportDocument(const fs::path& path) {
    auto doc_type = GetDocumentType(path);
    CreateNewDocument(path, doc_type);
}

void GraphicEditor::ExportDocument(const fs::path& path, DocumentType type) {
    m_active_document->SaveAs(path, type);
}