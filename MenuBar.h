#pragma once

#include <QMenuBar>
#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QVBoxLayout>
#include<QMessageBox>
#include<QRegularExpression>
#include<QTextDocument>
#include<QShortcut>
#include"TextEditor.h"
#include <QTextStream>
#include<QFileDialog>
#include<QByteArray>
#include<QIODevice>
class MenuBar : public QMenuBar {
    Q_OBJECT

public:
    explicit MenuBar(TextEditor *textEditor,QWidget* parent = nullptr);
    void openFindDialog();
    void openFindDialogForSubStr();
    void openFindDialog_1();
    void openFindReplaceDialog();
    void openFindAdvancedDialog();
    void openFindReplaceAdvancedDialog();
    void clearHighlighting();
    void findPrevious();
    void findNext();
    void replaceNext();
    void replacePrevious();
    void findPreviousAll();
    void findNextAll();
    void replacePreviousAll();
    void replaceNextAll();
    void setUpShortcuts();
    void toUpper();
    void toLower();
    void openAddPostfixDialog();
    void openAddPrefixDialog();
    void addPostfixToWord(const QString& targetWord, const QString& postfix);
    void addPrefixToWord(const QString& targetWord, const QString& prefix);
    void openCountsDialog();
    void calculateCountsAndDisplay(QLabel*, QLabel*, QLabel*, QLabel*, QLabel*, QLabel*, QLabel* );
    void mergeFiles(bool mergeIntoFirstFile);
    void onMergeFilesTriggered();
    bool canFormWord(const QString& word, const QString& letters);
    int countValidWords(const QString& word, const QStringList& dictionary);
    void openWordGameDialog();
    QString findWordWithMostWords();
    
private:
    void createMenus();
    QString searchText;
    QString replaceText;
    TextEditor* textEditor;
};


