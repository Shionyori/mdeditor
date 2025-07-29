#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QWebEngineView>
#include <QWebChannel>
#include "document.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void updateContent();

private:
    QPlainTextEdit *editor;
    QWebEngineView *preview;
    QDockWidget *dock;
    QWebChannel *channel;
    Document *content;
};

#endif // MAINWINDOW_H