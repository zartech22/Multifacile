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

// Fichier contenant des enumerations utiles a differents endroits

#ifndef MODEENUM_H
#define MODEENUM_H

enum Mode
{
    EASY, MEDIUM, HARD
};

enum Widget
{
    FirstWidget, SecondWidget
};

typedef enum Mode Mode;
typedef enum Widget Widget;
typedef unsigned short int operande;

#endif // MODEENUM_H
