// src/Editor.h
#ifndef EDITOR_H
#define EDITOR_H

#include <QTextEdit>
#include <QAction>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class Editor : public QTextEdit
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    void newFile();
    void openFile();
    void saveFile();
    void saveAs();

private:
    QString currentFilePath;
};

#endif // EDITOR_H