/******************************************************************************//**
 * @file
 * @brief Main routine
 *
 * @copyright Copyright (C) by Doru Julian Bugariu
 * julian@bugariu.eu
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation
 * 51 Franklin Street, Fifth Floor
 * Boston, MA 02110-1301, USA
 * http://www.fsf.org/about/contact.html
 *********************************************************************************/

#include "glicko.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    glicko::Glicko<int> glicko{0.06, 0.5};

    // add some players
    glicko.CreatePlayer(1, 1500, 200, 0.06);
    glicko.CreatePlayer(2, 1400, 30, 0.06);
    glicko.CreatePlayer(3, 1550, 100, 0.06);
    glicko.CreatePlayer(4, 1700, 300, 0.06);


    qDebug() << 1 << glicko.GetRating(1) << glicko.GetDeviation(1) << glicko.GetVolatility(1);
    qDebug() << 2 << glicko.GetRating(2) << glicko.GetDeviation(2) << glicko.GetVolatility(2);
    qDebug() << 3 << glicko.GetRating(3) << glicko.GetDeviation(3) << glicko.GetVolatility(3);
    qDebug() << 4 << glicko.GetRating(4) << glicko.GetDeviation(4) << glicko.GetVolatility(4);


    // add games
    glicko.AddGame(1, 2, glicko::GameResult::Player1);
    glicko.AddGame(1, 3, glicko::GameResult::Player2);
    glicko.AddGame(1, 4, glicko::GameResult::Player2);


    // compute ratings
    glicko.ComputeRatings();
    qDebug() << 1 << glicko.GetRating(1) << glicko.GetDeviation(1) << glicko.GetVolatility(1);
    qDebug() << 2 << glicko.GetRating(2) << glicko.GetDeviation(2) << glicko.GetVolatility(2);
    qDebug() << 3 << glicko.GetRating(3) << glicko.GetDeviation(3) << glicko.GetVolatility(3);
    qDebug() << 4 << glicko.GetRating(4) << glicko.GetDeviation(4) << glicko.GetVolatility(4);
}
