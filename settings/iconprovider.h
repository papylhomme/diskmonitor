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


#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QObject>


namespace Settings {

  /*
   * Component to provide icons depending on the configuration
   */
  class IconProvider : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QString healthy READ healthy NOTIFY healthyChanged)
    Q_PROPERTY(QString failing READ failing NOTIFY failingChanged)
    Q_PROPERTY(QString unknown READ unknown NOTIFY unknownChanged)

  public:
    explicit IconProvider(QObject *parent = 0);
    ~IconProvider();

    QString healthy() const;
    QString failing() const;
    QString unknown() const;

  signals:
    void healthyChanged();
    void failingChanged();
    void unknownChanged();

  public slots:
    void configChanged();
  };

}

#endif // ICONPROVIDER_H
