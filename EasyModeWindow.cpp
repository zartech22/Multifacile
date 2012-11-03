#include "EasyModeWindow.h"

EasyModeWindow::EasyModeWindow(const int m_multiplicateur, bool shuffleNeeded, bool chrono)
{
    time = chrono;

    Shuffle shuffle(shuffleNeeded);
    shuffle.getNumbers(array);
    m_multiple = m_multiplicateur;

    this->setWindowTitle(tr("Table de ")+QString::number(m_multiple));

    corriger = new QPushButton(tr("Corriger"));
    astuces = new QPushButton(tr("Astuce"));

    hlayoutBottom = new QHBoxLayout;

    hlayoutBottom->addWidget(astuces);
    hlayoutBottom->addWidget(corriger);

    if(time)
    {
        text = new QLabel(tr("Temps : "));
        minute = new QLabel("00");
        deuxPoint = new QLabel(":");
        seconde = new QLabel("00");

        hlayoutTop = new QHBoxLayout;
        hlayoutTop->setAlignment(Qt::AlignCenter);
        hlayoutTop->addWidget(text);
        hlayoutTop->addWidget(minute);
        hlayoutTop->addWidget(deuxPoint);
        hlayoutTop->addWidget(seconde);
    }


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
    if(time)
        vlayout->addLayout(hlayoutTop);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayoutBottom);


    this->setLayout(vlayout);

    if(time)
        startTime();

    connect(corriger, SIGNAL(clicked()), this, SLOT(open()));
    connect(astuces, SIGNAL(clicked()), this, SLOT(openAstuce()));

    for(int i = 0; i < 10; i++)
        connect(reponses[i], SIGNAL(enterKeyPressed(int)), this, SLOT(newSetFocus(int)));
}
void EasyModeWindow::openAstuce()
{
    AstuceWindow astuce(m_multiple);
    astuce.exec();
}
void EasyModeWindow::open()
{
    if(time)
    {
        chronometre->stop();
        fen = new Fen_correction(m_multiple, reponses, array, secondes, EASY);
    }
    else if(!time)
        fen = new Fen_correction(m_multiple, reponses, array);
    fen->resize(200, 200);
    fen->show();
    this->close();
}

EasyModeWindow::~EasyModeWindow()
{
    delete astuces;
    astuces = nullptr;
}
