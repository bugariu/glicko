/******************************************************************************//**
 * @file
 * @brief Some usefull defines
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

#ifndef GLICKO_DEFINES_H
#define GLICKO_DEFINES_H

/**
 * @brief Additional macro to prevent copy of a class.
 *
 * @param[in] Class Class name.
 */
#define GL_DISABLE_COPY(Class) Class(const Class &) = delete; Class &operator=(const Class &) = delete;

/**
 * @brief Additional macro to prevent move of a class.
 *
 * @param[in] Class Class name.
 */
#define GL_DISABLE_MOVE(Class) Class(Class &&) = delete; Class &operator=(Class &&) = delete;

/**
 * @brief Additional macro to prevent copy and move of a class.
 *
 * @param[in] Class Class name.
 */
#define GL_DISABLE_COPY_AND_MOVE(Class) GL_DISABLE_COPY(Class) GL_DISABLE_MOVE(Class)

#endif // GLICKO_DEFINES_H
