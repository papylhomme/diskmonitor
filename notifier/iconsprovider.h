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


#ifndef ICONSPROVIDER_H
#define ICONSPROVIDER_H

#include <QString>
#include <QObject>


#include "types.h"



/*
 * Class to manage icons from the Qml world
 */
class IconsProvider: public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString iconUnknown READ iconUnknown WRITE setIconUnknown NOTIFY iconUnknownChanged())
  Q_PROPERTY(QString iconHealthy READ iconHealthy WRITE setIconHealthy NOTIFY iconHealthyChanged())
  Q_PROPERTY(QString iconWarning READ iconWarning WRITE setIconWarning NOTIFY iconWarningChanged())
  Q_PROPERTY(QString iconFailing READ iconFailing WRITE setIconFailing NOTIFY iconFailingChanged())

public:
  IconsProvider();
  ~IconsProvider();


  const QString& iconUnknown() const;
  const QString& iconHealthy() const;
  const QString& iconWarning() const;
  const QString& iconFailing() const;

  Q_INVOKABLE QString iconForStatus(int healthStatus) const;

  void setIconUnknown(const QString& unknownIcon);
  void setIconHealthy(const QString& healthyIcon);
  void setIconWarning(const QString& warningIcon);
  void setIconFailing(const QString& failingIcon);

signals:
  void iconUnknownChanged();
  void iconHealthyChanged();
  void iconWarningChanged();
  void iconFailingChanged();

private:
  QString unknownIcon;
  QString healthyIcon;
  QString warningIcon;
  QString failingIcon;
};

#endif // ICONSPROVIDER_H
