#include "TextEditor.h"

TextEditor::TextEditor(QWidget* parent) : QTextEdit(parent) 
{
    
}


void TextEditor::Undo()
{
    undo();
}
void TextEditor::Redo()
{
    redo();
}



TextEditor::~TextEditor() {}
