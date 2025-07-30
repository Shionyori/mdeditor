// src/MarkdownRenderer.h
#ifndef MARKDOWNRENDERER_H
#define MARKDOWNRENDERER_H

#include <QString>

class MarkdownRenderer
{
public:
    static QString markdownToHtml(QString& markdown);
};

#endif // MARKDOWNRENDERER_H