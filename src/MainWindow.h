#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QToolBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include "ViewPage.h"
#include "SettingPage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();

    QToolBar* createNavigationBar(QStackedWidget* stackedWidget);
    void createMenuBar();

    void restoreLayout();
    
protected:
    void closeEvent(QCloseEvent* event) override;

private:
    QMenuBar* menuBar; // 菜单栏
    QMenu* fileMenu;   // 菜单
    QAction* newAction; // 新建操作
    QAction* openAction; // 打开操作
    QAction* saveAction; // 保存操作
    QAction* saveAsAction; // 另存为操作

    ViewPage* viewPage;
    SettingPage* settingPage;
};

#endif // MAINWINDOW_H