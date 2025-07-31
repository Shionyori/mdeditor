// src/MainWindow.cpp
#include "MainWindow.h"
#include "MarkdownRenderer.h"
#include <QSplitter>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setStyleSheet(
        "QWidget { background-color: #e8e8fa; color: #333333; }"
        "QToolBar { background-color: #c9c9ff; border: none; }"
        "QMenuBar { background-color: #acacfa; }"
        "QMenuBar::item { color: #333333; }"
        "QMenuBar::item:hover, QMenuBar::item:selected { background-color: #7b7bdb; }"
        "QMenu { background-color: rgba(232, 232, 250, 192); border: 1px solid #7b7bdb;}"
        "QMenu::item { color: #333333; }"
        "QMenu::item:hover, QMenu::item:selected { background-color: #7b7bdb; }"
        "QPushButton { background-color: #c9c9ff; border: none; padding: 2px; border-radius: 2px; }"
        "QPushButton:hover { background-color: #adadd7; }"
        "QPushButton:pressed { background-color: #a4a4cd; }"
    );

    QIcon icon(":/icons/app_icon.png");
    setWindowIcon(icon);

    initUI();
    createDockWidgets();
    connectSignals();

    loadDefaultDocument();
}

void MainWindow::initUI()
{
    editor = new Editor(this);
    preview = new Preview(editor, this);

    toolbar = new Toolbar(editor, this);
    toolbar->setObjectName("Toolbar");
    toolbar->setWindowTitle("工具栏");

    menu = new Menu(this);

    addToolBar(toolbar);
    setMenuBar(menu->getMenuBar());
}

void MainWindow::createDockWidgets()
{
    QDockWidget* editorDock = new QDockWidget("编辑器", this);
    editorDock->setWidget(editor);
    editorDock->setObjectName("EditorDock");
    editorDock->setFeatures(QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::LeftDockWidgetArea, editorDock);

    QDockWidget* previewDock = new QDockWidget("预览", this);
    previewDock->setWidget(preview);
    previewDock->setObjectName("PreviewDock");
    previewDock->setFeatures(QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::RightDockWidgetArea, previewDock);

    // 设置窗口堆叠属性
    setDockOptions(QMainWindow::AllowNestedDocks);
    editorDock->setFeatures(QDockWidget::DockWidgetMovable); // 禁用浮动
    previewDock->setFeatures(QDockWidget::DockWidgetMovable); // 禁用浮动

    // 设置默认停靠关系
    splitDockWidget(editorDock, previewDock, Qt::Horizontal);
    resizeDocks({editorDock, previewDock}, {1, 2}, Qt::Horizontal); // 设置初始比例

    editorDock->setMinimumSize(200, 150);
    previewDock->setMinimumSize(200, 150);
}

void MainWindow::connectSignals()
{
    connect(editor, &QTextEdit::textChanged, preview, &Preview::updatePreview);
    connect(menu->getNewAction(), &QAction::triggered, editor, &Editor::newFile);
    connect(menu->getOpenAction(), &QAction::triggered, editor, &Editor::openFile);
    connect(menu->getSaveAction(), &QAction::triggered, editor, &Editor::saveFile);
    connect(menu->getSaveAsAction(), &QAction::triggered, editor, &Editor::saveAs);
}

void MainWindow::loadDefaultDocument()
{
    QString defaultFilePath = QString(QDir::currentPath() + "/res/default.md"); // 假设默认文档在资源文件中
    QFile file(defaultFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString content = in.readAll();
        editor->setPlainText(content);
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "错误", "无法加载默认文档");
    }
}