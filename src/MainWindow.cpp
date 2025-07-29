#include "MainWindow.h"
#include <QApplication>
#include <QWebChannel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 创建WebEngineView
    view = new QWebEngineView(this);
    view->setUrl(QUrl("qrc:/index.html"));

    // 设置WebChannel
    channel = new QWebChannel(this);
    view->page()->setWebChannel(channel);

    // 设置主窗口的中心部件
    setCentralWidget(view);

    // 创建菜单栏
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    QAction *openAction = fileMenu->addAction(tr("&Open File..."));
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    setMenuBar(menuBar);
}

MainWindow::~MainWindow() = default;

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Markdown File"), "", tr("Markdown Files (*.md);;All Files (*)"));
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString content = in.readAll();
            file.close();

            // 打印文件内容以确保内容正确加载
            qDebug() << "Loaded content:" << content;

            // 将内容传递到JavaScript进行渲染
            view->page()->runJavaScript(QString("editor.innerText = %1; renderMarkdown(editor.innerText);").arg(content));
        } else {
            QMessageBox::critical(this, tr("Error"), tr("Failed to open file: %1").arg(filePath));
        }
    }
}