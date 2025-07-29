#pragma once

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QWebEngineView>
#include <QWebChannel>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void saveFile();
    void updatePreview();

private:
    QPlainTextEdit* editor;
    QWebEngineView *preview;
};