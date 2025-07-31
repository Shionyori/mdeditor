// src/Preview.h
#ifndef PREVIEW_H
#define PREVIEW_H

#include <QWebEngineView>
#include "Editor.h"

class Preview : public QWebEngineView
{
    Q_OBJECT

public:
    Preview(Editor* editor, QWidget *parent = nullptr);
    void updatePreview();

private:
    Editor* editor; // 保存 Editor 对象的指针
};

#endif // PREVIEW_H