/******************************************************************************//**
 * @file
 * @brief Class glicko::Game
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

#ifndef GLICKO_GAME_H
#define GLICKO_GAME_H

namespace glicko
{

/**
 * @brief Game result
 */
enum class GameResult
{
    Player1,    ///< Player 1 has won.
    Tie,        ///< Tie.
    Player2     ///< player 2 has won.
};

/**
 * @brief Game class
 */
template <typename IDTYPE> class Game
{
public:
    /**
     * @brief Constructor
     *
     * @param[in]   player1ID   ID of player 1.
     * @param[in]   player2ID   ID of player 2.
     * @param[in]   result      Game result.
     */
    Game(const IDTYPE &player1ID, const IDTYPE &player2ID, GameResult result):
        m_Player1{player1ID},
        m_Player2{player2ID},
        m_Result{result}
    {
    }
    /**
     * @brief Get ID of player 1.
     *
     * @return ID of player 1.
     */
    IDTYPE GetPlayer1ID() const
    {
        return m_Player1;
    }
    /**
     * @brief Get ID of player 2.
     *
     * @return ID of player 2.
     */
    IDTYPE GetPlayer2ID() const
    {
        return m_Player2;
    }
    /**
     * @brief Get Game result.
     *
     * @return Game result.
     */
    GameResult GetResult() const
    {
        return m_Result;
    }
protected:
private:
    IDTYPE      m_Player1;                  ///< ID of player 1.
    IDTYPE      m_Player2;                  ///< ID of player 2.
    GameResult  m_Result{GameResult::Tie};  ///< Game result.
};

} // namespace glicko

#endif // GLICKO_GAME_H
