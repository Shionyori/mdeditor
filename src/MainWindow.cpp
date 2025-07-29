#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    editor = new QPlainTextEdit(this);

    preview = new QWebEngineView(this);
    preview->setUrl(QUrl("qrc:/index.html"));

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(editor);
    layout->addWidget(preview);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    QAction *openAction = fileMenu->addAction(tr("&Open..."));
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    QAction *saveAction = fileMenu->addAction(tr("&Save..."));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    setMenuBar(menuBar);

    QWebChannel *channel = new QWebChannel(this);
    preview->page()->setWebChannel(channel);

    connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::updatePreview);
}

MainWindow::~MainWindow(){};

void MainWindow::openFile() 
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Markdown File"), "", tr("Markdown Files (*.md);;All Files (*)"));
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            editor->setPlainText(in.readAll());
            file.close();
        }
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Markdown File"), "", tr("Markdown Files (*.md);;All Files (*)"));
    if (!fileName.isEmpty()) 
    {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) 
        {
            QTextStream out(&file);
            out << editor->toPlainText();
            file.close();
        }
    }
}

void MainWindow::updatePreview()
{
    QString md = editor->toPlainText();
    preview->page()->runJavaScript(QString("renderMarkdown(%1)").arg(md));
}