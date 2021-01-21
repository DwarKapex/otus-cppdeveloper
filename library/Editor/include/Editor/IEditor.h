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

#include <string>

class IEditor {
public:
    virtual void CreateNewDocument(const std::string& path) = 0;
    virtual void ImportDocument() = 0;
    virtual void ExportDocument() = 0;
    virtual void CreateGraphicalPrimitive() = 0;
    virtual void RemoveGraphicalPrimitive() = 0;

    virtual ~IEditor();
private:
};