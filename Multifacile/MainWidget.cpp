#include "MainWidget.h"

MainWidget::MainWidget(Mode mode) : QWidget()
{
    _texte = new QLabel(tr("Choisis la table de multiplication que tu souhaites travailler !"));
    _texte->setAttribute(Qt::WA_TranslucentBackground);

    _point = new QLabel;
    _point->setPixmap(QPixmap(":/image/Point.png"));

    _mapper = new QSignalMapper(this);

    for(int i = 0; i < 10; ++i)
    {
        if(mode == EASY || mode == MEDIUM)
            _bouton[i] = new QPushButton(tr("La table de ")+QString::number(i+1), this);
        else // _mode == HARD
            _bouton[i] = new QPushButton(tr("La table aléatoire"), this);

        _bouton[i]->setFixedSize(256, 94);

        connect(_bouton[i], SIGNAL(clicked()), _mapper, SLOT(map()));
        _mapper->setMapping(_bouton[i], i+1);
    }

    checkSucceedTables(mode);

    _quit = new QPushButton(tr("Quitter"));
    _quit->setFixedSize(70, 40);
    _quit->setObjectName("QuitButton");

    _texte->setParent(this);
    _texte->move(68, 25);

    _point->setParent(this);
    _point->move(50, 38);

    _quit->setParent(this);
    _quit->move(490, 480);

    for(int i = 0, j = 0; i < 10; ++i)
    {
        if(i % 2 == 0)
            _bouton[i]->move(80, (75 + 80 * j));
        else
        {
            _bouton[i]->move(320, (75 + 80 * j));
            ++j;
        }
    }


    connect(_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(_mapper, SIGNAL(mapped(int)), this, SIGNAL(clicked(int)));
}

void MainWidget::checkSucceedTables(Mode mode)
{
    if(mode != HARD)
    {
        QMap<int, bool> *list = DataFileMgr::getNoErrorList("Multifacile.xml", (mode == EASY) ? "EasyMode" : "MediumMode");

        for(QMap<int, bool>::Iterator it = list->begin(); it != list->end(); ++it)
            if(it.value())
                _bouton[ (it.key() - 1)]->setStyleSheet("background-image: url(\":/image/Bouton_succes.png\");");

        delete list;

    }
}

void MainWidget::updateButtonsLabels(Mode mode)
{
    if(mode == EASY || mode == MEDIUM)
    {
        for(int i = 0; i < 10; ++i)
        {
            _bouton[i]->setText(tr("La table de ") + QString::number(i+1));
            _bouton[i]->setStyleSheet("");
        }

        checkSucceedTables(mode);
    }
    else if(mode == HARD)
    {
        for(int i = 0; i < 10; ++i)
        {
            _bouton[i]->setText(tr("La table aléatoire"));
            _bouton[i]->setStyleSheet("");
        }
    }
}

void MainWidget::updateButtonsLabels(Mode mode, bool isProgressifMode)
{
    if(mode == MEDIUM && isProgressifMode)
    {
        for(int i = 0; i < 10; ++i)
            if(!DataFileMgr::hasNoErrorTrue("Multifacile.xml", "EasyMode", (i + 1)))
                _bouton[i]->setStyleSheet("background-image: url(\":/image/Bouton_inacessible.png\"); color: grey;");
    }
    else if(mode == MEDIUM && !isProgressifMode)
        for(int i = 0; i < 10; ++i)
        {
            if(!DataFileMgr::hasNoErrorTrue("Multifacile.xml", "EasyMode", (i + 1)) && !DataFileMgr::hasNoErrorTrue("Multifacile.xml", "MediumMode", (i + 1)))
                _bouton[i]->setStyleSheet("");
            else
                _bouton[i]->setStyleSheet("background-image: url(\":/image/Bouton_succes.png\");");
        }
}
