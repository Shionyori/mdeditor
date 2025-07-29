#include "MainWindow.h"
#include <QDockWidget>
#include <QFile>
#include <QUrl>
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 创建编辑区域
    editor = new QPlainTextEdit(this);
    setCentralWidget(editor);

    // 创建预览区域
    preview = new QWebEngineView(this);
    dock = new QDockWidget("Preview", this);
    dock->setWidget(preview);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    // 加载默认 Markdown 文件
    QFile defaultTextFile(":/res/default.md");
    if (defaultTextFile.open(QIODevice::ReadOnly)) {
        editor->setPlainText(defaultTextFile.readAll());
        defaultTextFile.close();
    } else {
        qDebug() << "Failed to load default.md file.";
    }

    QFile file(":/res/default.md");
    if (file.exists()) {
        qDebug() << "Resource file exists:" << file.fileName();
    } else {
        qDebug() << "Resource file does not exist:" << file.fileName();
    }

    // 初始化 QWebChannel
    channel = new QWebChannel(this);
    content = new Document(this);
    channel->registerObject(QStringLiteral("content"), content);
    preview->page()->setWebChannel(channel);

    // 加载预览页面
    QUrl url("qrc:/res/index.html");
    qDebug() << "Loading URL:" << url;
    preview->setUrl(url);

    // 连接编辑区域的文本变化信号
    connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::updateContent);
}

void MainWindow::updateContent()
{
    content->setText(editor->toPlainText());
}