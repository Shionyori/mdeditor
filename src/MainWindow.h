// src/MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QWebEngineView>
#include <QDockWidget>
#include <QAction>
#include "Editor.h"
#include "Preview.h"
#include "Toolbar.h"
#include "Menu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    Editor* editor;
    Preview* preview;
    Toolbar* toolbar;
    Menu* menu;

    void initUI();
    void createDockWidgets();
    void connectSignals();
    void loadDefaultDocument();
};

#endif // MAINWINDOW_H