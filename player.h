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
        m_Volatility{initialVolatility}
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
     * @brief Set rating.
     *
     * @param[in]   rating      New rating.
     */
    void SetRating(double rating)
    {
        m_Rating = rating;
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
     * @brief Set deviation.
     *
     * @param[in]   deviation       New deviation.
     */
    void SetDeviation(double deviation)
    {
        m_Deviation = deviation;
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
     * @brief Set volatility.
     *
     * @param[in]   volatility      New volatility.
     */
    void SetVolatility(double volatility)
    {
        m_Volatility = volatility;
    }
protected:
private:
    double      m_Rating;       ///< Player's rating.
    double      m_Deviation;    ///< Player's rating deviation.
    double      m_Volatility;   ///< Player's rating volatility.
};

} // namespace glicko

#endif // GLICKO_PLAYER_H
