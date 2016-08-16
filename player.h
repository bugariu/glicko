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

#ifndef GLICKO_PLAYER_H
#define GLICKO_PLAYER_H

namespace glicko
{

/**
 * @brief Class describing one player.
 *
 * It has a rating, a rating deviation and a rating volatility.
 * As a "current" value and a "new" value. The "new" value will be
 * taken when AdoptNewValues is called.
 * @attention Values in glicko2 scale!
 */
class Player
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in]   initialRating       Initial rating.
     * @param[in]   initialDeviation    Initial rating deviation.
     * @param[in]   initialVolatility   Initial rating volatility.
     */
    Player(double initialRating, double initialDeviation, double initialVolatility):
        m_Rating{initialRating},
        m_Deviation{initialDeviation},
        m_Volatility{initialVolatility},
        m_NewRating{initialRating},
        m_NewDeviation{initialDeviation},
        m_NewVolatility{initialVolatility}
    {
    }
    /**
     * @brief Get rating.
     *
     * @return  Current rating.
     */
    double GetRating() const
    {
        return m_Rating;
    }
    /**
     * @brief Get deviation.
     *
     * @return  Current deviation.
     */
    double GetDeviation() const
    {
        return m_Deviation;
    }
    /**
     * @brief Get volatility.
     *
     * @return  Current volatility.
     */
    double GetVolatility() const
    {
        return m_Volatility;
    }
    /**
     * @brief Set new rating.
     *
     * Rating will be adopted when AdoptNewValues is called.
     * @param[in]   rating      New rating.
     */
    void SetNewRating(double rating)
    {
        m_NewRating = rating;
    }
    /**
     * @brief Set deviation.
     *
     * Rating will be adopted when AdoptNewValues is called.
     * @param[in]   deviation       New deviation.
     */
    void SetNewDeviation(double deviation)
    {
        m_NewDeviation = deviation;
    }
    /**
     * @brief Set volatility.
     *
     * Rating will be adopted when AdoptNewValues is called.
     * @param[in]   volatility      New volatility.
     */
    void SetNewVolatility(double volatility)
    {
        m_NewVolatility = volatility;
    }
    /**
     * @brief AdoptNewValues
     */
    void AdoptNewValues()
    {
        m_Rating = m_NewRating;
        m_Deviation = m_NewDeviation;
        m_Volatility = m_NewVolatility;
    }
private:
    double      m_Rating{0};            ///< Player's current rating.
    double      m_Deviation{0};         ///< Player's current rating deviation.
    double      m_Volatility{0};        ///< Player's current rating volatility.
    double      m_NewRating{0};         ///< Player's new rating.
    double      m_NewDeviation{0};      ///< Player's new rating deviation.
    double      m_NewVolatility{0};     ///< Player's new rating volatility.
};

} // namespace glicko

#endif // GLICKO_PLAYER_H
