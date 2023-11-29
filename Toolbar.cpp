#include "Toolbar.h"
#include"TextEditor.h"
#include <QAction>

ToolBar::ToolBar(TextEditor* editor, QWidget* parent) : QToolBar(tr("Main Toolbar"), parent)
{
    setupToolBar(); 

    connect(undoAction, &QAction::triggered, editor, &TextEditor::Undo);

    connect(redoAction, &QAction::triggered, editor, &TextEditor::Redo);
    
}

ToolBar::~ToolBar() 
{

}

void ToolBar::setupToolBar() 
{
    QAction* newAction = new QAction(QIcon("new.png"), tr("&New"), this);
    addAction(newAction); 
    
    QAction* openAction = new QAction(QIcon("open.png"), tr("&Open"), this);
    addAction(openAction);

    undoAction = addAction(QIcon("undo.png"), tr("Undo"));
    
    redoAction = addAction(QIcon("redo.png"), tr("Redo"));

}

void ToolBar::newFile() {
   
}

void ToolBar::openFile() {
   
}
