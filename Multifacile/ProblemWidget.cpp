#include "ProblemWidget.h"

bool ProblemWidget::bddIsCreated = false;

ProblemWidget::ProblemWidget() : QWidget()
{
    if(!ProblemWidget::bddIsCreated)
    {
        bdd = QSqlDatabase::addDatabase("QSQLITE");
        bdd.setDatabaseName("problems.db");
        bdd.open();

        ProblemWidget::bddIsCreated = true;
    }

    _tables = new QPushButton(tr("Tables"), this);
    _problems = new QPushButton(tr("Problèmes"), this);
    _chooseATable = new QPushButton(tr("Choisir une table"), this);
    _correction = new QPushButton(tr("Corriger"), this);
    _quit = new QPushButton(tr("Quitter"), this);
    _answer = new QLineEdit(this);
    _answer->setPlaceholderText(tr("Ta réponse"));
    _answer->setValidator(new QRegExpValidator(QRegExp("\\d{0,3}"), _answer));

    _tables->setFixedSize(256, 94);
    _problems->setFixedSize(256, 94);
    _chooseATable->setFixedSize(150, 40);
    _correction->setFixedSize(80, 40);
    _quit->setFixedSize(70, 40);
    _answer->setFixedSize(302, 69);

    _tables->move(68, 5);
    _problems->move(350, 5);
    _chooseATable->move(240, 480);
    _correction->move(400, 480);
    _quit->move(490, 480);
    _answer->move(200, 325);

    _tables->setStyleSheet("background-image: url(\":/image/Bouton_inacessible.png\")");
    _problems->setStyleSheet("background-image: url(\":/image/Bouton.png\")");
    _chooseATable->setObjectName("QuitButton");
    _correction->setObjectName("QuitButton");
    _quit->setObjectName("QuitButton");
    _answer->setAttribute(Qt::WA_TranslucentBackground);
    _answer->setStyleSheet("border-image: url(\":/image/TextBox.png\") 0, 0, 0, 0; \
                           border-radius: 4px; \
                           padding: 25px;");

    _text = new QLabel(tr("Vérifie que tu connais bien tes tables grâce aux problèmes !"), this);
    _text->setFixedSize(500, 200);
    _text->move(100, 105);

    showProblem(Shuffle::random(1, 10));

    connect(_tables, SIGNAL(clicked()), this, SIGNAL(goToTables()));
    connect(_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void ProblemWidget::showProblem(int table)
{
    QSqlQuery query("SELECT enonce FROM problems WHERE id = 1");
    query.next();

    qDebug() << "coucou";

    _text->setWordWrap(true);
    _text->setText(query.value(0).toString().replace("%d", QString::number(table)));

}
