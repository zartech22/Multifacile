#include "Updater.h"

Updater::Updater() : QProgressDialog(), downloadedFiles(0), FilesMessageSize(0), NamesMessageSize(0), ToDoMessageSize(0),
    FilesNumber(0), downloaded(false), net(getNetwork())
{
    this->setLabelText("Téléchargement de la mise à  jour en cours...");
    this->setCancelButtonText("&Annuler");
    this->setAutoClose(false);
    this->setAutoReset(false);
    this->setWindowTitle("Updater");

    connect(net, SIGNAL(connected()), this, SLOT(setConnection()));
    connect(this, SIGNAL(canceled()), this, SLOT(stop()));
    net->tryConnection(serverName, updatePort);

}
void Updater::ReceiveFilesData(QByteArray *array)
{
    QDataStream in(array, QIODevice::ReadOnly);
    QFile file;
    QByteArray data;

    in >> FilesNumber;

    for(quint16 i = 0; i < FilesNumber; ++i)
    {
        data.clear();

        in >> fileSize;

        in >> data;

        file.setFileName(QString("TempFile%1.tmp").arg(i));
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

    for(const QString &commandLine : commandList)
    {
        QStringList argList(commandLine.split(" ", QString::SkipEmptyParts));

        const QString &command = argList.first();
        argList.pop_front();

        QDir dir;

        if(command == "mkdir")
        {
            for(const QString &dirName : argList)
            {
                QFileInfo dirInfo(dirName);
                dir.mkdir(QDir::toNativeSeparators(dirInfo.absoluteFilePath().simplified()));
            }
        }
        else if(command == "rmdir")
        {
            for(const QString &dirName : argList)
            {
                const QString simplifiedDirName = dirName.simplified();

                QFileInfoList infoList(QDir(simplifiedDirName).entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot));

                for(const QFileInfo &file : infoList)
                    QFile::remove(simplifiedDirName + "/" + file.fileName());

                dir.rmdir(simplifiedDirName);
            }
        }
        else if(command == "del")
            for(const QString &file : argList)
                QFile::remove(file.simplified());
        else if(command == "renameFile")
        {
            if(QFile::exists(argList.at(1).simplified()))
                QFile::remove(argList.at(1).simplified());
            QFile::rename(argList.at(0).simplified(), argList.at(1).simplified());
        }
        else if(command == "renameDir")
            dir.rename(argList.at(0).simplified(), argList.at(1).simplified());
    }

    finish();
}

void Updater::remplacement()
{
    const QStringList listeNames = name.split("\n", QString::SkipEmptyParts);

    quint16 i = 0;

    for(const QString &fileName : listeNames)
    {
        if(QFile::exists(fileName))
            QFile::remove(fileName);

        QFile::rename(QString("TempFile%1.tmp").arg(++i), fileName);
    }
}
void Updater::sendRequest(QueryState state)
{
    switch(state)
    {
    case FileQuery :
#ifdef Q_OS_LINUX
        request = "LinuxStartFile";
#elif defined(Q_OS_WIN)
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
