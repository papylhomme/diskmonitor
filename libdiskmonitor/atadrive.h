/****************************************************************************
 * DisKMonitor, KDE tools to monitor SMART and MDRaid health status         *
 * Copyright (C) 2014-2025 Michaël Lhomme <papylhomme@gmail.com>            *
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


#ifndef ATADRIVE_H
#define ATADRIVE_H

#include "drive.h"



/*
 * Represent an ATA Drive node in UDisks2
 */
class AtaDrive : public Drive
{
  Q_OBJECT


public:
  explicit AtaDrive(QDBusObjectPath objectPath, QString device);
  ~AtaDrive();

  bool isSmartEnabled() const;
  bool isSmartSupported() const;

  int getSelfTestPercentRemaining() const;
  const QString& getSelfTestStatus() const;
  const AtaSmartAttributesList& getSMARTAttributes() const;

  virtual void update() override;
  virtual bool isAtaDrive() const override { return true; }

protected:
    bool smartEnabled = false;
    bool smartSupported = false;
    int selfTestPercentRemaining = 0;

    QString selfTestStatus;
    AtaSmartAttributesList attributes;

signals:

public slots:
};

#endif // DRIVE_H
