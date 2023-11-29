#include"MenuBar.h"
#include <QtWidgets/QApplication>

MenuBar::MenuBar(TextEditor* textEditor, QWidget* parent) : textEditor(textEditor),QMenuBar(parent)
{
    createMenus(); 
    setUpShortcuts();
}

void MenuBar::createMenus() {
    QMenu* fileMenu = addMenu(tr("&File"));
    QMenu* editMenu = addMenu(tr("&Edit"));


    // File Menu
    QAction* newAction = fileMenu->addAction(tr("&New"));
    QAction* openAction = fileMenu->addAction(tr("&Open"));
    QAction* saveAction = fileMenu->addAction(tr("&Save"));
    fileMenu->addSeparator();
    QAction* exitAction = fileMenu->addAction(tr("E&xit"));
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

    // Edit Menu
    QAction* findAction = editMenu->addAction(tr("&Find"));
    connect(findAction, &QAction::triggered, this, &MenuBar::openFindDialog);
    QAction* findReplaceAction = editMenu->addAction(tr("Find && &Replace"));
    connect(findReplaceAction, &QAction::triggered, this, &MenuBar::openFindReplaceDialog);
    editMenu->addSeparator();
    QAction* findAction_1 = editMenu->addAction(tr("&Find insensitive"));
    connect(findAction_1, &QAction::triggered, this, &MenuBar::openFindDialog_1);
    QAction* findSubStrAction = editMenu->addAction(tr("&Find Substring"));
    connect(findSubStrAction, &QAction::triggered, this, &MenuBar::openFindDialogForSubStr);
    editMenu->addSeparator();
    QAction* AdvanceActions = editMenu->addAction(tr("&Advance Findings"));
    connect(AdvanceActions, &QAction::triggered, this, &MenuBar::openFindAdvancedDialog);
    QAction* AdvanceActions_1 = editMenu->addAction(tr("&Advance Replacements"));
    connect(AdvanceActions_1, &QAction::triggered, this, &MenuBar::openFindReplaceAdvancedDialog);
    editMenu->addSeparator();
    QAction* PrefixActions = editMenu->addAction(tr("Prefix"));
    connect(PrefixActions, &QAction::triggered, this, &MenuBar::openAddPrefixDialog);
    QAction* PostfixActions = editMenu->addAction(tr("Postfix"));
    connect(PostfixActions, &QAction::triggered, this, &MenuBar::openAddPostfixDialog);
    editMenu->addSeparator();
    QAction* mergeAction = editMenu->addAction(tr("Merge"));
    mergeAction->setShortcut(QKeySequence(tr("Ctrl+M")));
    connect(mergeAction, &QAction::triggered, this, &MenuBar::onMergeFilesTriggered);
   /* QAction* wordGameAction = editMenu->addAction(tr("Word Game"));
    wordGameAction->setShortcut(QKeySequence(tr("Ctrl+W")));
    connect(wordGameAction, &QAction::triggered, this, &MenuBar::openWordGameDialog);*/
    
}

void MenuBar::openFindDialog() 
{
    QDialog* findDialog = new QDialog(this);
    findDialog->setWindowTitle("Find");


    QLabel* findLabel = new QLabel("Find:", findDialog);
    QLineEdit* findLineEdit = new QLineEdit(findDialog);
    QPushButton* findButton = new QPushButton("Find", findDialog);

    QLabel* countLabel = new QLabel("Count: 0", findDialog);

    QVBoxLayout* layout = new QVBoxLayout(findDialog);
    layout->addWidget(findLabel);
    layout->addWidget(findLineEdit);
    layout->addWidget(findButton);
    layout->addWidget(countLabel);

    connect(findButton, &QPushButton::clicked, [=]() 
        {
        QString searchText = findLineEdit->text();
        QString content = textEditor->toPlainText();

        QTextCursor cursor(textEditor->document());

        QTextCharFormat format;
        format.setBackground(Qt::yellow); 

        int count = 0;
        int index = content.indexOf(searchText);
        while (index != -1) 
        {
            count++;
            cursor.setPosition(index);
            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, searchText.length());
            cursor.mergeCharFormat(format);
            index = content.indexOf(searchText, index + searchText.length());
        }
        connect(findDialog, &QDialog::finished, this, &MenuBar::clearHighlighting);
        if (count > 0)
        {
            countLabel->setText("Count: " + QString::number(count));

            
            QTextCursor moveCursor = textEditor->textCursor();
            moveCursor.setPosition(content.indexOf(searchText));
            textEditor->setTextCursor(moveCursor);
            textEditor->ensureCursorVisible();
        }
        else 
        {
            QMessageBox::information(findDialog, "Find", "Text not found.");
        }
        });

    findDialog->setLayout(layout);
    findDialog->exec();
    

}

