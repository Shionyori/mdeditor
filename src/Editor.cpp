// src/Editor.cpp
#include "Editor.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Editor::Editor(QWidget *parent)
    : QTextEdit(parent)
{
}

void Editor::newFile()
{
    clear();
    currentFilePath.clear();
}

void Editor::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "打开 Markdown 文件", "", "Markdown 文件 (*.md);;所有文件 (*)");
    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            setPlainText(in.readAll());
            file.close();
            currentFilePath = filePath;
        }
        else
        {
            QMessageBox::critical(this, "错误", "无法打开文件");
        }
    }
}

void Editor::saveFile()
{
    QString filePath = currentFilePath.isEmpty() ? QFileDialog::getSaveFileName(this, "保存 Markdown 文件", "", "Markdown 文件 (*.md);;所有文件 (*)") : currentFilePath;
    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << toPlainText();
            file.close();
            currentFilePath = filePath;
        }
        else
        {
            QMessageBox::critical(this, "错误", "无法保存文件");
        }
    }
}

void Editor::saveAs()
{
    QString f = QFileDialog::getSaveFileName(this, "Save As", "", "Markdown (*.md)");
    if (!f.isEmpty()) {
        currentFilePath = f;
        saveFile();
    }
}