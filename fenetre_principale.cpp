#include "fenetre_principale.h"
#include "bouton.h"
#include "CheckUpdate.h"
#include "Shuffle.h"

Fenetre_principale::Fenetre_principale()
{
    userAction = false;
    mode = EASY;

    widget = new QWidget();

    check = new CheckUpdate(this, VERSION);


    texte = new QLabel("Choisis la table que tu veux travailler !");
    espace = new QLabel("<hr />");

    quit = new QPushButton("Quitter");
    customTable = new QPushButton("Table personnalisée");

    file = menuBar()->addMenu("&Fichier");
    tools = menuBar()->addMenu("&Outils");
    modes = menuBar()->addMenu("&Mode");
    actionGroup = new QActionGroup(this);

    quitAction = new QAction(QIcon("sortie.png"), "&Quitter", this);
    updateAction = new QAction(QIcon("update.png"), "Vérifier les mise à jours", this);
    chrono = new QAction("Table chronomètré", this);
    shuffleAction = new QAction("Table en désordre", this);
    easyMode = new QAction("Facile", this);
    mediumMode = new QAction("Moyen", this);
    hardMode = new QAction("Difficile", this);

    easyMode->setCheckable(true);
    mediumMode->setCheckable(true);
    hardMode->setCheckable(true);

    easyMode->setChecked(true);

    actionGroup->addAction(easyMode);
    actionGroup->addAction(mediumMode);
    actionGroup->addAction(hardMode);
    actionGroup->setExclusive(true);

    shuffleAction->setCheckable(true);
    chrono->setCheckable(true);

    file->addAction(quitAction);
    tools->addAction(updateAction);
    modes->addActions(actionGroup->actions());
    modes->addSeparator();
    modes->addAction(shuffleAction);
    modes->addAction(chrono);

    for(int i = 0; i < 10; i++)
        bouton[i] = new Bouton("Table de "+QString::number(i+1), i+1);

    layout = new QGridLayout();
    glayout = new QGridLayout();
    vlayout = new QVBoxLayout();

    layout->addWidget(texte, 0, 0, 1, 2);

    layout->addWidget(bouton[0], 1, 0);
    layout->addWidget(bouton[1], 1, 1);
    layout->addWidget(bouton[2], 2, 0);
    layout->addWidget(bouton[3], 2, 1);
    layout->addWidget(bouton[4], 3, 0);
    layout->addWidget(bouton[5], 3, 1);
    layout->addWidget(bouton[6], 4, 0);
    layout->addWidget(bouton[7], 4, 1);
    layout->addWidget(bouton[8], 5, 0);
    layout->addWidget(bouton[9], 5, 1);

    glayout->addWidget(espace, 0, 1, 1, 2);
    glayout->addWidget(customTable, 1, 1);
    glayout->addWidget(quit, 1, 2);

    vlayout->addLayout(layout);
    vlayout->addLayout(glayout);

    widget->setLayout(vlayout);
    this->setCentralWidget(widget);

    check->tryConnection();

    for(int i = 0; i < 10; i++)
    {
        connect(bouton[i], SIGNAL(clicked()), bouton[i], SLOT(clique()));
        connect(bouton[i], SIGNAL(cliquer(int)), this, SLOT(open_window(int)));
    }

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(customTable, SIGNAL(clicked()), this, SLOT(open_window()));

    connect(check, SIGNAL(updateNeeded(bool)), this, SLOT(answer(bool)));
    connect(check, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket()));

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(updateAction, SIGNAL(triggered()), this, SLOT(verification()));
    connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(setMode(QAction*)));
    connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(resetLabel(QAction*)));
}
void Fenetre_principale::open_window()
{
    bool ok = false;
    int nbr = QInputDialog::getInteger(this, "Choix de la table", "Indiquer la table sur laquelle vous voulez travailler", 0, -2147483647, 2147483647, 1, &ok);
    if(ok)
    {
        if(mode == EASY)
        {
            fen = new EasyModeWindow(nbr, shuffleAction->isChecked(), chrono->isChecked());
            fen->resize(300, 200);
            fen->show();
            fenList.append(fen);
        }
        else if(mode == MEDIUM)
        {
            fen = new MediumModeWindow(nbr, chrono->isChecked());
            fen->resize(300, 200);
            fen->show();
            fenList.append(fen);
        }
        else if(mode == HARD)
        {
            fen = new HardModeWindow(chrono->isChecked());
            fen->resize(300, 200);
            fen->show();
            fenList.append(fen);
        }
    }
}