void MenuBar::openFindReplaceDialog() 
{
    QDialog* findReplaceDialog = new QDialog(this);
    findReplaceDialog->setWindowTitle("Find and Replace");

    
    QLabel* findLabel = new QLabel("Find:", findReplaceDialog);
    QLineEdit* findLineEdit = new QLineEdit(findReplaceDialog);
    QLabel* replaceLabel = new QLabel("Replace:", findReplaceDialog);
    QLineEdit* replaceLineEdit = new QLineEdit(findReplaceDialog);
    QPushButton* findButton = new QPushButton("Find", findReplaceDialog);
    QPushButton* replaceButton = new QPushButton("Replace", findReplaceDialog);
    QVBoxLayout* layout = new QVBoxLayout(findReplaceDialog);
    layout->addWidget(findLabel);
    layout->addWidget(findLineEdit);
    layout->addWidget(replaceLabel);
    layout->addWidget(replaceLineEdit);
    layout->addWidget(findButton);
    layout->addWidget(replaceButton);

    connect(findButton, &QPushButton::clicked, [=]() 
        {
        QString searchText = findLineEdit->text();
        QString content = textEditor->toPlainText();

        QTextCursor cursor(textEditor->document());

        QTextCharFormat format;
        format.setBackground(Qt::yellow); 

        int count = 0;
        int index = content.indexOf(searchText);
        while (index != -1) 
        {
            count++;
            cursor.setPosition(index);
            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, searchText.length());
            cursor.mergeCharFormat(format);
            index = content.indexOf(searchText, index + searchText.length());
        }
        connect(findReplaceDialog, &QDialog::finished, this, &MenuBar::clearHighlighting);
        if (count > 0) 
        {
            QTextCursor moveCursor = textEditor->textCursor();
            moveCursor.setPosition(content.indexOf(searchText));
            textEditor->setTextCursor(moveCursor);
            textEditor->ensureCursorVisible();
        }
        else 
        {
            QMessageBox::information(findReplaceDialog, "Find", "Text not found.");
        }
        });

    connect(replaceButton, &QPushButton::clicked, [=]() {
        
        QString searchText = findLineEdit->text();
        QString replaceText = replaceLineEdit->text();
        QString content = textEditor->toPlainText();

        int replaceCount = 0;
        int index = content.indexOf(searchText);
        while (index != -1) {
            ++replaceCount;
            content.replace(index, searchText.length(), replaceText);
            index = content.indexOf(searchText, index + replaceText.length());
        }

        textEditor->setPlainText(content);
        QMessageBox::information(findReplaceDialog, "Replace", "Replaced " + QString::number(replaceCount) + " occurrences.");
        });

    findReplaceDialog->setLayout(layout);
    findReplaceDialog->exec();
}

