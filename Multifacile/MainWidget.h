/*Copyright (C) <2013> <Plestan> <Kévin>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSignalMapper>
#include <QApplication>

#include "Include.h"
#include "DataFileMgr.h"

class MainWidget : public QWidget  // Classe representant la fenetre de presentation des tables
{
    Q_OBJECT
public:
    MainWidget(Mode mode);

    void updateButtonsLabels(Mode mode);  //modifie le texte et le style des boutons de tables
    void updateButtonsLabels(Mode mode, bool isProgressifMode);  //idem
    void checkSucceedTables(Mode mode);  //verifie si les tables on ete reussite ou pas et modifie le style du bouton crorrespondant en consequence

private:
    QLabel *_point;
    QLabel *_texte;

    QPushButton *_bouton[10];
    QPushButton *_quit;
    //QPushButton *_tables;
    //QPushButton *_problems;

    QSignalMapper *_mapper;
    
signals:
    void clicked(int);
    //void goToProblems();
        
};

#endif // MAINWIDGET_H
