// src/SettingPage.cpp
#include "SettingPage.h"

SettingPage::SettingPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel("这里是设置窗口", this);
    layout->addWidget(label);
    setLayout(layout);
}