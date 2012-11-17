#include "MediumModeWindow.h"
#include "fen_correction.h"

MediumModeWindow::MediumModeWindow()
{
}

MediumModeWindow::MediumModeWindow(const int multiplicateur, bool chrono)
{
    time = chrono;
    m_multiple = multiplicateur;

    Shuffle shuffle(true);
    shuffle.getNumbers(array);

    this->setWindowTitle(tr("Table de ")+QString::number(m_multiple));

    corriger = new QPushButton(tr("Corriger"));

    hlayoutBottom = new QHBoxLayout;

    if(time)
    {
        text = new QLabel(tr("Temps :"));
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

    hlayoutBottom->addWidget(corriger);

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

    for(int i = 0; i < 10; i++)
        connect(reponses[i], SIGNAL(enterKeyPressed(int)), this, SLOT(newSetFocus(int)));
}

void MediumModeWindow::open()
{
    if(time)
    {
        chronometre->stop();
        fen = new Fen_correction(m_multiple, reponses, array, secondes, MEDIUM);
    }
    else if(!time)
        fen = new Fen_correction(m_multiple, reponses, array);
    fen->resize(200, 200);
    fen->show();
    this->close();
}
void MediumModeWindow::newSetFocus(const int number)
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
void MediumModeWindow::startTime()
{
    chronometre = new QTimer;
    chronometre->start(1000);
    secondes = 0;
    connect(chronometre, SIGNAL(timeout()), this, SLOT(newSecond()));
    connect(this, SIGNAL(addSeconde(int)), this, SLOT(updateLabel(int)));
}
void MediumModeWindow::closeEvent(QCloseEvent *event)
{
    if(time && event->spontaneous())
        delete chronometre;
    event->accept();
}
void MediumModeWindow::newSecond()
{
    secondes++;
    emit addSeconde(secondes);
}
void MediumModeWindow::updateLabel(const int temps) const
{
    if((temps/60) != 0)
    {
        minute->setText("0"+QString::number(temps/60));
        if((temps%60) < 10)
            seconde->setText("0"+QString::number(temps%60));
        else
            seconde->setText(QString::number(temps%60));
    }
    else
    {
        if(temps < 10)
            seconde->setText("0"+QString::number(temps));
        else
            seconde->setText(QString::number(temps));
    }
}

MediumModeWindow::~MediumModeWindow()
{
    delete corriger;
    delete layout;
    delete vlayout;

    corriger = nullptr;
    layout = nullptr;
    vlayout = nullptr;

    for(int i = 0; i < 10; i++)
    {
        delete reponses[i];
        reponses[i] = nullptr;
    }

    if(time)
        chronometre = nullptr;
}
