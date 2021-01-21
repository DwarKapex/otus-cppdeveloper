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

class GraphicEditor: public IEditor {
public:
    void CreateNewDocument() override;
    void ImportDocument() override;
    void ExportDocument() override;
    void CreateGraphicalPrimitive() override;
    void RemoveGraphicalPrimitive() override;
};