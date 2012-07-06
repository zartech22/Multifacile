#include "fen_correction.h"

Fen_correction::Fen_correction(const int multiple, SpinBox *reponses[], int *order, int time, Mode mode)
{

    if(time != 0)
        timeElapsed = time;
    this->setWindowTitle(tr("Correction"));
    note = 10;

    tab = order;

    for(int i = 0; i < 4; i++)
        timeTab[i] = 0;

    for(int i = 0; i < 10; i++)
        reponse[i] = reponses[i]->value();

    setWindowLayout(multiple);

    this->setLayout(vlayout);

    if(time != 0)
    {
        if(note == 10)
        {
            QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Multifacile", QString(), this);
            if(mode == EASY)
                settings.beginGroup("EasyMode");
            else if(mode == MEDIUM)
                settings.beginGroup("MediumMode");
            if(!settings.contains("TableDe"+QString::number(multiple)))
            {
                settings.setValue("TableDe"+QString::number(multiple), timeElapsed);
                returnTime(timeElapsed, NORECORD);
                QMessageBox::information(this, tr("Temps de réponses"), tr("Tu as mis ")+QString::number(timeTab[1])+tr(" minute(s) et ")+QString::number(timeTab[0])+tr(" secondes."));
            }
            else
            {
                if(1000 < settings.value("TableDe"+QString::number(multiple)).toInt())
                    settings.setValue("TableDe"+QString::number(multiple), (settings.value("TableDe"+QString::number(multiple)).toInt()/1000));
                if(timeElapsed < settings.value("TableDe"+QString::number(multiple)).toInt())
                {
                    returnTime(timeElapsed, NORECORD);
                    returnTime(settings.value("TableDe"+QString::number(multiple)).toInt(), RECORD);
                    QMessageBox::information(this, tr("Temps de réponses"), tr("Tu as mis ")+QString::number(timeTab[1])+tr(" minute(s) et ")+QString::number(timeTab[0])+tr(" secondes.<br /><strong>C'est un nouveau record ! Félicitation !</strong><br />L'ancien record était de ")+QString::number(timeTab[3])+tr(" minute(s) et ")+QString::number(timeTab[2])+tr(" secondes."));
                    settings.setValue("TableDe"+QString::number(multiple), timeElapsed);
                    settings.endGroup();
                }
                else
                {
                    returnTime(timeElapsed, NORECORD);
                    QMessageBox::information(this, tr("Temps de réponses"), tr("Tu as mis ")+QString::number(timeTab[1])+tr(" minute(s) et ")+QString::number(timeTab[0])+tr(" secondes."));
                }
            }
        }
        else
        {
            returnTime(timeElapsed, NORECORD);
            QMessageBox::information(this, tr("Temps de réponses"), tr("Tu as mis ")+QString::number(timeTab[1])+tr(" minute(s) et ")+QString::number(timeTab[0])+tr(" secondes.<br />Ce temps ne compte pas pour les records car tu as fait des fautes !"));
        }
    }

    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
}
Fen_correction::Fen_correction(SpinBox *reponses[], int *multipleOrder, int *order, int time)
{
    if(time != 0)
        timeElapsed = time;

    this->setWindowTitle(tr("Correction"));

    note = 10;

    tab = order;

    orderTab = multipleOrder;

    for(int i = 0; i < 10; i++)
        reponse[i] = reponses[i]->value();

    setWindowLayout(orderTab);

    if(time != 0)
    {
        if(note == 10)
        {
            QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Multifacile", QString(), this);
            if(!settings.contains("HardMode"))
            {
                settings.setValue("HardMode", timeElapsed);
                returnTime(timeElapsed, NORECORD);
                QMessageBox::information(this, tr("Temps de réponses"), tr("Tu as mis ")+QString::number(timeTab[1])+tr(" minute(s) et ")+QString::number(timeTab[0])+tr(" secondes."));
            }

            else
            {
                if(1000 < settings.value("HardMode").toInt())
                    settings.setValue("HardMode", (settings.value("HardMode").toInt()/1000));
                if(timeElapsed < settings.value("HardMode").toInt())
                {
                    returnTime(timeElapsed, NORECORD);
                    returnTime(settings.value("HardMode").toInt(), RECORD);
                    QMessageBox::information(this, tr("Temps de réponses"), tr("Tu as mis ")+QString::number(timeTab[1])+tr(" minute(s) et ")+QString::number(timeTab[0])+tr(" secondes.<br /><strong>C'est un nouveau record ! Félicitation !</strong><br />L'ancien record était de ")+QString::number(timeTab[3])+tr(" minute(s) et ")+QString::number(timeTab[2])+tr(" secondes."));
                    settings.setValue("HardMode", timeElapsed);
                }
                else
                {
                    returnTime(timeElapsed, NORECORD);
                    QMessageBox::information(this, tr("Temps de réponses"), tr("Tu as mis ")+QString::number(timeTab[1])+tr(" minute(s) et ")+QString::number(timeTab[0])+tr(" secondes."));
                }
            }
        }
        else
        {
            returnTime(timeElapsed, NORECORD);
            QMessageBox::information(this, tr("Temps de réponses"), tr("Tu as mis ")+QString::number(timeTab[1])+tr(" minute(s) et ")+QString::number(timeTab[0])+tr(" secondes.<br />Ce temps ne compte pas pour les records car tu as fait des fautes !"));
        }
    }

    this->setLayout(vlayout);

    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

}
void Fen_correction::setWindowLayout(int multiple)
{
    for(int i = 0; i < 10; i++)
    {
        multiplication[i] = new QLabel();
        multiplication[i]->setText(QString::number(multiple)+ " x " + QString::number(tab[i]) + " = "+QString::number(reponse[i]));
    }

    notation(multiple);

    texte = new QLabel(tr("<h3><strong>Voici la correction : </strong></h3>"));
    if(note >= 7)
    {
        total = new QLabel(tr("Tu as eu <strong><span style=\"color: green;\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal = new QLabel();
        if(note == 10)
            pngTotal->setPixmap(QPixmap("excellent.png"));
        else
            pngTotal->setPixmap(QPixmap("bien.png"));
    }
    else if(note <= 2)
    {
        total = new QLabel(tr("Tu as eu <strong><span style=\"color: red;\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal = new QLabel();
        pngTotal->setPixmap(QPixmap("mauvais.png"));
    }
    else
    {
        total = new QLabel(tr("Ta as eu <strong><span style=\"color: orange;\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal =  new QLabel();
        pngTotal->setPixmap(QPixmap("moyen.png"));
    }

    layout = new QGridLayout();

    vlayout = new QVBoxLayout(this);

    hlayout[0] = new QHBoxLayout();
    hlayout[1] = new QHBoxLayout();
    hlayout[2] = new QHBoxLayout();

    quit = new QPushButton(tr("Fermer"));

    layout->addWidget(multiplication[0], 1, 0);
    layout->addWidget(correction[0][0], 1, 1);
    layout->addWidget(correction[1][0], 1, 2);

    layout->addWidget(multiplication[1], 2, 0);
    layout->addWidget(correction[0][1], 2, 1);
    layout->addWidget(correction[1][1], 2, 2);


    layout->addWidget(multiplication[2], 3, 0);
    layout->addWidget(correction[0][2], 3, 1);
    layout->addWidget(correction[1][2], 3, 2);


    layout->addWidget(multiplication[3], 4, 0);
    layout->addWidget(correction[0][3], 4, 1);
    layout->addWidget(correction[1][3], 4, 2);


    layout->addWidget(multiplication[4], 5, 0);
    layout->addWidget(correction[0][4], 5, 1);
    layout->addWidget(correction[1][4], 5, 2);


    layout->addWidget(multiplication[5], 6, 0);
    layout->addWidget(correction[0][5], 6, 1);
    layout->addWidget(correction[1][5], 6, 2);


    layout->addWidget(multiplication[6], 7, 0);
    layout->addWidget(correction[0][6], 7, 1);
    layout->addWidget(correction[1][6], 7, 2);


    layout->addWidget(multiplication[7], 8, 0);
    layout->addWidget(correction[0][7], 8, 1);
    layout->addWidget(correction[1][7], 8, 2);


    layout->addWidget(multiplication[8], 9, 0);
    layout->addWidget(correction[0][8], 9, 1);
    layout->addWidget(correction[1][8], 9, 2);


    layout->addWidget(multiplication[9], 10, 0);
    layout->addWidget(correction[0][9], 10, 1);
    layout->addWidget(correction[1][9], 10, 2);


    hlayout[0]->setAlignment(Qt::AlignCenter);
    hlayout[0]->addWidget(texte);

    hlayout[1]->setAlignment(Qt::AlignCenter);
    hlayout[1]->addWidget(total);
    hlayout[1]->addWidget(pngTotal);

    hlayout[2]->setAlignment(Qt::AlignRight);
    hlayout[2]->addWidget(quit);

    vlayout->addLayout(hlayout[0]);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout[1]);
    vlayout->addLayout(hlayout[2]);

}
void Fen_correction::setWindowLayout(int tabOrder[])
{
    for(int i = 0; i < 10; i++)
    {
        multiplication[i] = new QLabel();
        multiplication[i]->setText(QString::number(tabOrder[i])+ " x " + QString::number(tab[i]) + " = "+QString::number(reponse[i]));
    }

    notation(tabOrder);

    texte = new QLabel(tr("<h3><strong>Voici la correction : </strong></h3>"));
    if(note >= 7)
    {
        total = new QLabel(tr("Tu as eu <strong><span style=\"color: green;\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal = new QLabel();
        if(note == 10)
            pngTotal->setPixmap(QPixmap("excellent.png"));
        else
            pngTotal->setPixmap(QPixmap("bien.png"));
    }
    else if(note <= 2)
    {
        total = new QLabel(tr("Tu as eu <strong><span style=\"color: red;\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal = new QLabel();
        pngTotal->setPixmap(QPixmap("mauvais.png"));
    }
    else
    {
        total = new QLabel(tr("Tu as eu <strong><span style=\"color: orange;\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal =  new QLabel();
        pngTotal->setPixmap(QPixmap("moyen.png"));
    }

    layout = new QGridLayout();

    vlayout = new QVBoxLayout(this);

    hlayout[0] = new QHBoxLayout();
    hlayout[1] = new QHBoxLayout();
    hlayout[2] = new QHBoxLayout();

    quit = new QPushButton("Fermer");

    layout->addWidget(multiplication[0], 1, 0);
    layout->addWidget(correction[0][0], 1, 1);
    layout->addWidget(correction[1][0], 1, 2);

    layout->addWidget(multiplication[1], 2, 0);
    layout->addWidget(correction[0][1], 2, 1);
    layout->addWidget(correction[1][1], 2, 2);


    layout->addWidget(multiplication[2], 3, 0);
    layout->addWidget(correction[0][2], 3, 1);
    layout->addWidget(correction[1][2], 3, 2);


    layout->addWidget(multiplication[3], 4, 0);
    layout->addWidget(correction[0][3], 4, 1);
    layout->addWidget(correction[1][3], 4, 2);


    layout->addWidget(multiplication[4], 5, 0);
    layout->addWidget(correction[0][4], 5, 1);
    layout->addWidget(correction[1][4], 5, 2);


    layout->addWidget(multiplication[5], 6, 0);
    layout->addWidget(correction[0][5], 6, 1);
    layout->addWidget(correction[1][5], 6, 2);


    layout->addWidget(multiplication[6], 7, 0);
    layout->addWidget(correction[0][6], 7, 1);
    layout->addWidget(correction[1][6], 7, 2);


    layout->addWidget(multiplication[7], 8, 0);
    layout->addWidget(correction[0][7], 8, 1);
    layout->addWidget(correction[1][7], 8, 2);


    layout->addWidget(multiplication[8], 9, 0);
    layout->addWidget(correction[0][8], 9, 1);
    layout->addWidget(correction[1][8], 9, 2);


    layout->addWidget(multiplication[9], 10, 0);
    layout->addWidget(correction[0][9], 10, 1);
    layout->addWidget(correction[1][9], 10, 2);


    hlayout[0]->setAlignment(Qt::AlignCenter);
    hlayout[0]->addWidget(texte);

    hlayout[1]->setAlignment(Qt::AlignCenter);
    hlayout[1]->addWidget(total);
    hlayout[1]->addWidget(pngTotal);

    hlayout[2]->setAlignment(Qt::AlignRight);
    hlayout[2]->addWidget(quit);

    vlayout->addLayout(hlayout[0]);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout[1]);
    vlayout->addLayout(hlayout[2]);

}

void Fen_correction::notation(const int m_multiple)
{
    for(int i = 0; i < 10; i++)
    {
        resultat[i] = m_multiple*tab[i];
    }

    for(int i = 0; i < 10; i++)
    {
        correction[0][i] = new QLabel;
        correction[1][i] = new QLabel;
        if(reponse[i] == resultat[i])
        {
            correction[0][i]->setPixmap(QPixmap("ok.png"));
            correction[1][i]->setText(tr("<span style=\"color: green;\">C'est correct !</style>"));
        }
        else
        {
            note--;
            correction[0][i]->setPixmap(QPixmap("faux.png"));
           correction[1][i]->setText(tr("<span style=\"color: red;\">La bonne réponse était ")+QString::number(resultat[i])+"</style>");
        }
    }

}
void Fen_correction::notation(int *m_multiple)
{
    int *multiple = m_multiple;
    for(int i = 0; i < 10; i++)
    {
        resultat[i] = multiple[i]*tab[i];
    }

    for(int i = 0; i < 10; i++)
    {
        correction[0][i] = new QLabel;
        correction[1][i] = new QLabel;
        if(reponse[i] == resultat[i])
        {
            correction[0][i]->setPixmap(QPixmap("ok.png"));
            correction[1][i]->setText(tr("<span style=\"color: green;\">C'est correct !</style>"));
        }
        else
        {
            note--;
            correction[0][i]->setPixmap(QPixmap("faux.png"));
           correction[1][i]->setText(tr("<span style=\"color: red;\">La bonne réponse était ")+QString::number(resultat[i])+"</style>");
        }
    }
}
void Fen_correction::returnTime(const int sec, RecordState state)
{
    if(state == NORECORD)
    {
        timeTab[0] = sec;
        timeTab[1] = timeTab[0]/60;
        if(timeTab[1] != 0)
            timeTab[0] %= 60;
    }
    else if(state == RECORD)
    {
        timeTab[2] = sec;
        timeTab[3] = timeTab[2]/60;
        if(timeTab[3] != 0)
            timeTab[2] %= 60;
    }
}
Fen_correction::~Fen_correction()
{
    delete total;
    delete layout;
    delete vlayout;
    delete quit;
    delete texte;
    delete pngTotal;

    total = 0;
    layout = 0;
    vlayout = 0;
    quit = 0;
    texte = 0;

    for (int i = 0; i < 10; i++)
    {
        delete multiplication[i];
        multiplication[i] = 0;
    }
    for (int i = 0; i < 3; i++)
    {
        delete hlayout[i];
        hlayout[i] = 0;
    }
    for (int i = 0; i < 2; i++)
    {
        for ( int j = 0; j < 10; j++)
        {
            delete correction[i][j];
            correction[i][j] = 0;
        }
    }
}
