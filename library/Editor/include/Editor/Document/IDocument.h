#pragma once

#include <Editor/Document/Primitives/IPrimitive.h>
#include <Editor/Document/DocumentType.h>

#include <filesystem>
#include <vector>

namespace document {

class IDocument {
public:
    IDocument(const std::filesystem::path& path) :
        m_path(path) {}

    virtual bool SaveAs(const std::filesystem::path& new_path, DocumentType) = 0;

    bool AddPrimitive(const std::shared_ptr<IPrimitive> primitive) {
        m_primitives.push_back(primitive);
        return true;
    }

    virtual void Update() {};

    std::vector<std::shared_ptr<IPrimitive>>& GetAllPrimitives() { return m_primitives; }

    virtual ~IDocument() = default;
protected:
    std::filesystem::path m_path;
    std::vector<std::shared_ptr<IPrimitive>> m_primitives;
};

} // namespace document