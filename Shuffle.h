/*Copyright (C) <2012> <Plestan> <Kévin>

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

class Shuffle
{
public:
    Shuffle(bool shuffle);
    void getNumbers(int tab[]);
    void getNumbers(int tab[], int array[]);
private:
    bool needShuffle;
    int numbers[10];
    int n;
};

#endif // SHUFFLE_H
