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


#ifndef ATADRIVEPANEL_H
#define ATADRIVEPANEL_H

#include "udisks2wrapper.h"
#include "atadrivepropertiesmodel.h"
#include "storageunitpanel.h"


namespace Ui {
class AtaDrivePanel;
}

class AtaDrivePanel : public StorageUnitPanel
{
    Q_OBJECT

public:
    explicit AtaDrivePanel(QWidget *parent = nullptr);
    ~AtaDrivePanel() override;

  void setAtaDrive(AtaDrive* drive);
  AtaDrive* getAtaDrive();

protected:
  virtual void updateUI() override;
  virtual bool isOperationRunning() override;

private:
  Ui::AtaDrivePanel *ui;

  QString localizeSelfTestStatus(QString status) const;

public slots:
  void enableSmart();
  void startShortSelfTest();
  void startExtendedSelfTest();
  void startSelfTest(UDisks2Wrapper::SMARTSelfTestType type);
  void cancelSelfTest();
};

#endif // ATADRIVEPANEL_H
