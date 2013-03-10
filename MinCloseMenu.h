#ifndef MINCLOSEMENU_H
#define MINCLOSEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>

class MinCloseMenu : public QWidget
{
    Q_OBJECT

public:
    MinCloseMenu(QWidget *parent = 0);
    ~MinCloseMenu();
private:
    QHBoxLayout *layout;

    QPushButton *mini, *cross;

    QWidget *ParentWidget;
};

#endif // MINCLOSEMENU_H
