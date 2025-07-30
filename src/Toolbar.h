// src/Toolbar.h
#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QBoxLayout>

class Toolbar : public QWidget
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