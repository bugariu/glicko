/******************************************************************************//**
 * @file
 * @brief Exception classes.
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

#ifndef GLICKO_EXCEPTIONS_H
#define GLICKO_EXCEPTIONS_H

#include <QString>
#include <stdexcept>

namespace glicko
{

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
    GlickoException(const QString &message, const QString &fileName, int line):
        std::runtime_error{message.toUtf8().constData()},
        m_FileName{fileName},
        m_Line{line}
    {
    }
    /**
     * @brief Get file name.
     *
     * @return File name.
     */
    QString GetFileName() const
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
    QString     m_FileName; ///< File name where exception occured.
    int         m_Line;     ///< Line in which exception occured.
};

} // namespace glicko

#define GLTHROW(msg) throw glicko::GlickoException{msg, __FILE__, __LINE__};

#endif // GLICKO_EXCEPTIONS_H
