// src/Toolbar.h
#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStyle>

class Toolbar : public QToolBar
{
    Q_OBJECT

public:
    Toolbar(QTextEdit* editor, QWidget *parent = nullptr);

private slots:
    void makeBold();
    void makeItalic();
    void makeTitle();
    void makeUnderline();

private:
    QTextEdit* editor;
};

#endif // TOOLBAR_H