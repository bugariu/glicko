/******************************************************************************//**
 * @file
 * @brief The glicko system
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

#ifndef GLICKO_GLICKO_H
#define GLICKO_GLICKO_H

#include <map>
#include <list>
#include <cmath>

namespace glicko
{

namespace config
{
constexpr double GLICO_CONSTANT = 173.7178;                     ///< The glicko constant to convert from glicko to glicko2 ratings.
constexpr double INITIAL_RATING = 1500;                         ///< Initial glicko rating for a new player.
constexpr double INITIAL_DEVIATION = 350;                       ///< Initial glicko rating deviation for a new player.
}

/**
 * @brief Additional macro to throw an exception of type glicko::GlickoException.
 *
 * @param[in] msg   The message.
 */
#define GLTHROW(msg) throw glicko::GlickoException{msg, __FILE__, __LINE__};

/**
 * @brief Glicko exception.
 *
 * Saves file name and line number where exception was thrown.
 */
class GlickoException : public std::runtime_error
{
public:
    /**
     * @brief Constructor
     *
     * @param[in]   message     Message of exception.
     * @param[in]   fileName    File name where exception occured.
     * @param[in]   line        Line where exception occured.
     */
    GlickoException(const std::string &message, const std::string &fileName, int line):
        std::runtime_error{message},
        m_FileName{fileName},
        m_Line{line}
    {
    }
    /**
     * @brief Get file name.
     *
     * @return File name.
     */
    std::string GetFileName() const
    {
        return m_FileName;
    }
    /**
     * @brief Get line number.
     *
     * @return Line number.
     */
    int GetLine() const
    {
        return m_Line;
    }
private:
    std::string m_FileName; ///< File name where exception occured.
    int         m_Line;     ///< Line in which exception occured.
};


/**
 * @brief Game result
 */
enum class GameResult
{
    Player1,    ///< Player 1 has won.
    Draw,       ///< Draw.
    Player2     ///< player 2 has won.
};


/**
 * @brief The glicko system.
 *
 * It handles players, games and computation stuff.
 */
template <typename IDTYPE> class Glicko
{

private:
    /**
     * @brief Game class
     */
    class Game
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
        GameResult  m_Result{GameResult::Draw}; ///< Game result.
    };


    /**
     * @brief Helper struct for games.
     */
    struct GameHelper
    {
        double  mu;     ///< @todo comment
        double  phi;    ///< @todo comment
        double  g;      ///< @todo comment
        double  E;      ///< @todo comment
        double  s;      ///< @todo comment
    };


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


