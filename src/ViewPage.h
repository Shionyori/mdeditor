#ifndef VIEWPAGE_H
#define VIEWPAGE_H

#include <QMainWindow>
#include "Editor.h"
#include "Preview.h"
#include "Toolbar.h"

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