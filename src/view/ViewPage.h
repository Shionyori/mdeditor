// src/ViewPage.h
#ifndef VIEWPAGE_H
#define VIEWPAGE_H

#include <QMainWindow>
#include <QDockWidget>
#include <QSplitter>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include "../component/Editor.h"
#include "../component/Preview.h"
#include "../component/Toolbar.h"

class ViewPage : public QMainWindow
{
    Q_OBJECT

public:
    ViewPage(QWidget *parent = nullptr);

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAs();

private:
    Editor* editor;
    Preview* preview;
    Toolbar* toolbar;

    QDockWidget* editorDock;
    QDockWidget* previewDock;

    void initUI();
    void createDockWidgets();
    void connectSignals();
    void loadDefaultDocument();
    void restoreLayout();
};

#endif // VIEWPAGE_H