#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QWebEngineView>
#include <QToolBar>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QSplitter>
#include <QMouseEvent>
#include <QPushButton>
#include <QBoxLayout>
#include <QToolBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void updatePreview();
    void newFile();
    void openFile();
    void saveFile();
    void saveAs();

private:
    QTextEdit* editor;
    QWebEngineView* preview;
    QString currentFilePath;

    QAction* openAction;
    QAction* saveAction; 
    QAction* newAction;     
    QAction* saveAsAction;  
    QAction* aboutAction;       

    void createActions();
    void createMenus();
    void createToolBars();
};

#endif // MAINWINDOW_H