void MenuBar::openFindDialog_1() 
{
    QDialog* findDialog = new QDialog(this);
    findDialog->setWindowTitle("Find");


    QLabel* findLabel = new QLabel("Find:", findDialog);
    QLineEdit* findLineEdit = new QLineEdit(findDialog);
    QPushButton* findButton = new QPushButton("Find", findDialog);

    QLabel* countLabel = new QLabel("Count: 0", findDialog);

    QVBoxLayout* layout = new QVBoxLayout(findDialog);
    layout->addWidget(findLabel);
    layout->addWidget(findLineEdit);
    layout->addWidget(findButton);
    layout->addWidget(countLabel);

    connect(findButton, &QPushButton::clicked, [=]() 
        {
        QString searchText = findLineEdit->text();
        QString content = textEditor->toPlainText();

        QTextCursor cursor(textEditor->document());

        QTextCharFormat format;
        format.setBackground(Qt::green); 

        int count = 0;
        int index = content.indexOf(searchText, 0, Qt::CaseInsensitive); 
        while (index != -1) 
        {
            count++;
            cursor.setPosition(index);
            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, searchText.length());
            cursor.mergeCharFormat(format);
            index = content.indexOf(searchText, index + searchText.length(), Qt::CaseInsensitive); // Performing case-insensitive search
        }
        connect(findDialog, &QDialog::finished, this, &MenuBar::clearHighlighting);
        if (count > 0) 
        {
            countLabel->setText("Count: " + QString::number(count));

            
            QTextCursor moveCursor = textEditor->textCursor();
            moveCursor.setPosition(content.indexOf(searchText, 0, Qt::CaseInsensitive)); // Performing case-insensitive search
            textEditor->setTextCursor(moveCursor);
            textEditor->ensureCursorVisible();
        }
        else 
        {
            QMessageBox::information(findDialog, "Find", "Text not found.");
        }
        });

    findDialog->setLayout(layout);
    findDialog->exec();
}

void MenuBar::openFindDialogForSubStr() 
{
    QDialog* findDialog = new QDialog(this);
    findDialog->setWindowTitle("Find");

    
    QLabel* findLabel = new QLabel("Find:", findDialog);
    QLineEdit* findLineEdit = new QLineEdit(findDialog);
    QPushButton* findButton = new QPushButton("Find", findDialog);

    QLabel* countLabel = new QLabel("Count: 0", findDialog);

    QVBoxLayout* layout = new QVBoxLayout(findDialog);
    layout->addWidget(findLabel);
    layout->addWidget(findLineEdit);
    layout->addWidget(findButton);
    layout->addWidget(countLabel);

    connect(findButton, &QPushButton::clicked, [=]() 
        {
        QString searchText = findLineEdit->text().toLower(); 
        QString content = textEditor->toPlainText().toLower(); 

        QTextCursor cursor(textEditor->document());

        QTextCharFormat format;
        format.setBackground(Qt::yellow); 

        QStringList words = content.split(QRegularExpression("\\W+"), Qt::SkipEmptyParts);
        int count = 0;

        for (const QString& word : words) {
            if (word.contains(searchText)) {
                int index = 0;
                while ((index = content.indexOf(word, index, Qt::CaseInsensitive)) != -1) {
                    cursor.setPosition(index);
                    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, word.length());
                    cursor.mergeCharFormat(format);
                    index += word.length();
                    ++count;
                }
            }
        }
        connect(findDialog, &QDialog::finished, this, &MenuBar::clearHighlighting);
        if (count > 0) {
            countLabel->setText("Count: " + QString::number(count));

            QTextCursor moveCursor = textEditor->textCursor();
            moveCursor.setPosition(content.indexOf(searchText)); 
            textEditor->setTextCursor(moveCursor);
            textEditor->ensureCursorVisible();
        }
        else {
            QMessageBox::information(findDialog, "Find", "Text not found.");
        }
        });

    findDialog->setLayout(layout);
    findDialog->exec();
}

