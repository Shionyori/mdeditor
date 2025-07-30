// src/MainWindow.cpp
#include "MainWindow.h"
#include "MarkdownRenderer.h"
#include "Toolbar.h"
#include <QSplitter>
#include <QBoxLayout>
#include <QDockWidget>

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

    // 创建编辑器和预览窗口
    editor = new QTextEdit(this);
    preview = new QWebEngineView(this);

    // 创建工具栏
    QToolBar* toolbar = addToolBar("工具栏");
    toolbar->addWidget(new Toolbar(editor));

    // // 创建水平分割器
    // QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    // splitter->addWidget(editor);
    // splitter->addWidget(preview);
    // splitter->setSizes({300, 600});

    // 设置主窗口的中心部件
    // setCentralWidget(splitter);

    // 创建 Dock Widgets
    QDockWidget* editorDock = new QDockWidget("编辑器", this);
    editorDock->setWidget(editor);
    editorDock->setObjectName("EditorDock");
    addDockWidget(Qt::LeftDockWidgetArea, editorDock);

    QDockWidget* previewDock = new QDockWidget("预览", this);
    previewDock->setWidget(preview);
    previewDock->setObjectName("PreviewDock");
    addDockWidget(Qt::RightDockWidgetArea, previewDock);

    // 禁用停靠到上下区域
    setDockOptions(QMainWindow::AllowNestedDocks);
    editorDock->setFeatures(QDockWidget::DockWidgetMovable); // 禁用浮动
    previewDock->setFeatures(QDockWidget::DockWidgetMovable); // 禁用浮动

    // 设置默认停靠关系
    splitDockWidget(editorDock, previewDock, Qt::Horizontal);
    resizeDocks({editorDock, previewDock}, {1, 2}, Qt::Horizontal); // 设置初始比例

    // 设置最小宽度限制
    editorDock->setMinimumSize(200, 150); 
    previewDock->setMinimumSize(200, 150); 

    // 监听编辑器内容变化
    connect(editor, &QTextEdit::textChanged, this, &MainWindow::updatePreview);

    // 创建动作
    createActions();
    // 创建菜单
    createMenus();

    // 指定默认文件的绝对路径
    initDefaultFile(QDir::currentPath() + "/res/default.md");
}

void MainWindow::updatePreview()
{
    QString markdownText = editor->toPlainText();
    QString htmlText = MarkdownRenderer::markdownToHtml(markdownText);
    preview->setHtml(htmlText);
}

void MainWindow::newFile()
{
    editor->clear();
    currentFilePath.clear();
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "打开 Markdown 文件", "", "Markdown 文件 (*.md);;所有文件 (*)");
    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            QString content = in.readAll();
            editor->setPlainText(content);
            file.close();
            currentFilePath = filePath;
        }
        else
        {
            QMessageBox::critical(this, "错误", "无法打开文件");
        }
    }
}

void MainWindow::saveFile()
{
    QString filePath = currentFilePath.isEmpty() ? QFileDialog::getSaveFileName(this, "保存 Markdown 文件", "", "Markdown 文件 (*.md);;所有文件 (*)") : currentFilePath;
    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << editor->toPlainText();
            file.close();
            currentFilePath = filePath;
        }
        else
        {
            QMessageBox::critical(this, "错误", "无法保存文件");
        }
    }
}

void MainWindow::saveAs()
{
    QString f = QFileDialog::getSaveFileName(this, "Save As", "", "Markdown (*.md)");
    if (!f.isEmpty()) {
        currentFilePath = f;
        saveFile();
    }
}

void MainWindow::createActions()
{
    newAction = new QAction("新建", this);
    newAction->setShortcut(QKeySequence("Ctrl+N"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);

    openAction = new QAction("打开", this);
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    saveAction = new QAction("保存", this);
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    saveAsAction = new QAction("另存为", this);
    saveAsAction->setShortcut(QKeySequence("Ctrl+Shift+S"));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);
}

void MainWindow::createMenus()
{
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu* fileMenu = menuBar->addMenu("文件");
    fileMenu->addAction(newAction);
    fileMenu->addSeparator();
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAsAction);
}

void MainWindow::initDefaultFile(QString defaultFilePath)
{
    if (QFile::exists(defaultFilePath)) {
        QFile file(defaultFilePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString content = in.readAll();
            editor->setPlainText(content);
            file.close();
            currentFilePath = defaultFilePath;
        } else {
            QMessageBox::critical(this, "错误", "无法打开默认文件");
        }
    } else {
        QMessageBox::information(this, "提示", "默认文件不存在，将创建一个新文件。");
    }   
}