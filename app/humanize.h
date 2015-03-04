/****************************************************************************
 * DisKMonitor, KDE tools to monitor SMART and MDRaid health status         *
 * Copyright (C) 2014-2015 Michaël Lhomme <papylhomme@gmail.com>            *
 *                                                                          *
 * This program is free software; you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by     *
 * the Free Software Foundation; either version 2 of the License, or        *
 * (at your option) any later version.                                      *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 * GNU General Public License for more details.                             *
 *                                                                          *
 * You should have received a copy of the GNU General Public License along  *
 * with this program; if not, write to the Free Software Foundation, Inc.,  *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
 ****************************************************************************/


#ifndef HUMANIZE_H
#define HUMANIZE_H


#include <QString>


/*
 * Helpers class for formatting values to human friendly versions
 */
class Humanize
{
public:
    Humanize();
    ~Humanize();

    static QString size(qint64 size);
    static QString duration(qint64 duration, QString inputUnit = "ms", QString keepFrom = "");
    static QString percentage(double percent);
    static QString temperature(qint64 temp);
};

#endif // HUMANIZE_H
