#include "fen_correction.h"
//#include "fen_secondaire.h"
#include "fenetre_principale.h"

Fen_correction::Fen_correction(const int multiple, SpinBox *reponses[], int *order)
{
    this->setWindowTitle("Correction");
    m_multiple = multiple;
    note = 10;

    tab = order;

    for(int i = 0; i < 10; i++)
    {
        reponse[i] = reponses[i]->value();
    }
    for(int i = 0; i < 10; i++)
    {
        multiplication[i] = new QLabel();
        multiplication[i]->setText(QString::number(m_multiple)+ " x " + QString::number(tab[i]) + " = "+QString::number(reponse[i]));
    }

    notation();

    texte = new QLabel("<h3><strong>Voici la correction : </strong></h3>");
    if(note >= 7)
        total = new QLabel("Vous avez eu <strong><span style=\"color: green;\">"+QString::number(note)+"/10</span></strong>");
    else if(note <= 2)
        total = new QLabel("Vous avez eu <strong><span style=\"color: red;\">"+QString::number(note)+"/10</span></strong>");
    else
        total = new QLabel("Vous avez eu <strong><span style=\"color: orange;\">"+QString::number(note)+"/10</span></strong>");

    layout = new QGridLayout();

    vlayout = new QVBoxLayout(this);

    hlayout[0] = new QHBoxLayout();
    hlayout[1] = new QHBoxLayout();
    hlayout[2] = new QHBoxLayout();

    quit = new QPushButton("Fermer");

    layout->addWidget(multiplication[0], 1, 0);
    layout->addWidget(correction[0], 1, 1);

    layout->addWidget(multiplication[1], 2, 0);
    layout->addWidget(correction[1], 2, 1);

    layout->addWidget(multiplication[2], 3, 0);
    layout->addWidget(correction[2], 3, 1);

    layout->addWidget(multiplication[3], 4, 0);
    layout->addWidget(correction[3], 4, 1);

    layout->addWidget(multiplication[4], 5, 0);
    layout->addWidget(correction[4], 5, 1);

    layout->addWidget(multiplication[5], 6, 0);
    layout->addWidget(correction[5], 6, 1);

    layout->addWidget(multiplication[6], 7, 0);
    layout->addWidget(correction[6], 7, 1);

    layout->addWidget(multiplication[7], 8, 0);
    layout->addWidget(correction[7], 8, 1);

    layout->addWidget(multiplication[8], 9, 0);
    layout->addWidget(correction[8], 9, 1);

    layout->addWidget(multiplication[9], 10, 0);
    layout->addWidget(correction[9], 10, 1);

    hlayout[0]->setAlignment(Qt::AlignCenter);
    hlayout[0]->addWidget(texte);

    hlayout[1]->setAlignment(Qt::AlignCenter);
    hlayout[1]->addWidget(total);

    hlayout[2]->setAlignment(Qt::AlignRight);
    hlayout[2]->addWidget(quit);

    vlayout->addLayout(hlayout[0]);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout[1]);
    vlayout->addLayout(hlayout[2]);

    this->setLayout(vlayout);

    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
}
void Fen_correction::notation()
{
    for(int i = 0; i < 10; i++)
    {
        resultat[i] = m_multiple*tab[i];
    }

    for(int i = 0; i < 10; i++)
    {
        correction[i] = new QLabel;
        if(reponse[i] == resultat[i])
        {
            correction[i]->setText("<span style=\"color: green;\">C'est correct !</style>");
            //correction[i]->setPixmap(QPixmap("Desert.jpg"));
            /*if(correction[i]->pixmap() != 0)
                correction[i]->setText("il y a une image !");*/
        }
        else
        {
            note--;
            // correction[i]->setPixmap(QPixmap("faux.png"));
           correction[i]->setText("<span style=\"color: red;\">La bonne réponse était "+QString::number(resultat[i])+"</style>");
        }
    }

}
Fen_correction::~Fen_correction()
{
    delete total;
    delete layout;
    delete vlayout;
    delete quit;
    delete texte;

    total = 0;
    layout = 0;
    vlayout = 0;
    quit = 0;
    texte = 0;

    for (int i = 0; i < 3; i++)
    {
        delete hlayout[i];
        hlayout[i] = 0;
    }

    for(int i = 0; i < 10; i++)
    {
        delete multiplication[i];

        multiplication[i] = 0;
    }
}
