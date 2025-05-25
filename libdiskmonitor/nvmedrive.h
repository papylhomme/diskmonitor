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


#ifndef NVMEDRIVE_H
#define NVMEDRIVE_H

#include "drive.h"



/*
 * Represent an NVME Drive node in UDisks2
 */
class NvmeDrive : public Drive
{
  Q_OBJECT


public:
  explicit NvmeDrive(QDBusObjectPath objectPath, QString device);
  ~NvmeDrive();

  bool isSmartEnabled() const;
  bool isSmartSupported() const;

  int getSelfTestPercentRemaining() const;
  const QString& getSelfTestStatus() const;
  const NvmeSmartAttributes& getSMARTAttributes() const;

  virtual void update() override;
  virtual bool isNvmeDrive() const override { return true; }

protected:
    bool smartEnabled = false;
    bool smartSupported = false;
    int selfTestPercentRemaining = 0;

    QString selfTestStatus;
    NvmeSmartAttributes attributes;

signals:

public slots:
};

#endif // NVMEDRIVE_H
