// src/Menubar.cpp
#include "Menubar.h"

Menubar::Menubar(ViewPage* viewPage ,QWidget* parent) 
    : QMenuBar(parent), viewPage(viewPage)
{
    
    setStyleSheet(
        "QMenuBar { background-color: #9898fc; }"
        "QMenuBar::item { color: #333333; width: 80px; height: 30px; padding: 10px 15px; }"
        "QMenuBar::item:hover, QMenuBar::item:selected { background-color: #7b7bdb; }"
        "QMenu { background-color: rgba(232, 232, 250, 192); border: 1px solid #7b7bdb; }"
        "QMenu::item { color: #333333; }"
        "QMenu::item:hover, QMenu::item:selected { background-color: #7b7bdb; }"
    );

    QMenu* fileMenu = addMenu(tr("文件(F)"));
    QAction* newAction = fileMenu->addAction(tr("新建"));
    newAction->setShortcut(QKeySequence("Ctrl+N"));
    QAction* openAction = fileMenu->addAction(tr("打开"));
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    fileMenu->addSeparator();
    QAction* saveAction = fileMenu->addAction(tr("保存"));
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    QAction* saveAsAction = fileMenu->addAction(tr("另存为"));
    saveAsAction->setShortcut(QKeySequence("Ctrl+Shift+S"));

    QMenu* editMenu = addMenu(tr("编辑(E)"));
    QAction* undoAction = editMenu->addAction(tr("撤销"));
    undoAction->setShortcut(QKeySequence("Ctrl+Z"));
    QAction* restoreAction = editMenu->addAction(tr("恢复"));
    restoreAction->setShortcut(QKeySequence("Ctrl+Y"));
    editMenu->addSeparator();
    QAction* cutAction = editMenu->addAction(tr("剪切"));
    cutAction->setShortcut(QKeySequence("Ctrl+X"));
    QAction* copyAction = editMenu->addAction(tr("复制"));
    copyAction->setShortcut(QKeySequence("Ctrl+C"));
    QAction* pasteAction = editMenu->addAction(tr("粘贴"));
    pasteAction->setShortcut(QKeySequence("Ctrl+V"));

    QMenu* chooseMenu = addMenu(tr("选择(S)"));
    QAction* chooseAllAction = chooseMenu->addAction(tr("全选"));
    chooseAllAction->setShortcut(QKeySequence("Ctrl+A"));

    // 连接菜单项信号到槽
    connect(newAction, &QAction::triggered, this, &Menubar::newFile);
    connect(openAction, &QAction::triggered, this, &Menubar::openFile);
    connect(saveAction, &QAction::triggered, this, &Menubar::saveFile);
    connect(saveAsAction, &QAction::triggered, this, &Menubar::saveAsFile);
}

void Menubar::newFile()
{
    viewPage->newFile();
}

void Menubar::openFile()
{
    viewPage->openFile();
}

void Menubar::saveFile()
{
    viewPage->saveFile();
}

void Menubar::saveAsFile()
{
    viewPage->saveAs();
}