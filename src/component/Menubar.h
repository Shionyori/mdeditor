// src/Menubar.h
#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include <QMenu>
#include "../view/ViewPage.h"

class Menubar : public QMenuBar
{
    QOBJECT_H

public:
    Menubar(ViewPage* viewPage,QWidget* parent = nullptr);

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();

private:

    ViewPage* viewPage;
};


#endif // MENUBAR_H