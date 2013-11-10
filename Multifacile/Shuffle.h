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

#ifndef SHUFFLE_H
#define SHUFFLE_H

#include <cstdlib>
#include <ctime>

class Shuffle  // Classe melengeant les tables
{
public:
    Shuffle(bool shuffle);
    void getNumbers(int tab[]);  //initialise un tableau allant de 1 à 10 dans l'ordre ou dans le desordre en fonction de _needShuffle
    void getNumbers(int tab[], unsigned short int array[]);  //initialise 2 tableau allant de 1 à 10 dans le desordre
private:
    bool _needShuffle;
    unsigned short int _numbers[10];
};

#endif // SHUFFLE_H
