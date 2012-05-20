#include "HardModeWindow.h"

HardModeWindow::HardModeWindow()
{
    Shuffle shuffle(true);
    shuffle.getNumbers(array, multiple);
    this->setWindowTitle("Table de aléatoire");

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

    if(multiple[5] == array[5])
        qDebug("pas bon !");
    for(int i = 0; i < 10; i++)
        label[i] = new QLabel(QString::number(multiple[i])+" x "+QString::number(array[i]));

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
void HardModeWindow::open()
{
    fen = new Fen_correction(reponses, multiple, array);
    fen->resize(200, 200);
    fen->show();
    this->close();
}
