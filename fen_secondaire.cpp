#include "fen_secondaire.h"
#include "fen_correction.h"

Fen_secondaire::Fen_secondaire()
{

}
Fen_secondaire::Fen_secondaire(const int multiplicateur, bool shuffle)
{
    m_multiplicateur = multiplicateur;

    Shuffle tab(shuffle);

    tab.getNumbers(array);

    this->setWindowTitle("Table de "+QString::number(m_multiplicateur));

    corriger = new QPushButton("corriger");

    for(int i = 0; i < 10; i++)
    {
        reponses[i] = new QSpinBox;
        reponses[i]->setMaximum(10000);
        reponses[i]->setMinimum(0);
    }

    layout = new QFormLayout();

    layout->addRow(QString::number(m_multiplicateur)+" x "+QString::number(array[0]), reponses[0]);
    layout->addRow(QString::number(m_multiplicateur)+" x "+QString::number(array[1]), reponses[1]);
    layout->addRow(QString::number(m_multiplicateur)+" x "+QString::number(array[2]), reponses[2]);
    layout->addRow(QString::number(m_multiplicateur)+" x "+QString::number(array[3]), reponses[3]);
    layout->addRow(QString::number(m_multiplicateur)+" x "+QString::number(array[4]), reponses[4]);
    layout->addRow(QString::number(m_multiplicateur)+" x "+QString::number(array[5]), reponses[5]);
    layout->addRow(QString::number(m_multiplicateur)+" x "+QString::number(array[6]), reponses[6]);
    layout->addRow(QString::number(m_multiplicateur)+" x "+QString::number(array[7]), reponses[7]);
    layout->addRow(QString::number(m_multiplicateur)+" x "+QString::number(array[8]), reponses[8]);
    layout->addRow(QString::number(m_multiplicateur)+" x "+QString::number(array[9]), reponses[9]);


    vlayout = new QVBoxLayout();
    vlayout->addLayout(layout);
    vlayout->addWidget(corriger);


    this->setLayout(vlayout);

    connect(corriger, SIGNAL(clicked()), this, SLOT(open()));
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
