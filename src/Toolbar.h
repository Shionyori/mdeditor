// src/Toolbar.h
#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>

class Toolbar : public QToolBar
{
    Q_OBJECT

public:
    Toolbar(QTextEdit* editor, QWidget *parent = nullptr);

private slots:
    void makeBold();
    void makeItalic();

private:
    QTextEdit* editor;
};

#endif // TOOLBAR_H