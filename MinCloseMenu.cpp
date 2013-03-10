#include "MinCloseMenu.h"

MinCloseMenu::MinCloseMenu(QWidget *parent) : QWidget(parent), ParentWidget(parent)
{
    cross = new QPushButton("X");
    mini = new QPushButton("_");

    cross->setObjectName("Cross");
    mini->setObjectName("mini");

    layout = new QHBoxLayout;

    layout->addWidget(mini);
    layout->addWidget(cross);

    this->setLayout(layout);

    connect(cross, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(mini, SIGNAL(clicked()), ParentWidget, SLOT(showMinimized()));
}
MinCloseMenu::~MinCloseMenu()
{
    delete cross, mini, layout;

    cross = nullptr;
    mini = nullptr;
    layout = nullptr;
}
