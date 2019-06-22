#include "Updater.h"

Updater::Updater() : QProgressDialog(), lib(NETWORK)
{
    typedef Network* (*NetworkConstructor)();
    NetworkConstructor constructor = (NetworkConstructor) lib.resolve("getNetwork");
    if(constructor)
        net = constructor();

    downloadedFiles = 0;
    FilesMessageSize = 0;
    NamesMessageSize = 0;
    ToDoMessageSize = 0;
    FilesNumber = 0;
    downloaded = false;
    this->setLabelText("Téléchargement de la mise à  jour en cours...");
    this->setCancelButtonText("&Annuler");
    this->setAutoClose(false);
    this->setAutoReset(false);
    this->setWindowTitle("Updater");

    connect(net, SIGNAL(connected()), this, SLOT(setConnection()));
    connect(this, SIGNAL(canceled()), this, SLOT(stop()));
    net->tryConnection("multifacile.no-ip.org", 8090);

}
void Updater::ReceiveFilesData(QByteArray *array)
{

    QDataStream in(array, QIODevice::ReadOnly);

    in >> FilesNumber;

    for(int i = 0; i < FilesNumber; ++i)
    {
        QByteArray data;

        in >> fileSize;

        in >> data;

        QFile file(QString("TempFile%1.tmp").arg(i));
        file.open(QIODevice::WriteOnly);
        file.write(data);
        file.close();
    }
    sendRequest(NameQuery);

    delete array;
}
void Updater::ReceiveNamesData(QByteArray *array)
{
    QDataStream in(array, QIODevice::ReadOnly);

    in >> name;
    remplacement();
    sendRequest(ToDoQuery);

    delete array;
}

void Updater::ReceiveToDoData(QByteArray *array)
 {
    ToDo = QTextCodec::codecForMib(106)->toUnicode(*array);
    ToDoProcess();
    delete array;
}

void Updater::ToDoProcess()
{
    QStringList commandList(ToDo.split("\n", QString::SkipEmptyParts));


    if(!commandList.isEmpty())
    {
        for(int i = 0; i < commandList.size(); ++i)
        {
            QStringList argList(commandList.at(i).split(" ", QString::SkipEmptyParts));

            QDir dir;

            if(argList.at(0) == "mkdir")
                for(int mkDirIndex = 1; mkDirIndex < argList.size(); mkDirIndex++)
                {
                    QFileInfo dirInfo(argList.at(mkDirIndex));
                    dir.mkdir(QDir::toNativeSeparators(dirInfo.absoluteFilePath().simplified()));
                }
            else if(argList.at(0) == "rmdir")
                for(int rmDirIndex = 1; rmDirIndex < argList.size(); rmDirIndex++)
                {
                    QDir dirToRemove(argList.at(rmDirIndex).simplified());
                    QFileInfoList infoList(dirToRemove.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot));
                    for(int j = 0; j < infoList.size(); j++)
                        QFile::remove(argList.at(rmDirIndex).simplified()+"/"+infoList.at(j).fileName());
                    dir.rmdir(argList.at(rmDirIndex).simplified());
                }
            else if(argList.at(0) == "del")
                for(int delFileIndex = 1; delFileIndex < argList.size(); delFileIndex++)
                    QFile::remove(argList.at(delFileIndex).simplified());
            else if(argList.at(0) == "renameFile")
            {
                if(QFile::exists(argList.at(2).simplified()))
                    QFile::remove(argList.at(2).simplified());
                QFile::rename(argList.at(1).simplified(), argList.at(2).simplified());
            }
            else if(argList.at(0) == "renameDir")
                dir.rename(argList.at(1).simplified(), argList.at(2).simplified());
        }
    }
    finish();
}

void Updater::remplacement()
{
    for(int i = 0; i < FilesNumber; ++i)
    {
        QFile *file = new QFile(QString("TempFile%1.tmp").arg(i));
        files << file;
    }
    QStringList listeNames = name.split("\n", QString::SkipEmptyParts);
    for(int i = 0; i < FilesNumber; ++i)
    {
        if(QFile::exists(listeNames[i]))
            QFile::remove(listeNames[i]);
        QFile::rename(QString("TempFile%1.tmp").arg(i), listeNames[i]);
    }
}
void Updater::sendRequest(QueryState state)
{
    switch(state)
    {
    case FileQuery :
#ifdef Q_OS_LINUX
        request = "LinuxStartFile";
#endif
#ifdef Q_OS_WIN
        request = "WinStartFile";
#endif
        connect(net, SIGNAL(answer(QByteArray*)), this, SLOT(ReceiveFilesData(QByteArray*)));
        net->sendMsg(request, QUIntSize::QUInt64);
        break;

    case NameQuery :
        request = "StartNames";
        disconnect(net, SIGNAL(answer(QByteArray*)), this, SLOT(ReceiveFilesData(QByteArray*)));
        connect(net, SIGNAL(answer(QByteArray*)), this, SLOT(ReceiveNamesData(QByteArray*)));
        net->sendMsg(request);
        break;

    case ToDoQuery :
        request = "StartToDo";
        disconnect(net, SIGNAL(answer(QByteArray*)), this, SLOT(ReceiveNamesData(QByteArray*)));
        connect(net, SIGNAL(answer(QByteArray*)), this, SLOT(ReceiveToDoData(QByteArray*)));
        net->sendMsg(request);
        break;

    default :
        break;
    }
}
void Updater::finish()
{
#ifdef Q_OS_LINUX
    QFile::setPermissions("Multifacile", QFile::ExeOwner | QFile::ReadOwner | QFile::WriteOwner);
    QProcess::startDetached("Multifacile");
#elif defined(Q_OS_WIN)
   QProcess::startDetached("Multifacile.exe");
#endif
   this->close();
}
