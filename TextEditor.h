#pragma once
#include <QTextEdit>

class TextEditor : public QTextEdit {
    Q_OBJECT

public:
    TextEditor(QWidget* parent = nullptr);
    ~TextEditor();

    void Undo();
    void Redo();
    
    
};
