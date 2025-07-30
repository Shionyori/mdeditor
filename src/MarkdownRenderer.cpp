#include "MarkdownRenderer.h"
#include <cmark.h>

QString MarkdownRenderer::markdownToHtml(QString& markdown)
{
    QByteArray utf8 = markdown.toUtf8();
    char* html = cmark_markdown_to_html(utf8.constData(), utf8.size(), CMARK_OPT_DEFAULT);
    QString result = QString::fromUtf8(html);
    free(html);
    return "<html><body>" + result + "</body></html>";
}