void MenuBar::openFindAdvancedDialog() 
{
    QDialog* findDialog = new QDialog(this);
    findDialog->setWindowTitle("Find");

    QLabel* findLabel = new QLabel("Find:", findDialog);
    QLineEdit* findLineEdit = new QLineEdit(findDialog);

    QPushButton* findNextButton = new QPushButton("Find Next", findDialog);
    QPushButton* findPrevButton = new QPushButton("Find Previous", findDialog);
    QPushButton* findNextAllButton = new QPushButton("Find Next All", findDialog);
    QPushButton* findPrevAllButton = new QPushButton("Find Previous All", findDialog);

    QVBoxLayout* layout = new QVBoxLayout(findDialog);
    layout->addWidget(findLabel);
    layout->addWidget(findLineEdit);
    layout->addWidget(findNextButton);
    layout->addWidget(findPrevButton);
    layout->addWidget(findNextAllButton);
    layout->addWidget(findPrevAllButton);

    connect(findNextButton, &QPushButton::clicked, this, &MenuBar::findNext);
    connect(findDialog, &QDialog::finished, this, &MenuBar::clearHighlighting);

    connect(findPrevButton, &QPushButton::clicked, this, &MenuBar::findPrevious);
    connect(findNextAllButton, &QPushButton::clicked, this, &MenuBar::findNextAll);
    connect(findPrevAllButton, &QPushButton::clicked, this, &MenuBar::findPreviousAll);
    connect(findLineEdit, &QLineEdit::textChanged, this, [this](const QString& text) {
        searchText = text;
        });

    findDialog->setLayout(layout);
    findDialog->exec();
}

void MenuBar::openFindReplaceAdvancedDialog() 
{
    QDialog* findDialog = new QDialog(this);
    findDialog->setWindowTitle("Replacement Advance");

    QLabel* findLabel = new QLabel("Find:", findDialog);
    QLineEdit* findLineEdit = new QLineEdit(findDialog);
    QLabel* replaceLabel = new QLabel("Replace:", findDialog);
    QLineEdit* replaceLineEdit = new QLineEdit(findDialog);

    QPushButton* ReplaceNextButton = new QPushButton("Replace Next", findDialog);
    QPushButton* replacePreviousButton = new QPushButton("Replace Previous", findDialog);
    QPushButton* ReplaceNextAllButton = new QPushButton("Replace Next All", findDialog);
    QPushButton* replacePreviousAllButton = new QPushButton("Replace Previous All", findDialog);

    QVBoxLayout* layout = new QVBoxLayout(findDialog);
    layout->addWidget(findLabel);
    layout->addWidget(findLineEdit);
    layout->addWidget(replaceLabel);
    layout->addWidget(replaceLineEdit);
    layout->addWidget(ReplaceNextButton);
    layout->addWidget(replacePreviousButton);
    layout->addWidget(ReplaceNextAllButton);
    layout->addWidget(replacePreviousAllButton);

    connect(ReplaceNextButton, &QPushButton::clicked, this, &MenuBar::replaceNext);
    connect(replacePreviousButton, &QPushButton::clicked, this, &MenuBar::replacePrevious);
    connect(findDialog, &QDialog::finished, this, &MenuBar::clearHighlighting);
    connect(ReplaceNextAllButton, &QPushButton::clicked, this, &MenuBar::replaceNextAll);
    connect(replacePreviousAllButton, &QPushButton::clicked, this, &MenuBar::replacePreviousAll);
    connect(findLineEdit, &QLineEdit::textChanged, this, [this](const QString& text) {
        searchText = text;
        });
    connect(replaceLineEdit, &QLineEdit::textChanged, this, [this](const QString& text) {
        replaceText = text;
        });

    findDialog->setLayout(layout);
    findDialog->exec();
}

void MenuBar::clearHighlighting() 
{
    QTextCursor cursor(textEditor->document());
    cursor.select(QTextCursor::Document);
    cursor.setCharFormat(QTextCharFormat()); 
}

void MenuBar::findPrevious() {
    if (!textEditor || searchText.isEmpty()) {
        return;
    }

    QTextCursor cursor = textEditor->textCursor();

    if (!cursor.isNull()) {
        QTextDocument* document = textEditor->document();

        QTextCursor highlightCursor(document);
        highlightCursor = document->find(searchText, cursor, QTextDocument::FindBackward);

        if (!highlightCursor.isNull()) {
            textEditor->setTextCursor(highlightCursor);
            textEditor->ensureCursorVisible();
        }
    }
}

void MenuBar::findNext() {
    if (!textEditor || searchText.isEmpty()) {
        return;
    }

    QTextCursor cursor = textEditor->textCursor();

    if (!cursor.isNull()) {
        QTextDocument* document = textEditor->document();

        QTextCursor highlightCursor(document);
        highlightCursor = document->find(searchText, cursor);

        if (!highlightCursor.isNull()) {
            textEditor->setTextCursor(highlightCursor);
            textEditor->ensureCursorVisible();
        }
    }
}

