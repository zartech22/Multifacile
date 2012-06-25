#include "AstuceWindow.h"

AstuceWindow::AstuceWindow(const int table) : QMessageBox()
{
    astucesInit();
    this->addButton(QMessageBox::Ok);
    this->setIcon(QMessageBox::Information);
    if(astuces.contains(table))
        this->setText(astuces[table]);
    else
        this->setText("Il n'y a pas encore d'astuces pour cette table.");
}
void AstuceWindow::astucesInit()
{
    astuces[1] = "Pour la table de 1, le résultat sera toujours égal au nombre que multiplie 1.<br />Exemple :<br /><strong>1 x <span style=\"text-decoration: underline;\">7</span> = <span style=\"text-decoration: underline;\">7</span></strong>";
    astuces[2] = "Pour la table de 2, le résultat est toujours un nombre paire et les résultats vont de 2 en 2.<br />Exmple :<br /><strong>2 x 1 = <span style=\"text-decoration: underline;\">2</span><br />2 x 2 = <span style=\"text-decoration: underline;\">4</span></strong>";
    astuces[5] = "Pour la table de 5, le résultat termine soit par 0 soit par 5. Cela dépend du nombre que multiplie 5 : si le nombre est paire, le résultat terminera par 0 sinon, si le nombre est impaire, le résultat terminera par 5. En plus, les résultats vont de 5 en 5 !<br />Exemple :<br /><strong>5 x 2 = <span style=\"text-decoration: underline;\">10</span><br />5 x 3 = <span style=\"text-decoration: underline;\">15</span></strong>";
    astuces[10] = "Pour la table de 10, on rajoute un 0 au chiffre que multiplie 10.<br />Exemple :<br /><strong>5 x 10 = <span style=\"text-decoration: underline;\">50</span></strong>";
}
