// src/Preview.cpp
#include "Preview.h"
#include "MarkdownRenderer.h"

Preview::Preview(Editor* editor, QWidget *parent)
    : QWebEngineView(parent), editor(editor)
{
}

void Preview::updatePreview()
{
    QString markdownText = editor->toPlainText(); // 使用保存的 editor 对象
    QString htmlText = MarkdownRenderer::markdownToHtml(markdownText);
    setHtml(htmlText);
}