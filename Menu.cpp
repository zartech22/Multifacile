#include "Menu.h"


bool Menu::event(QEvent *e)
{

    if(e->type() == QEvent::ToolTip)
    {
        QHelpEvent *he = dynamic_cast<QHelpEvent*>(e);
        QAction *act = actionAt(he->pos());

        if(act)
            QToolTip::showText(he->globalPos(), act->toolTip());
    }
    else
        QToolTip::hideText();

    return QMenu::event(e);
}
