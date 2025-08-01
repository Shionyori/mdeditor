// src/Toolbar.cpp
#include "Toolbar.h"

Toolbar::Toolbar(QTextEdit* editor, QWidget *parent)
    : QToolBar(parent), editor(editor)
{

    auto mkBtn = [this](const QString &icon, const QKeySequence &ks) -> QPushButton* {
        QPushButton *btn = new QPushButton(this);
        btn->setIcon(QIcon(icon));
        btn->setIconSize(QSize(15, 15));
        btn->setFixedSize(25, 25);       
        btn->setShortcut(ks);
        btn->setFlat(true);
        return btn;
    };

    QPushButton *boldBtn = mkBtn(":/icons/bold.png", QKeySequence("Ctrl+B"));
    QPushButton *italicBtn = mkBtn(":/icons/italic.png", QKeySequence("Ctrl+I"));
    QPushButton *titleBtn = mkBtn(":/icons/title.png", QKeySequence("Ctrl+T"));
    QPushButton *underlineBtn = mkBtn(":/icons/underline.png", QKeySequence("Ctrl+U"));

    connect(boldBtn, &QPushButton::clicked, this, &Toolbar::makeBold);
    connect(italicBtn, &QPushButton::clicked, this, &Toolbar::makeItalic);
    connect(titleBtn, &QPushButton::clicked, this, &Toolbar::makeTitle);
    connect(underlineBtn, &QPushButton::clicked, this, &Toolbar::makeUnderline);

    addWidget(boldBtn);
    addWidget(italicBtn);
    addWidget(titleBtn);
    addWidget(underlineBtn);
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

void Toolbar::makeTitle()
{
    QTextCursor cursor = editor->textCursor();
    QString selectedText = cursor.selectedText();
    if (!selectedText.isEmpty())
        cursor.insertText("# " + selectedText);
    else
        cursor.insertText("# ");
}

void Toolbar::makeUnderline()
{
    QTextCursor cursor = editor->textCursor();
    QString selectedText = cursor.selectedText();
    if (!selectedText.isEmpty())
        cursor.insertText("`" + selectedText + "`");
    else
        cursor.insertText("`");
}