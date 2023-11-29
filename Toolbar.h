#pragma once
// ToolBar.h

#include<qaction.h>
#include <QToolBar>
#include"TextEditor.h"

class ToolBar : public QToolBar {
    Q_OBJECT

public:
    explicit ToolBar(TextEditor* editor, QWidget* parent = nullptr);
    ~ToolBar();

private slots:
    void newFile();
    void openFile();
    
    

private:
    QAction* undoAction;
    QAction* redoAction;
    QAction* boldAction;
    QAction* italicAction;
    QAction* underlineAction;
    void setupToolBar(); // Function to set up the toolbar actions
};




