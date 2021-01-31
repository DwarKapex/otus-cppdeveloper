/**
 * \brief Main application
 */

#include <Editor/GraphicEditor.h>
#include <Editor/Document/Tools/Tools.h>
#include <Editor/Document/Primitives/Circle.h>

#include <memory>

using namespace document;

int main() {
    GraphicEditor editor;
    editor.CreateNewDocument("/tmp/file0.jpg", DocumentType::JPG);
    editor.ImportDocument("/tmp/file1.jpg");
    editor.ExportDocument("/tmp/file1_export.jpg", DocumentType::PNG);
    auto config = PrimitiveConfig{Color::Red, LineStyle::Solid, {0,0}, std::make_shared<Pensil>()};
    auto circle = std::make_shared<Circle>(1, config);
    editor.CreatePrimitive(circle);
    editor.RemovePrimitive(circle);
    editor.SetActiveDocument();

    return 0;
}
