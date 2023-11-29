#include "TextEditorv102.h"

#include <QtWidgets/QApplication>
#include<QFile>
#include<QDebug>
#include <QTextStream>
#include <QFileSystemWatcher>
#include<QPixMap>
#include<QSplashScreen>

void openFileInEditor(const QString& fileName, TextEditorv102& editor) {
    
    
    editor.openFile(fileName);
    qDebug() << "Opening file in text editor:" << fileName;
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QPixmap originalPixmap("splash.png");

    QPixmap resizedPixmap = originalPixmap.scaled(800, 600, Qt::KeepAspectRatio);

    QSplashScreen splash(resizedPixmap);
    splash.show();

    TextEditorv102 w;
    w.show();
    splash.finish(&w);
    QString commandFilePath = "C:\\Users\\malik\\source\\repos\\Dos v1\\dos_commands.txt";

    QFileSystemWatcher watcher;
    watcher.addPath(commandFilePath);

    QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, [&w, &commandFilePath]() {
        QFile file(commandFilePath);
        if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "dos_commands.txt does not exist or cannot be opened";
            return;
        }

        QTextStream in(&file);
        QString command = in.readAll().trimmed();

        if (command.startsWith("edit")) {
            QString fileName = command.mid(5).trimmed();
            openFileInEditor(fileName, w);
        }

        file.close();
        });

    return a.exec();
}