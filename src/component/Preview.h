// src/Preview.h
#ifndef PREVIEW_H
#define PREVIEW_H

#include <QWebEngineView>
#include <QDir>
#include <QApplication>
#include "Editor.h"

class Preview : public QWebEngineView
{
    Q_OBJECT

public:
    Preview(Editor* editor, QWidget *parent = nullptr);
    void updatePreview();

private:
    Editor* editor;
};

#endif // PREVIEW_H