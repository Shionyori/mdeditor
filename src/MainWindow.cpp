// src/MainWindow.cpp
#include "MainWindow.h"
#include <QOverload>
#include <QButtonGroup>

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
    );

    // 设置窗口图标
    QIcon icon(":/icons/app_icon.png");
    setWindowIcon(icon);

    // 初始化成员变量
    viewPage = new ViewPage(this);
    favoritePage = new FavoritePage(this);
    settingPage = new SettingPage(this);

    // 创建 QStackedWidget
    QStackedWidget* stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(viewPage);
    stackedWidget->addWidget(favoritePage);
    stackedWidget->addWidget(settingPage);

    // 创建导航栏
    QToolBar* navigationBar = createNavigationBar(stackedWidget);

    // 添加导航栏到主窗口的左侧
    addToolBar(Qt::LeftToolBarArea, navigationBar);

    // 创建菜单栏
    menubar = new Menubar(viewPage, this);
    setMenuBar(menubar);

    // 设置主窗口的中央部件
    setCentralWidget(stackedWidget);

    restoreLayout(); // 恢复布局
}


// 描述导航页按钮
struct NavItem
{
    QString iconPath;
    QString tip;
    int targetIndex;   // 对应 QStackedWidget 的页号
};

static const QList<NavItem> navItems = {
    { ":/icons/view_icon.png", "视图", 0 },
    { ":/icons/favorite_icon.png", "收藏", 1 },
    { ":/icons/setting_icon.png", "设置", 2 },
};

QToolBar* MainWindow::createNavigationBar(QStackedWidget* stackedWidget)
{
    QToolBar* navigationBar = new QToolBar(this);
    navigationBar->setObjectName("NavigationBar");
    navigationBar->setWindowTitle("导航栏");
    navigationBar->setOrientation(Qt::Vertical);
    navigationBar->setFloatable(false);
    navigationBar->setMovable(false);
    navigationBar->setStyleSheet("QToolBar { background-color: #acacfa; border: none; }");

    // 互斥按钮组
    auto* group = new QButtonGroup(navigationBar);   
    group->setExclusive(true);

    for (const NavItem& item : navItems)
    {
        auto* btn = new QPushButton(navigationBar);
        btn->setIcon(QIcon(item.iconPath));
        btn->setIconSize({32, 32});
        btn->setFixedSize({42, 52});
        btn->setToolTip(item.tip);
        btn->setCheckable(true);           // 允许弹起/按下
        btn->setAutoExclusive(true);       // 互斥
        btn->setProperty("pageIndex", item.targetIndex);

        btn->setStyleSheet(
            "QPushButton { border: none; background: #acacfa; padding: 6px; }"
            "QPushButton:hover:!checked { background: #d9d9f3; }"
            "QPushButton:checked { background: #c9c9ff; }"
        );

        navigationBar->addWidget(btn);
        group->addButton(btn);
    }

    connect(group, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
            [stackedWidget](QAbstractButton* btn)
    {
        int idx = btn->property("pageIndex").toInt();
        stackedWidget->setCurrentIndex(idx);
    });

    // 默认选中第0个按钮
    if (QAbstractButton* firstBtn = group->buttons().value(0))
        firstBtn->setChecked(true);

    return navigationBar;
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