#include "Correction.h"

Correction::Correction(Mode mode, int multiple, int *order, int* userAnswers, int time)
{
    Multiple = multiple;
    orderTab = order;
    answers = userAnswers;
    difficultyMode = mode;
    seconds = time;
    isHardMode = false;
}
Correction::Correction(int *multiple, int *order, int *userAnswers, int time)
{
    multipleTab = multiple;
    orderTab = order;
    answers = userAnswers;
    seconds = time;
}
int Correction::getCorrection(QLabel *correction[][10])
{
    int resultat[10];
    note = 10;

    bool isCorrect[10];
    for(int i = 0; i < 10; i++)
        isCorrect[i] = true;

    this->notation(resultat, isCorrect);
    this->doCorrection(correction, resultat, isCorrect);

    if(seconds != 0)
        this->manageTime();

    return note;
}
void Correction::notation(int resultat[], bool isCorrect[])
{
    if(!isHardMode)
    {
        for(int i = 0; i < 10; i++)
        {
            resultat[i] = Multiple*orderTab[i];
            if(resultat[i] != answers[i])
            {
                isCorrect[i] = false;
                --note;
            }
        }
    }
    else
    {
        for(int i = 0; i < 10; i++)
        {
            resultat[i] = multipleTab[i]*orderTab[i];
            if(resultat[i] != answers[i])
            {
                isCorrect[i] = false;
                --note;
            }
        }
    }
}
void Correction::doCorrection(QLabel *correction[][10], int resultat[], bool isCorrect[])
{
    for(int i = 0; i < 10; i++)
    {
        if(isCorrect[i])
        {
            correction[0][i]->setPixmap(QPixmap("ok.png"));
            correction[1][i]->setText(tr("<span style=\"color: green;\">C'est correct !</style>"));
        }
        else
        {
            correction[0][i]->setPixmap(QPixmap("faux.png"));
            correction[1][i]->setText(tr("<span style=\"color: red;\">La bonne réponse était ")+QString::number(resultat[i])+"</style>");
        }
    }
}

void Correction::manageTime()
{
    manager = new TimeRecordMgr(QSettings::IniFormat, QSettings::UserScope, "Multifacile", seconds, this->getModeGroupName(), this->getModeKeyName());

    QObject::connect(manager, SIGNAL(isNewRecord(RecordState,int)), this, SLOT(isRecordValid(RecordState, int)));

    manager->CompareTime();
}
void Correction::isRecordValid(RecordState record, int lastRecordTime)
{
    if(record == RECORD && note == 10)
        emit newRecord(RECORD, lastRecordTime);
    else if(record == RECORD && note != 10)
        emit newRecord(UNVALIDRECORD, lastRecordTime);
    else
        emit newRecord(NORECORD, lastRecordTime);
}
void Correction::saveTime(){ manager->SaveRecordInFile(); }

QString Correction::getModeGroupName()
{
    if(difficultyMode == EASY)
        return QString("EasyMode");
    else if(difficultyMode == MEDIUM)
        return QString("MediumMode");
    else
        return QString("HardMode");
}
QString Correction::getModeKeyName()
{
    if(difficultyMode == EASY || difficultyMode == MEDIUM)
        return QString("TableDe"+QString::number(Multiple));
    else
        return QString();
}
Correction::~Correction()
{
    delete manager;

    manager = 0;
}