public:
    /**
     * @brief Constructor.
     *
     * @param[in]   initialVolatility   Initial rating volatility.
     * @param[in]   tau                 Tau system constant.
     */
    Glicko(double initialVolatility, double tau):
        m_DefaultVolatility{initialVolatility},
        m_Tau{tau}
    {
    }
    static std::string GetVersion()
    {
        return "0.3.1";
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
        if(m_Players.find(playerID) != m_Players.end())
        {
            GLTHROW("Player with this ID already exists.");
        }
        // create player
        m_Players.insert({playerID, {0, config::INITIAL_DEVIATION/config::GLICO_CONSTANT, m_DefaultVolatility}});
    }
    /**
     * @brief Create a new player.
     *
     * Player will be created with the provided values for rating, deviation and volatility.
     * @throws glicko::GlickoException when player with this ID already exists.
     * @param[in]   playerID            ID of the player.
     * @param[in]   initialRating       Initial rating.
     * @param[in]   initialDeviation    Initial rating deviation.
     * @param[in]   initialVolatility   Initial rating volatility.
     */
    void CreatePlayer(const IDTYPE &playerID, double initialRating, double initialDeviation, double initialVolatility)
    {
        // check if player with this ID already exists
        if(m_Players.find(playerID) != m_Players.end())
        {
            GLTHROW("Player with this ID already exists.");
        }
        // create player
        m_Players.insert({playerID, {(initialRating-config::INITIAL_RATING)/config::GLICO_CONSTANT,
                                     initialDeviation/config::GLICO_CONSTANT, initialVolatility}});
    }
    /**
     * @brief Remove a player.
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
    /**
     * @brief Get rating for one player.
     *
     * @throws glicko::GlickoException when player with this ID does not exist.
     * @param[in]   playerID    ID of the player.
     * @retun                   Player rating.
     */
    double GetRating(const IDTYPE &playerID)
    {
        auto it = m_Players.find(playerID);
        // check if player with this ID already exists
        if(it == m_Players.end())
        {
            GLTHROW("Player with this ID does not exist.");
        }
        return config::GLICO_CONSTANT * it->second.GetRating() + config::INITIAL_RATING;
    }
    /**
     * @brief Get rating deviation for one player.
     *
     * @throws glicko::GlickoException when player with this ID does not exist.
     * @param[in]   playerID    ID of the player.
     * @retun                   Player rating deviation.
     */
    double GetDeviation(const IDTYPE &playerID)
    {
        auto it = m_Players.find(playerID);
        // check if player with this ID already exists
        if(it == m_Players.end())
        {
            GLTHROW("Player with this ID does not exist.");
        }
        return config::GLICO_CONSTANT * it->second.GetDeviation();
    }
    /**
     * @brief Get rating volatility for one player.
     *
     * @throws glicko::GlickoException when player with this ID does not exist.
     * @param[in]   playerID    ID of the player.
     * @retun                   Player rating volatility.
     */
    double GetVolatility(const IDTYPE &playerID)
    {
        auto it = m_Players.find(playerID);
        // check if player with this ID already exists
        if(it == m_Players.end())
        {
            GLTHROW("Player with this ID does not exist.");
        }
        return it->second.GetVolatility();
    }
    /**
     * @brief Add a game.
     *
     * @param[in]   playerID1   ID of player 1.
     * @param[in]   playerID2   ID of player 2.
     * @param[in]   result      game result.
     */
    void AddGame(const IDTYPE &playerID1, const IDTYPE &playerID2, GameResult result)
    {
        m_Games.push_back({playerID1, playerID2, result});
    }
    /**
     * @brief Compute new player ratings.
     *
     * Ratings for all players are updated.
     * @attention List of played games is deleted after computing new ratings.
     */
    void ComputeRatings()
    {
        // iterate through players
        for(auto it = m_Players.begin(); it != m_Players.end(); ++it)
        {
            IDTYPE playerID = it->first;
            Player & player = it->second;
            std::list<GameHelper> playedGames = CreateGameHelperList(playerID, player.GetRating());
            // compute new ratings for player
            if(!playedGames.empty())
            {
                // player has played some games
                double v = 0;
                double delta = 0;
                for(auto & it : playedGames)
                {
                    v += it.g*it.g*it.E*(1-it.E);
                    delta += it.g*(it.s-it.E);
                }
                v = 1/v;
                delta = v*delta;
                // start iteration
                double sigma = player.GetVolatility();
                double phi = player.GetDeviation();
                double a = log(sigma*sigma);
                double A = a;
                double B = 0;
                constexpr double EPSILON = 0.000001;
                if(delta*delta > phi*phi + v)
                {
                    B = log(delta*delta - phi*phi - v);
                }
                else
                {
                    // iterate
                    double k = 1;
                    while(f(a - k*m_Tau, delta, phi, v, a) < 0)
                    {
                        k++;
                    }
                    B = a - k*m_Tau;
                }
                double fA = f(A, delta, phi, v, a);
                double fB = f(B, delta, phi, v, a);
                while(fabs(B-A) > EPSILON)
                {
                    double C = A + (A - B)*fA/(fB-fA);
                    double fC = f(C, delta, phi, v, a);
                    if(fB*fC < 0)
                    {
                        A = B;
                        fA = fB;
                    }
                    else
                    {
                        fA = fA/2;
                    }
                    B = C;
                    fB = fC;
                }
                double newSigma = exp(A/2);
                double phiStarSquare = phi*phi + newSigma*newSigma;
                double newPhi = 1/sqrt(1/phiStarSquare + 1/v);
                double newMu = player.GetRating() + newPhi*newPhi*delta/v;
                player.SetNewRating(newMu);
                player.SetNewDeviation(newPhi);
                player.SetNewVolatility(newSigma);
            }
            else
            {
                // player has not played any games
                double phi = player.GetDeviation();
                double sigma = player.GetVolatility();
                player.SetNewDeviation(sqrt(phi*phi + sigma*sigma));
            }
        }
        // adopt new ratings for each player
        for(auto & player : m_Players)
        {
            player.second.AdoptNewValues();
        }
        // cleanup games list
        m_Games.clear();
    }
protected:
private:
    std::map<IDTYPE, Player>    m_Players;                          ///< The players.
    std::list<Game>             m_Games;                            ///< The games played.
    double                      m_DefaultVolatility{0};             ///< Default rating volatility when creating a new player.
    double                      m_Tau{0};                           ///< Tau system constant.
    /**
     * @brief Create and fill list of game helper structs.
     *
     * @param[in]   playerID        Player ID.
     * @param[in]   playerRating    Rating for player.
     * @return                      The list of game helper structs
     */
    std::list<GameHelper> CreateGameHelperList(const IDTYPE playerID, double playerRating)
    {
        std::list<GameHelper> result;
        // search for played games and add according results
        for(auto & game : m_Games)
        {
            const Player * opponent{nullptr};
            double s = 0;
            if(game.GetPlayer1ID() == playerID)
            {
                // we are the first player
                auto it = m_Players.find(game.GetPlayer2ID());
                if(it != m_Players.end())
                {
                    opponent = &(it->second);
                    s = (game.GetResult() == GameResult::Player1) ? 1 : ((game.GetResult() == GameResult::Draw) ? 0.5 : 0);
                }
            }
            else if(game.GetPlayer2ID() == playerID)
            {
                // we are the second player
                auto it = m_Players.find(game.GetPlayer1ID());
                if(it != m_Players.end())
                {
                    opponent = &(it->second);
                    s = (game.GetResult() == GameResult::Player2) ? 1 : ((game.GetResult() == GameResult::Draw) ? 0.5 : 0);
                }
            }
            if(opponent)
            {
                double mu = opponent->GetRating();
                double phi = opponent->GetDeviation();
                double g = 1/sqrt(1+3*phi*phi/M_PI/M_PI);
                double E = 1/(1+exp(-g*(playerRating-mu)));
                result.push_back({mu, phi, g, E, s});
            }
        }
        return result;
    }
    /**
     * @brief f function.
     *
     * @todo comment
     * @param[in]   x       @todo comment
     * @param[in]   delta   @todo comment
     * @param[in]   phi     @todo comment
     * @param[in]   v       @todo comment
     * @param[in]   a       @todo comment
     * @return
     */
    double f(double x, double delta, double phi, double v, double a)
    {
        return exp(x)*(delta*delta - phi*phi - v - exp(x))/2/(phi*phi + v + exp(x))/(phi*phi + v + exp(x)) - (x - a)/m_Tau/m_Tau;
    }
};

} // namespace glicko

#endif // GLICKO_GLICKO_H
