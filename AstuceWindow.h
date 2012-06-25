#ifndef ASTUCEWINDOW_H
#define ASTUCEWINDOW_H

#include <QMessageBox>
#include <QMap>

class AstuceWindow : public QMessageBox
{
    Q_OBJECT
public:
    AstuceWindow(const int table);
private:
    QMap<int, QString> astuces;
    void astucesInit();
signals:
    
public slots:
    
};

#endif // ASTUCEWINDOW_H
