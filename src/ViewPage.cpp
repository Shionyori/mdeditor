#include "ViewPage.h"
#include <QDockWidget>
#include <QSplitter>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

ViewPage::ViewPage(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "ViewPage constructed";
    initUI();
    createDockWidgets();
    connectSignals();
    loadDefaultDocument();
}

ViewPage::~ViewPage()
{
    qDebug() << "ViewPage destructed";
}

void ViewPage::initUI()
{
    editor = new Editor(this);
    preview = new Preview(editor, this);

    toolbar = new Toolbar(editor, this);
    toolbar->setObjectName("Toolbar");
    toolbar->setWindowTitle("工具栏");

    addToolBar(toolbar);
}

void ViewPage::createDockWidgets()
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

    setDockOptions(QMainWindow::AllowTabbedDocks);
    splitDockWidget(editorDock, previewDock, Qt::Horizontal);
    resizeDocks({editorDock, previewDock}, {1, 2}, Qt::Horizontal);

    editorDock->setMinimumSize(300, 225);
    previewDock->setMinimumSize(300, 225);
}

void ViewPage::connectSignals()
{
    connect(editor, &QTextEdit::textChanged, preview, &Preview::updatePreview);
}

void ViewPage::loadDefaultDocument()
{
    QString defaultFilePath = QString(QDir::currentPath() + "/res/default.md");
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

void ViewPage::newFile()
{
    editor->newFile();
}

void ViewPage::openFile()
{
    editor->openFile();
}

void ViewPage::saveFile()
{
    editor->saveFile();
}

void ViewPage::saveAs()
{
    editor->saveAs();
}