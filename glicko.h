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

#ifndef GLICKO_GLICKO_H
#define GLICKO_GLICKO_H

#include "player.h"
#include "exceptions.h"
#include <QMap>

namespace glicko
{

/**
 * @todo comment.
 * @todo no copy no move.
 */
template <typename IDTYPE> class Glicko
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in]   initialRating       Initial rating.
     * @param[in]   initialDeviation    Initial rating deviation.
     * @param[in]   initialVolatility   Initial rating volatility.
     */
    Glicko(double initialRating, double initialDeviation, double initialVolatility):
        m_DefaultRating{initialRating},
        m_DefaultDeviation{initialDeviation},
        m_DefaultVolatility{initialVolatility}
    {
    }
    /**
     * @brief Destructor.
     */
    ~Glicko()
    {
        qDeleteAll(m_Players);
    }
    /**
     * @brief Create a new player.
     *
     * Player will be created with the default values for rating, deviation and volatility.
     * @throws glicko::GlickoException when player with this ID already exists.
     * @param[in]   playerID    ID of the player.
     */
    void CreatePlayer(const IDTYPE &playerID)
    {
        // check if player with this ID already exists
        if(m_Players.contains(playerID))
        {
            GLTHROW("Player with this ID already exists.");
        }
        // create player
        m_Players[playerID] = new Player{m_DefaultRating, m_DefaultDeviation, m_DefaultVolatility};
    }
    /**
     * @brief remove a player.
     *
     * @throws glicko::GlickoException when player with this ID does not exist.
     * @param[in]   playerID    ID of the player.
     */
    void RemovePlayer(const IDTYPE &playerID)
    {
        auto it = m_Players.find(playerID);
        // check if player with this ID already exists
        if(it == m_Players.end())
        {
            GLTHROW("Player with this ID does not exist.");
        }
        // remove player
        delete *it;
        m_Players.remove(playerID);
    }
protected:
private:
    QMap<IDTYPE, Player *>  m_Players;              ///< The players.
    double                  m_DefaultRating{0};     ///< Default rating when creating a new player.
    double                  m_DefaultDeviation{0};  ///< Default rating deviation when creating a new player
    double                  m_DefaultVolatility{0}; ///< Default rating volatility when creating a new player
    Glicko(const Glicko&) = delete;
    Glicko(Glicko &&) = delete;
    Glicko & operator = (const Glicko&) = delete;
    Glicko & operator = (Glicko &&) = delete;
};

} // namespace glicko

#endif // GLICKO_GLICKO_H
