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

#include "Shuffle.h"

Shuffle::Shuffle(bool shuffle) : needShuffle(shuffle)
{
}
void Shuffle::getNumbers(int tab[])
{
        srand(time(0));

        for (int i=0; i<10; ++i)
            numbers[i] = i+1;
        if(needShuffle)
        {

            for (int i=0; i<(10-1); ++i)
            {
                int r = i + (rand() % (10-i));
                int temp = numbers[i]; numbers[i] = numbers[r]; numbers[r] = temp;
            }
        }
            for(int i = 0; i<10; ++i)
                tab[i] = numbers[i];
}
void Shuffle::getNumbers(int tab[], int array[])
{
    srand(time(0));

    for (int i=0; i<10; ++i)
        numbers[i] = i;

    for (int i=0; i<(10-1); ++i)
    {
        int r = i + (rand() % (10-i));
        int temp = numbers[i]; numbers[i] = numbers[r]; numbers[r] = temp;
    }
    for(int i = 0; i<10; ++i)
    {
        ++numbers[i];
        tab[i] = numbers[i];
    }
    for(int i = 0; i < (10-1); ++i)
    {
        int r = i + (rand() % (10-i));
        int temp = numbers[i]; numbers[i] = numbers[r]; numbers[r] = temp;
    }
    for(int i = 0; i < 10; ++i)
        array[i] = numbers[i];
}
