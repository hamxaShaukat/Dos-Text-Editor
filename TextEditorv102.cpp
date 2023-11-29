#include "TextEditorv102.h"
#include"Toolbar.h"
#include"TextEditor.h"

TextEditorv102::TextEditorv102(QWidget *parent)
    : QMainWindow(parent), textEditor(new TextEditor(this))
{
    ui.setupUi(this);
    //TextEditor* textEditor = new TextEditor(this);
    MenuBar* menuBar = new MenuBar(textEditor,this);
    ToolBar* toolbar = new ToolBar(textEditor,this);
    addToolBar(toolbar);
    setMenuBar(menuBar);
    setCentralWidget(textEditor);

}

void TextEditorv102::openFile(const QString& fileName) 
{
    QFile file("C:\\Users\\malik\\source\\repos\\Dos v1\\" + fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        QMessageBox::warning(this, "Error", "Cannot open file: "+fileName + file.errorString());
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    
    textEditor->setPlainText(content);
    setWindowTitle("Text Editor - " + fileName);
}

TextEditorv102::~TextEditorv102()
{}