void MenuBar::replaceNext() 
{
    if (!textEditor || searchText.isEmpty() || replaceText.isEmpty()) 
    {
        return;
    }

    QTextCursor cursor = textEditor->textCursor();

    if (!cursor.isNull()) 
    {
        QTextDocument* document = textEditor->document();

        QTextCursor replaceCursor(document);
        replaceCursor = document->find(searchText, cursor);

        if (!replaceCursor.isNull()) 
        {
            replaceCursor.insertText(replaceText);
            textEditor->setTextCursor(replaceCursor);
            textEditor->ensureCursorVisible();
        }
    }
}

void MenuBar::replacePrevious() 
{
    if (!textEditor || searchText.isEmpty() || replaceText.isEmpty()) 
    {
        return;
    }

    QTextCursor cursor = textEditor->textCursor();

    if (!cursor.isNull()) 
    {
        QTextDocument* document = textEditor->document();

        QTextCursor replaceCursor(document);
    
        replaceCursor = document->find(searchText, cursor, QTextDocument::FindBackward);

        if (!replaceCursor.isNull()) 
        {
            replaceCursor.insertText(replaceText);
            textEditor->setTextCursor(replaceCursor);
            textEditor->ensureCursorVisible();
        }
    }
}

void MenuBar::findNextAll() 
{
    if (!textEditor || searchText.isEmpty()) 
    {
        return;
    }

    QTextCursor cursor = textEditor->textCursor();
    QTextDocument* document = textEditor->document();

    cursor = document->find(searchText, cursor);

    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(Qt::yellow);

    while (!cursor.isNull() && !cursor.atEnd()) 
    {
        cursor.movePosition(QTextCursor::NextWord, QTextCursor::KeepAnchor);
        cursor.mergeCharFormat(highlightFormat);
        cursor = document->find(searchText, cursor, QTextDocument::FindWholeWords);
    }
    
}

void MenuBar::findPreviousAll() {
    if (!textEditor || searchText.isEmpty()) {
        return;
    }

    QTextCursor cursor = textEditor->textCursor();
    QTextDocument* document = textEditor->document();

    cursor = document->find(searchText, cursor, QTextDocument::FindWholeWords | QTextDocument::FindBackward);

    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(Qt::yellow);

    while (!cursor.isNull() && !cursor.atStart()) {
        cursor.movePosition(QTextCursor::StartOfWord);
        cursor.movePosition(QTextCursor::NextWord, QTextCursor::KeepAnchor);
        cursor.mergeCharFormat(highlightFormat);
        cursor = document->find(searchText, cursor, QTextDocument::FindWholeWords | QTextDocument::FindBackward);
    }
}

void MenuBar::replaceNextAll() 
{
    if (!textEditor || searchText.isEmpty()) 
    {
        return;
    }

    QTextCursor cursor = textEditor->textCursor();
    QTextDocument* document = textEditor->document();

    cursor = document->find(searchText, cursor);

    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(Qt::green);

    while (!cursor.isNull() && !cursor.atEnd()) 
    {
        QTextCursor tempCursor = cursor; 
        tempCursor.movePosition(QTextCursor::NextWord, QTextCursor::KeepAnchor);
        tempCursor.mergeCharFormat(highlightFormat);


        tempCursor.insertText(replaceText);

        cursor = document->find(searchText, cursor, QTextDocument::FindWholeWords);
    }
}

void MenuBar::replacePreviousAll() 
{
    if (!textEditor || searchText.isEmpty()) 
    {
        return;
    }

    QTextCursor cursor = textEditor->textCursor();
    QTextDocument* document = textEditor->document();

    cursor = document->find(searchText, cursor, QTextDocument::FindWholeWords | QTextDocument::FindBackward);

    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(Qt::green);

    while (!cursor.isNull() && !cursor.atStart()) 
    {
        QTextCursor tempCursor = cursor; 
        tempCursor.movePosition(QTextCursor::StartOfWord);
        tempCursor.movePosition(QTextCursor::NextWord, QTextCursor::KeepAnchor);
        tempCursor.mergeCharFormat(highlightFormat);

        
        tempCursor.insertText("ReplacementText");

        cursor = document->find(searchText, cursor, QTextDocument::FindWholeWords | QTextDocument::FindBackward);
    }
}

