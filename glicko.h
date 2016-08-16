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
#include "game.h"
#include "exceptions.h"
#include "defines.h"
#include <QMap>
#include <cmath>

namespace glicko
{

namespace
{
constexpr double PI = 3.141592653589793238462643383279502884;
}

/**
 * @brief The glicko system.
 *
 * It handles players, games and computation stuff.
 */
template <typename IDTYPE> class Glicko
{
    GL_DISABLE_COPY_AND_MOVE(Glicko);

private:
    struct helper
    {
        double  mu;
        double  phi;
        double  g;
        double  E;
        double  s;
    };

    using GameType = Game<IDTYPE>;

public:
    /**
     * @brief Constructor.
     *
     * @param[in]   initialRating       Initial rating.
     * @param[in]   initialDeviation    Initial rating deviation.
     * @param[in]   initialVolatility   Initial rating volatility.
     * @param[in]   tau                 tau system constant.
     */
    Glicko(double initialRating, double initialDeviation, double initialVolatility, double tau):
        m_DefaultRating{initialRating},
        m_DefaultDeviation{initialDeviation},
        m_DefaultVolatility{initialVolatility},
        m_Tau{tau}
    {
    }
    /**
     * @brief Destructor.
     */
    ~Glicko()
    {
        qDeleteAll(m_Players);
        qDeleteAll(m_Games);
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
        m_Players[playerID] = new Player{(m_DefaultRating-155)/173.7178, m_DefaultDeviation/173.7178, m_DefaultVolatility};
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
        if(m_Players.contains(playerID))
        {
            GLTHROW("Player with this ID already exists.");
        }
        // create player
        m_Players[playerID] = new Player{(initialRating-1500)/173.7178, initialDeviation/173.7178, initialVolatility};
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

    double GetRating(const IDTYPE &playerID)
    {
        auto it = m_Players.find(playerID);
        // check if player with this ID already exists
        if(it == m_Players.end())
        {
            GLTHROW("Player with this ID does not exist.");
        }
        return 173.7178*(*it)->GetRating() + 1500;
    }
    double GetDeviation(const IDTYPE &playerID)
    {
        auto it = m_Players.find(playerID);
        // check if player with this ID already exists
        if(it == m_Players.end())
        {
            GLTHROW("Player with this ID does not exist.");
        }
        return 173.7178*(*it)->GetDeviation();
    }
    double GetVolatility(const IDTYPE &playerID)
    {
        auto it = m_Players.find(playerID);
        // check if player with this ID already exists
        if(it == m_Players.end())
        {
            GLTHROW("Player with this ID does not exist.");
        }
        return (*it)->GetVolatility();
    }

    /**
     * @brief Add a game
     *
     * @param[in]   playerID1   ID of player 1.
     * @param[in]   playerID2   ID of player 2.
     * @param[in]   result      game result.
     */
    void AddGame(const IDTYPE &playerID1, const IDTYPE &playerID2, GameResult result)
    {
        m_Games.append(new GameType{playerID1, playerID2, result});
    }
    /**
     * @brief Compute new player ratings.
     */
    void ComputeRatings()
    {
        /// @todo implement
        // iterate through players
        for(auto it = m_Players.begin(); it != m_Players.end(); ++it)
        {
            IDTYPE playerID = it.key();
            Player *player = it.value();
            QList<helper> playedGames = GetGames(playerID, player->GetRating());
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
                double sigma = player->GetVolatility();
                double phi = player->GetDeviation();
                double a = log(sigma*sigma);
                double A = a;
                double B = 0;
                constexpr double EPSILON = 0.000001;
                if(delta*delta > phi*phi + v)
                {
                    B = delta*delta - phi*phi - v;
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
                double newMu = player->GetRating() + newPhi*newPhi*delta/v;
                player->SetNewRating(newMu);
                player->SetNewDeviation(newPhi);
                player->SetNewVolatility(newSigma);
            }
            else
            {
                // player has not played any games
                double phi = player->GetDeviation();
                double sigma = player->GetVolatility();
                player->SetNewDeviation(sqrt(phi*phi + sigma*sigma));
            }
        }
        // adopt new ratings for each player
        for(auto & player : m_Players)
        {
            player->AdoptNewValues();
        }
    }
protected:
private:
    QMap<IDTYPE, Player *>  m_Players;              ///< The players.
    QList<GameType *>       m_Games;                ///< The games played.
    double                  m_DefaultRating{0};     ///< Default rating when creating a new player.
    double                  m_DefaultDeviation{0};  ///< Default rating deviation when creating a new player
    double                  m_DefaultVolatility{0}; ///< Default rating volatility when creating a new player
    double                  m_Tau{0};               ///< Default rating volatility when creating a new player
    QList<helper> GetGames(const IDTYPE playerID, double rating)
    {
        QList<helper> result;
        // search for played games and add according results
        for(auto game : m_Games)
        {
            Player *opponent = nullptr;
            double s = 0;
            if(game->GetPlayer1ID() == playerID)
            {
                // we are the first player
                auto it = m_Players.find(game->GetPlayer2ID());
                if(it != m_Players.end())
                {
                    opponent = *it;
                    s = (game->GetResult() == GameResult::Player1) ? 1 : ((game->GetResult() == GameResult::Tie) ? 0.5 : 0);
                }
            }
            else if(game->GetPlayer2ID() == playerID)
            {
                // we are the second player
                auto it = m_Players.find(game->GetPlayer1ID());
                if(it != m_Players.end())
                {
                    opponent = *it;
                    s = (game->GetResult() == GameResult::Player2) ? 1 : ((game->GetResult() == GameResult::Tie) ? 0.5 : 0);
                }
            }
            if(opponent != nullptr)
            {
                double mu = opponent->GetRating();
                double phi = opponent->GetDeviation();
                double g = 1/sqrt(1+3*phi*phi/PI/PI);
                double E = 1/(1+exp(-g*(rating-mu)));
                result.append({mu, phi, g, E, s});
            }
        }
        return result;
    }
    double f(double x, double delta, double phi, double v, double a)
    {
        return exp(x)*(delta*delta - phi*phi - v - exp(x))/2/(phi*phi + v + exp(x)) - (x - a)/m_Tau/m_Tau;
    }
};

} // namespace glicko

#endif // GLICKO_GLICKO_H
