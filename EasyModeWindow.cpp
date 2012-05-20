#include "EasyModeWindow.h"

EasyModeWindow::EasyModeWindow(const int m_multiplicateur, bool shuffleNeeded)
{
    Shuffle shuffle(shuffleNeeded);
    shuffle.getNumbers(array);
    m_multiple = m_multiplicateur;

    this->setWindowTitle("Table de "+QString::number(m_multiple));

    corriger = new QPushButton("Corriger");
    melanger = new QPushButton("Mélanger");

    hlayout = new QHBoxLayout;

    hlayout->addWidget(corriger);
    hlayout->addWidget(melanger);


    for(int i = 0; i < 10; i++)
    {
        reponses[i] = new SpinBox();
        reponses[i]->setMaximum(2147483647);
        reponses[i]->setMinimum(-2147483647);
        reponses[i]->setValue(0);
        reponses[i]->setNumero(i);
        if(i == 0)
        {
            reponses[i]->setFocus();
            reponses[i]->selectAll();
        }
    }

    for(int i = 0; i < 10; i++)
        label[i] = new QLabel(QString::number(m_multiple)+" x "+QString::number(array[i]));

    layout = new QFormLayout();

    for(int i = 0; i < 10; i++)
        layout->addRow(label[i], reponses[i]);

    vlayout = new QVBoxLayout();
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout);


    this->setLayout(vlayout);

    connect(corriger, SIGNAL(clicked()), this, SLOT(open()));
    connect(melanger, SIGNAL(clicked()), this, SLOT(Melange()));

    for(int i = 0; i < 10; i++)
        connect(reponses[i], SIGNAL(enterKeyPressed(int)), this, SLOT(newSetFocus(int)));
}
void EasyModeWindow::Melange()
{
    Shuffle shuffle(true);
    shuffle.getNumbers(array);
    for(int i = 0; i < 10; i++)
        label[i]->setText(QString::number(m_multiple)+" x "+QString::number(array[i]));
    reponses[0]->setFocus();
    reponses[0]->selectAll();
}
EasyModeWindow::~EasyModeWindow()
{
    delete melanger;
    melanger = 0;
}
