#include "fen_secondaire.h"
#include "fen_correction.h"

Fen_secondaire::Fen_secondaire(const int multiplicateur, bool shuffle)
{
    m_multiplicateur = multiplicateur;

    Shuffle tab(shuffle);

    tab.getNumbers(array);

    this->setWindowTitle("Table de "+QString::number(m_multiplicateur));

    corriger = new QPushButton("corriger");
    melanger = new QPushButton("Mélanger");

    hlayout = new QHBoxLayout;

    hlayout->addWidget(melanger);
    hlayout->addWidget(corriger);

    for(int i = 0; i < 10; i++)
    {
        reponses[i] = new QSpinBox;
        reponses[i]->setMaximum(2147483647);
        reponses[i]->setMinimum(-2147483647);
        reponses[i]->setValue(0);
    }

    for(int i = 0; i < 10; i++)
        label[i] = new QLabel(QString::number(m_multiplicateur)+" x "+QString::number(array[i]));

    layout = new QFormLayout();

    for(int i = 0; i < 10; i++)
        layout->addRow(label[i], reponses[i]);

    vlayout = new QVBoxLayout();
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout);


    this->setLayout(vlayout);

    connect(corriger, SIGNAL(clicked()), this, SLOT(open()));
    connect(melanger, SIGNAL(clicked()), this, SLOT(Melange()));
}

void Fen_secondaire::open()
{
    fen = new Fen_correction(m_multiplicateur, reponses, array);
    fen->resize(200, 200);
    fen->show();
    this->close();
}
Fen_secondaire::~Fen_secondaire()
{
    delete corriger;
    delete layout;
    delete vlayout;

    corriger = 0;
    layout = 0;
    vlayout = 0;

    for(int i = 0; i < 10; i++)
    {
        delete reponses[i];
        reponses[i] = 0;
    }
}
void Fen_secondaire::Melange()
{
    Shuffle shuffle(true);
    shuffle.getNumbers(array);
    for(int i = 0; i < 10; i++)
        label[i]->setText(QString::number(m_multiplicateur)+" x "+QString::number(array[i]));
}
