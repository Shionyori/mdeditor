// src/SettingPage.cpp
#include "SettingPage.h"

SettingPage::SettingPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    auto *icon = new QLabel(this);
    icon->setPixmap(QPixmap(":/icons/under_construction.png"));
    icon->setFixedSize(128, 128);          
    icon->setScaledContents(true);

    auto *text = new QLabel(this);
    text->setText(tr("设置页面，未实现"));
    text->setAlignment(Qt::AlignHCenter);
    QFont f = text->font();
    f.setPixelSize(16);
    f.setBold(true);
    text->setFont(f);

    mainLayout->addWidget(icon);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(text);
}