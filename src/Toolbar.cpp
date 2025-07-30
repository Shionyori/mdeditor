// src/Toolbar.cpp
#include "Toolbar.h"
#include <QStyle>

Toolbar::Toolbar(QTextEdit* editor, QWidget *parent)
    : QWidget(parent), editor(editor)
{
    // 统一创建函数
    auto mkBtn = [this](const QString &icon, const QKeySequence &ks) -> QPushButton* {
        QPushButton *btn = new QPushButton(this);
        btn->setIcon(QIcon(icon));
        btn->setIconSize(QSize(14, 14));               // 更小图标
        btn->setFixedSize(24, 24);                     // 紧凑按钮
        btn->setShortcut(ks);
        btn->setFlat(true);                            // 无边框
        return btn;
    };

    QPushButton *boldBtn   = mkBtn(":/icons/bold.png",   QKeySequence("Ctrl+B"));
    QPushButton *italicBtn = mkBtn(":/icons/italic.png", QKeySequence("Ctrl+I"));

    connect(boldBtn,   &QPushButton::clicked, this, &Toolbar::makeBold);
    connect(italicBtn, &QPushButton::clicked, this, &Toolbar::makeItalic);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(2, 0, 2, 0);  // 左右各 2 px 边距
    layout->setSpacing(2);                   // 按钮之间 2 px
    layout->addWidget(boldBtn);
    layout->addWidget(italicBtn);
    setLayout(layout);
}

void Toolbar::makeBold()
{
    QTextCursor cursor = editor->textCursor();
    QString selectedText = cursor.selectedText();
    if (!selectedText.isEmpty())
    {
        cursor.insertText("**" + selectedText + "**");
    }
    else
    {
        cursor.insertText("**");
        cursor.movePosition(QTextCursor::Left);
        editor->setTextCursor(cursor);
    }
}

void Toolbar::makeItalic()
{
    QTextCursor cursor = editor->textCursor();
    QString selectedText = cursor.selectedText();
    if (!selectedText.isEmpty())
    {
        cursor.insertText("*" + selectedText + "*");
    }
    else
    {
        cursor.insertText("*");
        cursor.movePosition(QTextCursor::Left);
        editor->setTextCursor(cursor);
    }
}