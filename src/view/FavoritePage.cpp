// src/FavoritePage.cpp
#include "FavoritePage.h"

FavoritePage::FavoritePage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel("这里是收藏窗口", this);
    layout->addWidget(label);
    setLayout(layout);
}