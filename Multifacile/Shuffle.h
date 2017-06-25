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

#include <array>

class Shuffle  // Classe melengeant les tables
{
public:
    Shuffle(bool shuffle);

    void getNumbers(std::array<unsigned short int, 10> &tab);
    void getNumbers(std::array<unsigned short int, 10> &tab, std::array<unsigned short int, 10> &array);

    static int random(int a, int b);
private:
    bool _needShuffle;
    std::array<unsigned char, 10> _numbers;
};

#endif // SHUFFLE_H