void MenuBar::setUpShortcuts() 
{
    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_U), this);
    QShortcut* shortcutCounts = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), this);
    QShortcut* shortcutLower = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), this);
    connect(shortcutCounts, &QShortcut::activated, this, &MenuBar::openCountsDialog);
    connect(shortcutLower, &QShortcut::activated, this, &MenuBar::toLower);
    connect(shortcut, &QShortcut::activated, this, &MenuBar::toUpper);
}

void MenuBar::toUpper() 
{
    QTextCursor cursor = textEditor->textCursor();
    QString selectedText = cursor.selectedText();

    if (!selectedText.isEmpty()) 
    {
        cursor.beginEditBlock();
        cursor.removeSelectedText();
        cursor.insertText(selectedText.toUpper());
        cursor.endEditBlock();
    }
    else 
    {
        QTextCursor wordStart = cursor;
        wordStart.movePosition(QTextCursor::StartOfWord);
        QTextCursor wordEnd = cursor;
        wordEnd.movePosition(QTextCursor::EndOfWord);

        cursor.setPosition(wordStart.position());
        cursor.setPosition(wordEnd.position(), QTextCursor::KeepAnchor);
        QString word = cursor.selectedText();

        cursor.beginEditBlock();
        cursor.removeSelectedText();
        cursor.insertText(word.toUpper());
        cursor.endEditBlock();
    }
}

void MenuBar::toLower() 
{
    if (!textEditor) 
    {
        return;
    }

    QTextCursor cursor = textEditor->textCursor();

    if (!cursor.isNull()) 
    {
        cursor.select(QTextCursor::WordUnderCursor);
        QString selectedWord = cursor.selectedText();

        if (!selectedWord.isEmpty()) 
        {
            cursor.removeSelectedText();
            cursor.insertText(selectedWord.toLower());
        }
    }
}

void MenuBar::openAddPrefixDialog() 
{
    QDialog* prefixDialog = new QDialog(this);
    prefixDialog->setWindowTitle("Add Prefix to Word");

    QLabel* wordLabel = new QLabel("Word:", prefixDialog);
    QLineEdit* wordLineEdit = new QLineEdit(prefixDialog);

    QLabel* prefixLabel = new QLabel("Prefix:", prefixDialog);
    QLineEdit* prefixLineEdit = new QLineEdit(prefixDialog);

    QPushButton* addButton = new QPushButton("Add Prefix", prefixDialog);

    QVBoxLayout* layout = new QVBoxLayout(prefixDialog);
    layout->addWidget(wordLabel);
    layout->addWidget(wordLineEdit);
    layout->addWidget(prefixLabel);
    layout->addWidget(prefixLineEdit);
    layout->addWidget(addButton);

    connect(addButton, &QPushButton::clicked, [=]() {
        QString targetWord = wordLineEdit->text();
        QString prefix = prefixLineEdit->text();
        addPrefixToWord(targetWord, prefix);
        });

    prefixDialog->setLayout(layout);
    prefixDialog->exec();
}

void MenuBar::openAddPostfixDialog() 
{
    QDialog* postfixDialog = new QDialog(this);
    postfixDialog->setWindowTitle("Add Postfix to Word");

    QLabel* wordLabel = new QLabel("Word:", postfixDialog);
    QLineEdit* wordLineEdit = new QLineEdit(postfixDialog);

    QLabel* postfixLabel = new QLabel("Postfix:", postfixDialog);
    QLineEdit* postfixLineEdit = new QLineEdit(postfixDialog);

    QPushButton* addButton = new QPushButton("Add Postfix", postfixDialog);

    QVBoxLayout* layout = new QVBoxLayout(postfixDialog);
    layout->addWidget(wordLabel);
    layout->addWidget(wordLineEdit);
    layout->addWidget(postfixLabel);
    layout->addWidget(postfixLineEdit);
    layout->addWidget(addButton);

    connect(addButton, &QPushButton::clicked, [=]() {
        QString targetWord = wordLineEdit->text();
        QString postfix = postfixLineEdit->text();
        addPostfixToWord(targetWord, postfix);
        });

    postfixDialog->setLayout(layout);
    postfixDialog->exec();
}

