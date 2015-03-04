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


#include "humanize.h"

#include <QStringList>


/*
 *
 */
Humanize::Humanize()
{

}


/*
 *
 */
Humanize::~Humanize()
{

}



/*
 * Format a size given in octet
 *
 * TODO: more option (look at duration)
 */
QString Humanize::size(qint64 size)
{
  double num = size;
  QStringList list;
  list << "KB" << "MB" << "GB" << "TB";

  QStringListIterator i(list);
  QString unit("bytes");

  while(num >= 1024.0 && i.hasNext())
   {
      unit = i.next();
      num /= 1024.0;
  }

  return QString().setNum(num, 'f', 2) + " " + unit;
}



/*
 * Format a duration given in unit inputUnit, keeping only units starting
 * from keepFrom
 *
 * available units are 'us', 'ms', 's', 'm', 'h' and 'd'
 */
QString Humanize::duration(qint64 duration, QString inputUnit, QString keepFrom)
{
  QStringList units;
  units << "us" << "ms" << "s" << "m" << "h" << "d";
  QList<int> unitAmount;
  unitAmount << 1000 << 1000 << 60 << 60 << 24 << 1;


  QStringList res;

  int idx = units.indexOf(inputUnit);
  int keepFromIdx = units.indexOf(keepFrom);

  if(idx == -1)
    qFatal("Humanize::duration:  Unknown input unit");

  int currentAmount = unitAmount.at(idx);
  QString unit = units.at(idx);

  while(idx < units.size() && duration >= currentAmount) {
    int r = duration % currentAmount;
    duration /= currentAmount;

    if(r > 0 && idx >= keepFromIdx)
      res.push_front(QString::number(r) + " " + unit);

    if(++idx == units.size())
      break;

    unit = units.at(idx);
    currentAmount = unitAmount.at(idx);
  }

  res.push_front(QString::number(duration) + " " + unit);
  return res.join(" ");
}



/*
 * Format a percentage given as a double between 0.0 and 1.0
 */
QString Humanize::percentage(double percent)
{
  return QString().setNum(percent * 100, 'f', 2) + " %";
}



/*
 * Convert temperature given as millikelvin to celcius
 *
 * TODO: more option (fahrenheit)
 */
QString Humanize::temperature(qint64 temp)
{
  return QString().setNum(temp / 1000.0 - 273, 'f', 2) + "°C";
}

