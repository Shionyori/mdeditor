// src/Toolbar.cpp
#include "Toolbar.h"

Toolbar::Toolbar(QTextEdit* editor, QWidget *parent)
    : QToolBar(parent), editor(editor)
{

    auto mkBtn = [this](const QString &icon, const QKeySequence &ks) -> QPushButton* {
        QPushButton *btn = new QPushButton(this);
        btn->setIcon(QIcon(icon));
        btn->setIconSize(QSize(16, 16)); // 设置图标大小
        btn->setFixedSize(20, 20);       // 设置按钮大小
        btn->setShortcut(ks);
        btn->setFlat(true);
        return btn;
    };

    QPushButton *boldBtn = mkBtn(":/icons/bold.png", QKeySequence("Ctrl+B"));
    QPushButton *italicBtn = mkBtn(":/icons/italic.png", QKeySequence("Ctrl+I"));

    connect(boldBtn, &QPushButton::clicked, this, &Toolbar::makeBold);
    connect(italicBtn, &QPushButton::clicked, this, &Toolbar::makeItalic);

    addWidget(boldBtn);
    addWidget(italicBtn);
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