void Fenetre_principale::open_window(int nbr)
{
    if(mode == EASY)
    {
        fen = new EasyModeWindow(nbr, shuffleAction->isChecked(), chrono->isChecked());
        fen->resize(300, 200);
        fen->show();
        fenList.append(fen);
    }
    else if(mode == MEDIUM)
    {
        fen = new MediumModeWindow(nbr, chrono->isChecked());
        fen->resize(300, 200);
        fen->show();
        fenList.append(fen);
    }
    else if(mode == HARD)
    {
        fen = new HardModeWindow(chrono->isChecked());
        fen->resize(300, 200);
        fen->show();
        fenList.append(fen);
    }
}
void Fenetre_principale::answer(bool update)
{
    if(!update)
    {
        if(userAction)
        {
            QMessageBox::information(this, "Vérification de mise à jour", "Il n'y a pour le moment aucune mise à jour disponible.");
            userAction = false;
        }
        check->disconnectFromHost();
        return;
    }
    else if(update)
    {
        if(userAction)
            userAction = false;
        check->disconnectFromHost();
        int userAnswer = QMessageBox::question(this, "Mise à jour disponible", "Une version plus récente de multifacile est disponible, veux-tu la télécharger ?", QMessageBox::Yes | QMessageBox::No);
        if(userAnswer == QMessageBox::Yes)
        {
#ifdef Q_OS_WIN32
            ShellExecute(NULL, L"open", L"updater.exe", NULL, NULL, SW_SHOWNORMAL);
#endif
#ifdef Q_OS_LINUX
            QProcess::startDetached("updater.exe");
#endif
            this->close();
        }
        else if(userAnswer == QMessageBox::No)
            return;
        else
            return;
    }
}
void Fenetre_principale::setMode(QAction *action)
{
    if(action == easyMode)
    {
        mode = EASY;
        if(!shuffleAction->isEnabled())
        {
            shuffleAction->setEnabled(true);
            shuffleAction->setChecked(false);
        }
    }
    else if(action == mediumMode)
    {
        mode = MEDIUM;
        shuffleAction->setChecked(true);
        shuffleAction->setDisabled(true);
    }
    else if(action == hardMode)
    {
        mode = HARD;
        shuffleAction->setChecked(true);
        shuffleAction->setDisabled(true);
    }
}
void Fenetre_principale::resetLabel(QAction *action)
{
    if(action == easyMode || action == mediumMode)
        for(int i = 0; i < 10; i++)
            bouton[i]->setText("Table de "+QString::number(i+1));
    else if(action == hardMode)
        for(int i = 0; i < 10; i++)
            bouton[i]->setText("Table aléatoire");
}

void Fenetre_principale::erreurSocket()
{
    QMessageBox::information(this, "Erreur de connexion", "Impossible de vérifier les mise à jour");
}
void Fenetre_principale::verification()
{
    check->tryConnection();
    userAction = true;
}
void Fenetre_principale::closeEvent(QCloseEvent *event)
{
    qApp->quit();
    event->accept();
}
Fenetre_principale::~Fenetre_principale()
{
    delete file, tools, modes;
    delete quitAction, updateAction, shuffleAction, chrono, easyMode, mediumMode, hardMode;
    delete actionGroup;
    delete quit, customTable;
    delete layout, glayout, vlayout;
    delete check;
    delete widget;


    for(int i = 0; i < fenList.size(); i++)
    {
        delete fenList[i];
        fenList[i] = 0;
    }

    file =0;
    tools = 0;
    modes = 0;
    quitAction = 0;
    updateAction = 0;
    shuffleAction = 0;
    chrono = 0;
    easyMode = 0;
    mediumMode = 0;
    hardMode = 0;
    actionGroup = 0;
    quit = 0;
    customTable = 0;
    layout = 0;
    glayout = 0;
    vlayout = 0;
    check = 0;
    widget = 0;
}
