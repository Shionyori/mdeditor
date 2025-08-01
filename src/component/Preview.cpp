// src/Preview.cpp
#include "Preview.h"
#include "../utils/MarkdownRenderer.h"

Preview::Preview(Editor* editor, QWidget *parent)
    : QWebEngineView(parent), editor(editor)
{
}

void Preview::updatePreview()
{
    QString markdownText = editor->toPlainText();
    QString htmlText = MarkdownRenderer::markdownToHtml(markdownText);

    QDir imgDir(QApplication::applicationDirPath());
    setHtml(htmlText, QUrl::fromLocalFile(imgDir.absolutePath() + "/"));
}