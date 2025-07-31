// src/Menu.cpp
#include "Menu.h"

Menu::Menu(QWidget *parent)
    : QObject(parent)
{
    menuBar = new QMenuBar(parent);

    newAction = new QAction("新建", this);
    newAction->setShortcut(QKeySequence("Ctrl+N"));

    openAction = new QAction("打开", this);
    openAction->setShortcut(QKeySequence("Ctrl+O"));

    saveAction = new QAction("保存", this);
    saveAction->setShortcut(QKeySequence("Ctrl+S"));

    saveAsAction = new QAction("另存为", this);
    saveAsAction->setShortcut(QKeySequence("Ctrl+Shift+S"));

    QMenu* fileMenu = menuBar->addMenu("文件");
    fileMenu->addAction(newAction);
    fileMenu->addSeparator();
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAsAction);
}

QMenuBar* Menu::getMenuBar() const
{
    return menuBar;
}

QAction* Menu::getNewAction() const
{
    return newAction;
}

QAction* Menu::getOpenAction() const
{
    return openAction;
}

QAction* Menu::getSaveAction() const
{
    return saveAction;
}

QAction* Menu::getSaveAsAction() const
{
    return saveAsAction;
}