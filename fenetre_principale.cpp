#include "fenetre_principale.h"
#include "bouton.h"
#include "fen_secondaire.h"
#include "CheckUpdate.h"

Fenetre_principale::Fenetre_principale()
{
    version = VERSION;
    userAction = false;

    widget = new QWidget();
    check = new CheckUpdate(this, version);

    texte = new QLabel("Choisissez la table que vous voulez travailler !");
    espace = new QLabel("<hr />");

    quit = new QPushButton("Quitter");
    custom = new QPushButton("Table personnalisée");

    QMenu *fichier = menuBar()->addMenu("&Fichier");
    QAction *actionQuitter = new QAction("&Quitter", this);
    fichier->addAction(actionQuitter);

    QMenu *outils = menuBar()->addMenu("&Outils");
    QAction *actionUpdate = new QAction("Vérifiez les mise à jours", this);
    outils->addAction(actionUpdate);

    bouton1 = new Bouton("Table de 1", 1);
    bouton2 = new Bouton("Table de 2 ", 2);
    bouton3 = new Bouton("Table de 3 ", 3);
    bouton4 = new Bouton("Table de 4 ", 4);
    bouton5 = new Bouton("Table de 5 ", 5);
    bouton6 = new Bouton("Table de 6 ", 6);
    bouton7 = new Bouton("Table de 7 ", 7);
    bouton8 = new Bouton("Table de 8 ", 8);
    bouton9 = new Bouton("Table de 9 ", 9);
    bouton10 = new Bouton("Table de 10 ", 10);

    layout = new QGridLayout();
    glayout = new QGridLayout();
    vlayout = new QVBoxLayout();

    layout->addWidget(texte, 0, 0, 1, 2);

    layout->addWidget(bouton1, 1, 0);
    layout->addWidget(bouton2, 1, 1);
    layout->addWidget(bouton3, 2, 0);
    layout->addWidget(bouton4, 2, 1);
    layout->addWidget(bouton5, 3, 0);
    layout->addWidget(bouton6, 3, 1);
    layout->addWidget(bouton7, 4, 0);
    layout->addWidget(bouton8, 4, 1);
    layout->addWidget(bouton9, 5, 0);
    layout->addWidget(bouton10, 5, 1);

    glayout->addWidget(espace, 0, 1, 1, 2);
    glayout->addWidget(custom, 1, 1);
    glayout->addWidget(quit, 1, 2);

    vlayout->addLayout(layout);
    vlayout->addLayout(glayout);

    widget->setLayout(vlayout);
    this->setCentralWidget(widget);

    check->sendRequest();

    connect(bouton1, SIGNAL(clicked()), bouton1, SLOT(clique()));
    connect(bouton1, SIGNAL(cliquer(int)), this, SLOT(open_window(int)));

    connect(bouton2, SIGNAL(clicked()), bouton2, SLOT(clique()));
    connect(bouton2, SIGNAL(cliquer(int)), this, SLOT(open_window(int)));

    connect(bouton3, SIGNAL(clicked()), bouton3, SLOT(clique()));
    connect(bouton3, SIGNAL(cliquer(int)), this, SLOT(open_window(int)));

    connect(bouton4, SIGNAL(clicked()), bouton4, SLOT(clique()));
    connect(bouton4, SIGNAL(cliquer(int)), this, SLOT(open_window(int)));

    connect(bouton5, SIGNAL(clicked()), bouton5, SLOT(clique()));
    connect(bouton5, SIGNAL(cliquer(int)), this, SLOT(open_window(int)));

    connect(bouton6, SIGNAL(clicked()), bouton6, SLOT(clique()));
    connect(bouton6, SIGNAL(cliquer(int)), this, SLOT(open_window(int)));

    connect(bouton7, SIGNAL(clicked()), bouton7, SLOT(clique()));
    connect(bouton7, SIGNAL(cliquer(int)), this, SLOT(open_window(int)));

    connect(bouton8, SIGNAL(clicked()), bouton8, SLOT(clique()));
    connect(bouton8, SIGNAL(cliquer(int)), this, SLOT(open_window(int)));

    connect(bouton9, SIGNAL(clicked()), bouton9, SLOT(clique()));
    connect(bouton9, SIGNAL(cliquer(int)), this, SLOT(open_window(int)));

    connect(bouton10, SIGNAL(clicked()), bouton10, SLOT(clique()));
    connect(bouton10, SIGNAL(cliquer(int)), this, SLOT(open_window(int)));

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(custom, SIGNAL(clicked()), this, SLOT(open_window()));

    connect(check, SIGNAL(updateNeeded(bool)), this, SLOT(answer(bool)));

    connect(check, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionUpdate, SIGNAL(triggered()), this, SLOT(verification()));
}
void Fenetre_principale::open_window()
{
    bool ok = false;
    int nbr = QInputDialog::getInteger(this, "Choix de la table", "Indiquer la table sur laquelle vous voulez travailler", 0, -2147483647, 2147483647, 1, &ok);
    if(ok)
    {
        fen = new Fen_secondaire(nbr);
        fen->resize(300, 200);
        fen->show();
        //this->hide();
    }
}

void Fenetre_principale::open_window(int nbr)
{
    fen = new Fen_secondaire(nbr);
    fen->resize(300, 200);
    fen->show();
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
        check->disconnectFromHost();
        int userAnswer = QMessageBox::question(this, "Mise à jour disponible", "Une version plus récente de multifacile est disponible, voulez-vous la télécharger ?", QMessageBox::Yes | QMessageBox::No);
        if(userAnswer == QMessageBox::Yes)
        {
#ifdef WIN32
            ShellExecute(NULL, L"open", L"updater.exe", NULL, NULL, SW_SHOWNORMAL);
#endif
#ifdef LINUX
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
void Fenetre_principale::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur)
    {
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "Erreur", "<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "Erreur", "<em>ERREUR : le serveur a refusé la connexion. Vérifier si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::information(this, "Erreur", "<em>ERREUR : le serveur a coupé la connexion.</em>");
        break;
    default:
        QMessageBox::information(this, "Erreur", "<em>ERREUR : " + check->errorString() + "</em>.");
    }
}
void Fenetre_principale::verification()
{
    check->sendRequest();
    userAction = true;
}