void MenuBar::addPrefixToWord(const QString& targetWord, const QString& prefix) 
{
    if (!textEditor || targetWord.isEmpty() || prefix.isEmpty()) 
    {
        return;
    }

    QTextCursor cursor = textEditor->textCursor();
    QTextDocument* document = textEditor->document();

    while (!cursor.isNull() && !cursor.atEnd()) 
    {
        cursor = document->find(targetWord, cursor);
        if (!cursor.isNull()) 
        {
            cursor.beginEditBlock();
            cursor.insertText(prefix);
            cursor.movePosition(QTextCursor::EndOfWord);
            cursor.endEditBlock();
        }
    }
}

void MenuBar::addPostfixToWord(const QString& targetWord, const QString& postfix) 
{
    if (!textEditor || targetWord.isEmpty() || postfix.isEmpty()) 
    {
        return;
    }

    QTextCursor cursor = textEditor->textCursor();
    QTextDocument* document = textEditor->document();

    while (!cursor.isNull() && !cursor.atEnd()) 
    {
        cursor = document->find(targetWord, cursor);
        if (!cursor.isNull()) 
        {
            cursor.beginEditBlock();
            cursor.movePosition(QTextCursor::EndOfWord);
            cursor.insertText(postfix);
            cursor.endEditBlock();
        }
    }
}

