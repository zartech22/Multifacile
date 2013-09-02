#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenu>
#include <QHelpEvent>
#include <QEvent>
#include <QToolTip>

class Menu : public QMenu
{
public:
    Menu(QString title, QWidget *parent = 0) : QMenu(title, parent) { }
    virtual bool event(QEvent *e);
};

#endif // MENUBAR_H
