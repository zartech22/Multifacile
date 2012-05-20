#include "MediumModeWindow.h"
#include "fen_correction.h"

MediumModeWindow::MediumModeWindow()
{
}

MediumModeWindow::MediumModeWindow(const int multiplicateur)
{
    m_multiple = multiplicateur;

    Shuffle shuffle(true);
    shuffle.getNumbers(array);

    this->setWindowTitle("Table de "+QString::number(m_multiple));

    corriger = new QPushButton("Corriger");

    hlayout = new QHBoxLayout;

    hlayout->addWidget(corriger);

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

    for(int i = 0; i < 10; i++)
        connect(reponses[i], SIGNAL(enterKeyPressed(int)), this, SLOT(newSetFocus(int)));
}

void MediumModeWindow::open()
{
    fen = new Fen_correction(m_multiple, reponses, array);
    fen->resize(200, 200);
    fen->show();
    this->close();
}
void MediumModeWindow::newSetFocus(int number)
{
    if(number < 9)
    {
        int num = number+1;
        reponses[num]->setFocus();
        reponses[num]->selectAll();
    }
    else
        open();
}

MediumModeWindow::~MediumModeWindow()
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
