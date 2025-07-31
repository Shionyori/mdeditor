#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置样式表
    setStyleSheet(
        "QWidget { background-color: #e8e8fa; color: #333333; }"
        "QToolBar { background-color: #c9c9ff; border: none; }"
        "QLabel { color: #333333; }"
        "QPushButton { background-color: #c9c9ff; border: none; padding: 10px; }"
        "QPushButton:hover { background-color: #adadd7; }"
        "QPushButton:pressed { background-color: #a4a4cd; }"
        "QMenuBar { background-color: #9898fc; }"
        "QMenuBar::item { color: #333333; }"
        "QMenuBar::item:hover, QMenuBar::item:selected { background-color: #7b7bdb; }"
        "QMenu { background-color: rgba(232, 232, 250, 192); border: 1px solid #7b7bdb; }"
        "QMenu::item { color: #333333; }"
        "QMenu::item:hover, QMenu::item:selected { background-color: #7b7bdb; }"
    );

    // 设置窗口图标
    QIcon icon(":/icons/app_icon.png");
    setWindowIcon(icon);

    // 初始化成员变量
    viewPage = new ViewPage(this);
    settingPage = new SettingPage(this);

    // 创建 QStackedWidget
    QStackedWidget* stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(viewPage);
    stackedWidget->addWidget(settingPage);

    // 创建导航栏
    QToolBar* navigationBar = createNavigationBar(stackedWidget);

    // 添加导航栏到主窗口的左侧
    addToolBar(Qt::LeftToolBarArea, navigationBar);

    // 创建菜单栏
    createMenuBar();

    // 设置主窗口的中央部件
    setCentralWidget(stackedWidget);

    restoreLayout(); // 恢复布局
}

void MainWindow::newFile()
{
    viewPage->newFile();
}

void MainWindow::openFile()
{
    viewPage->openFile();
}

void MainWindow::saveFile()
{
    viewPage->saveFile();
}

void MainWindow::saveAsFile()
{
    viewPage->saveAs();
}

// 创建导航栏
QToolBar* MainWindow::createNavigationBar(QStackedWidget* stackedWidget)
{
    QToolBar* navigationBar = new QToolBar(this);
    navigationBar->setOrientation(Qt::Vertical);
    navigationBar->setFloatable(false);
    navigationBar->setMovable(false);
    navigationBar->setStyleSheet("QToolBar { background-color: #acacfa; border: none; }");

    // 添加导航按钮
    QPushButton* viewPageButton = new QPushButton(this);
    viewPageButton->setIcon(QIcon(":/icons/view_icon.png"));
    viewPageButton->setIconSize(QSize(30, 30));
    viewPageButton->setStyleSheet("QPushButton { background-color: #c9c9ff; }");

    QPushButton* settingPageButton = new QPushButton(this);
    settingPageButton->setIcon(QIcon(":/icons/setting_icon.png"));
    settingPageButton->setIconSize(QSize(30, 30));
    settingPageButton->setStyleSheet(
        "QPushButton { background-color: #acacfa; }"
        "QPushButton:hover { background-color: #d9d9f3; }");

    navigationBar->addWidget(viewPageButton);
    navigationBar->addWidget(settingPageButton);

    // 连接按钮信号到槽
    connect(viewPageButton, &QPushButton::clicked, [this, viewPageButton, settingPageButton, stackedWidget]() {
        stackedWidget->setCurrentIndex(0);
        viewPageButton->setStyleSheet("QPushButton { background-color: #c9c9ff; }");
        settingPageButton->setStyleSheet(
            "QPushButton { background-color: #acacfa; }"
            "QPushButton:hover { background-color: #d9d9f3; }");
    });

    connect(settingPageButton, &QPushButton::clicked, [this, viewPageButton, settingPageButton, stackedWidget]() {
        stackedWidget->setCurrentIndex(1);
        settingPageButton->setStyleSheet("QPushButton { background-color: #c9c9ff; }");
        viewPageButton->setStyleSheet(
            "QPushButton { background-color: #acacfa; }"
            "QPushButton:hover { background-color: #d9d9f3; }");
    });

    return navigationBar;
}

// 创建菜单栏
void MainWindow::createMenuBar()
{
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* fileMenu = menuBar->addMenu(tr("文件"));
    QAction* newAction = fileMenu->addAction(tr("新建"));
    newAction->setShortcut(QKeySequence("Ctrl+N"));
    QAction* openAction = fileMenu->addAction(tr("打开"));
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    QAction* saveAction = fileMenu->addAction(tr("保存"));
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    QAction* saveAsAction = fileMenu->addAction(tr("另存为"));
    saveAsAction->setShortcut(QKeySequence("Ctrl+Shift+S"));

    setMenuBar(menuBar);

    // 连接菜单项信号到槽
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAsFile);
}

void MainWindow::restoreLayout()
{
    QSettings settings("ShionLyrics", "Mdeditor");
    QByteArray state = settings.value("mainWindowState").toByteArray();
    if (!state.isEmpty()) {
        restoreState(state);
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QSettings settings("ShionLyrics", "Mdeditor");
    settings.setValue("mainWindowState", saveState());
    settings.setValue("viewPageState", viewPage->saveState());
    QMainWindow::closeEvent(event);
}