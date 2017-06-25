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

#include <random>
#include <functional>
#include <algorithm>
#include <chrono>

#include "Shuffle.h"

Shuffle::Shuffle(bool shuffle) : _needShuffle(shuffle) {}

void Shuffle::getNumbers(std::array<unsigned short, 10> &tab)
{
    for(int i = 0; i < 10; ++i) // 10 as defined in parameter
        tab.at(i) = i + 1;

    if(_needShuffle)
    {
        std::default_random_engine gen(std::time(nullptr));
        std::uniform_int_distribution<unsigned short int> dist(0, static_cast<unsigned short int>(tab.size() - 1));

        auto dice = std::bind(dist, gen);

        for(int i = 0; i < tab.size(); ++i)
        {
            const auto rand = (dice() % (tab.size() - i));
            const auto temp = tab.at(i);
            tab[i] = tab[rand];
            tab[rand] = temp;
        }
    }
}

void Shuffle::getNumbers(std::array<unsigned short, 10> &tab, std::array<unsigned short, 10> &array)
{
    for(int i = 0; i < tab.size(); ++i)
        tab.at(i) = i + 1;
    for(int i = 0; i < array.size(); ++i)
        array.at(i) = i + 1;

    std::default_random_engine gen(std::time(nullptr));
    std::uniform_int_distribution<unsigned short int> dist(0, static_cast<unsigned short int>(tab.size() - 1));

    auto dice = std::bind(dist, gen);

    for(int i = 0; i < tab.size(); ++i)
    {
        const auto rand = (dice() % (tab.size() - i));
        const auto temp = tab.at(i);
        tab[i] = tab[rand];
        tab[rand] = temp;
    }

    for(int i = 0; i < array.size(); ++i)
    {
        const auto rand = (dice() % (array.size() - i));
        const auto temp = array.at(i);
        array[i] = array[rand];
        array[rand] = temp;
    }
}

int Shuffle::random(int a, int b)
{
    if(a > b)
        std::swap(a, b);

    std::default_random_engine gen(std::time(nullptr));
    std::uniform_int_distribution<int> dist(a, b);

    return dist(gen);
}
