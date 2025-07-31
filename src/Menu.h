// src/Menu.h
#ifndef MENU_H
#define MENU_H

#include <QMenuBar>
#include <QAction>

class Menu : public QObject
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);

    QMenuBar* getMenuBar() const;
    QAction* getNewAction() const;
    QAction* getOpenAction() const;
    QAction* getSaveAction() const;
    QAction* getSaveAsAction() const;

private:
    QMenuBar* menuBar;
    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;
};

#endif // MENU_H