void MenuBar::openCountsDialog() {
    QDialog* countsDialog = new QDialog(this);
    countsDialog->setWindowTitle("Counts");

    QLabel* avgWordLengthLabel = new QLabel("Average Word Length:", countsDialog);
    QLabel* specialCharsCountLabel = new QLabel("Special Characters Count:", countsDialog);
    QLabel* sentencesParagraphsCountLabel = new QLabel("Sentences & Paragraphs Count:", countsDialog);
    QLabel* largestWordLengthLabel = new QLabel("Largest Word Length:", countsDialog);
    QLabel* smallestWordLabel = new QLabel("Smallest Word:", countsDialog);
    QLabel* paragraphsCountLabel = new QLabel("Paragraphs Count:", countsDialog);
    QLabel* largestParagraphWordLengthLabel = new QLabel("Largest Paragraph Word Length:", countsDialog);

    QPushButton* calculateButton = new QPushButton("Calculate", countsDialog);

    QVBoxLayout* layout = new QVBoxLayout(countsDialog);
    layout->addWidget(avgWordLengthLabel);
    layout->addWidget(specialCharsCountLabel);
    layout->addWidget(sentencesParagraphsCountLabel);
    layout->addWidget(largestWordLengthLabel);
    layout->addWidget(smallestWordLabel);
    layout->addWidget(paragraphsCountLabel);
    layout->addWidget(largestParagraphWordLengthLabel);
    layout->addWidget(calculateButton);

    connect(calculateButton, &QPushButton::clicked, [=]() {
        calculateCountsAndDisplay(avgWordLengthLabel, specialCharsCountLabel, sentencesParagraphsCountLabel,
        largestWordLengthLabel, smallestWordLabel, paragraphsCountLabel, largestParagraphWordLengthLabel);
        });


    countsDialog->setLayout(layout);
    countsDialog->exec();
}
void MenuBar::calculateCountsAndDisplay(QLabel* avgWordLengthLabel, QLabel* specialCharsCountLabel,
    QLabel* sentencesParagraphsCountLabel, QLabel* largestWordLengthLabel,
    QLabel* smallestWordLabel, QLabel* paragraphsCountLabel,
    QLabel* largestParagraphWordLengthLabel)
{
    if (!textEditor) 
    {
        
        return;
    }

    QString content = textEditor->toPlainText();
    QTextDocument* document = textEditor->document();

    // Calculate average word length
    QStringList words = content.split(QRegularExpression("\\W+"), Qt::SkipEmptyParts);
    double totalWordLength = 0;
    for (const QString& word : words) {
        totalWordLength += word.length();
    }
    double avgWordLength = words.isEmpty() ? 0 : totalWordLength / words.size();

    // Calculate special characters count
    int specialCharsCount = content.count(QRegularExpression("[^A-Za-z0-9\\s]"));

    // Calculate sentences & paragraphs count
    int sentencesCount = content.count(QRegularExpression("[.!?]"));
    int paragraphsCount = content.count("\n\n");

    // Find largest and smallest word lengths
    int largestWordLength = 0;
    int smallestWordLength = std::numeric_limits<int>::max();
    QString smallestWord;
    for (const QString& word : words) {
        if (word.length() > largestWordLength) {
            largestWordLength = word.length();
        }
        if (word.length() < smallestWordLength) {
            smallestWordLength = word.length();
            smallestWord = word;
        }
    }

    // Count largest paragraph word length
    QStringList paragraphs = content.split("\n\n", Qt::SkipEmptyParts);
    int largestParagraphWordLength = 0;
    for (const QString& paragraph : paragraphs) {
        QStringList paragraphWords = paragraph.split(QRegularExpression("\\W+"), Qt::SkipEmptyParts);
        for (const QString& word : paragraphWords) {
            if (word.length() > largestParagraphWordLength) {
                largestParagraphWordLength = word.length();
            }
        }
    }
    avgWordLengthLabel->setText("Average Word Length: " + QString::number(avgWordLength));
    specialCharsCountLabel->setText("Special Characters Count: " + QString::number(specialCharsCount));
    sentencesParagraphsCountLabel->setText("Sentences Count: " + QString::number(sentencesCount)
        + " Paragraphs Count: " + QString::number(paragraphsCount));
    largestWordLengthLabel->setText("Largest Word Length: " + QString::number(largestWordLength));
    smallestWordLabel->setText("Smallest Word: " + smallestWord);
    paragraphsCountLabel->setText("Paragraphs Count: " + QString::number(paragraphsCount));
    largestParagraphWordLengthLabel->setText("Largest Paragraph Word Length: " + QString::number(largestParagraphWordLength));

}


void MenuBar::onMergeFilesTriggered() {
    
    mergeFiles(true);  
    
}


void MenuBar::mergeFiles(bool mergeIntoFirstFile) 
{
    QString firstFilePath = QFileDialog::getOpenFileName(this, tr("Select First File"));
    QString secondFilePath = QFileDialog::getOpenFileName(this, tr("Select Second File"));

    if (firstFilePath.isEmpty() || secondFilePath.isEmpty()) 
    {
    
        return;
    }

    QFile firstFile(firstFilePath);
    QFile secondFile(secondFilePath);

    if (!firstFile.open(QIODevice::ReadOnly | QIODevice::Text) || !secondFile.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        
        return;
    }

    QString mergedContent;
    QTextStream firstStream(&firstFile);
    QTextStream secondStream(&secondFile);

    mergedContent += firstStream.readAll();
    if (mergeIntoFirstFile) 
    {
        firstFile.resize(firstFile.size() + secondFile.size()); 
        firstFile.seek(firstFile.size() - secondFile.size());
        mergedContent += secondStream.readAll();
        firstStream << mergedContent; 
    }
    else 
    {
        mergedContent += secondStream.readAll(); 
    }

    QString newFilePath = QFileDialog::getSaveFileName(this, tr("Save Merged File"));
    if (newFilePath.isEmpty()) 
    {
         return;
    }

    QFile newFile(newFilePath);
    if (!newFile.open(QIODevice::WriteOnly | QIODevice::Text)) 
    {
        return;
    }

    QTextStream newFileStream(&newFile);
    newFileStream << mergedContent; 

    newFile.close();
    firstFile.close();
    secondFile.close();
}