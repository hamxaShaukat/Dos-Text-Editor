#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TextEditorv103.h"
#include"MenuBar.h"
#include"TextEditor.h"
#include<QFile>
#include<QDebug>
#include <QTextStream>
#include<QMessageBox>
class TextEditorv102 : public QMainWindow
{
    Q_OBJECT

public:
    TextEditorv102(QWidget *parent = nullptr);
    ~TextEditorv102();
    void openFile(const QString& fileName);

private:
    Ui::TextEditorv103Class ui;
    TextEditor* textEditor;
};
