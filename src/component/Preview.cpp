// src/Preview.cpp
#include "Preview.h"
#include "../utils/MarkdownRenderer.h"
#include <QTimer>

Preview::Preview(Editor* editor, QWidget *parent)
    : QWebEngineView(parent), editor(editor)
{
    // 防抖：窗口 resize 后 n ms 内不再调用 setHtml
    resizeTimer = new QTimer(this);
    resizeTimer->setSingleShot(true);
    resizeTimer->setInterval(10);
    connect(resizeTimer, &QTimer::timeout,
            this, &Preview::updatePreview);

    // 编辑器内容变化时立即刷新
    connect(editor, &QTextEdit::textChanged,
            this, &Preview::updatePreview);
}

void Preview::updatePreview()
{
    QString markdownText = editor->toPlainText();
    QString htmlText = MarkdownRenderer::markdownToHtml(markdownText);

    // 确保 baseUrl 指向一个真实存在的目录；不存在就创建
    QDir imgDir(QApplication::applicationDirPath());
    if (!imgDir.exists())
        imgDir.mkpath(imgDir.absolutePath());

    setHtml(htmlText, QUrl::fromLocalFile(imgDir.absolutePath() + "/"));
}

// 覆盖 resizeEvent，只在最后一次 resize 完成后刷新
void Preview::resizeEvent(QResizeEvent *event)
{
    QWebEngineView::resizeEvent(event);
    resizeTimer->start();   // 重启防抖计时
}