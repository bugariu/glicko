/***************************************************************************
*   Copyright (C) by Doru Julian Bugariu                                  *
*   julian@bugariu.eu                                                     *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation                                              *
*   51 Franklin Street, Fifth Floor                                       *
*   Boston, MA 02110-1301, USA                                            *
*   http://www.fsf.org/about/contact.html                                 *
***************************************************************************/

#include "glicko.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    glicko::Glicko<int> glicko{1500, 350, 1.0};
    glicko.CreatePlayer(1);
    glicko.CreatePlayer(2);
    glicko.CreatePlayer(3);
}
