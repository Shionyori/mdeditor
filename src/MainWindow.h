// src/MainWindow.h
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
#include <QStatusBar>
#include "component/Menubar.h"
#include "view/ViewPage.h"
#include "view/FavoritePage.h"
#include "view/SettingPage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QToolBar* createNavigationBar(QStackedWidget* stackedWidget);
    QStatusBar* createStatusBar();
    void restoreLayout();
    
protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Menubar* menubar;
    ViewPage* viewPage;
    FavoritePage* favoritePage;
    SettingPage* settingPage;
};

#endif // MAINWINDOW_H