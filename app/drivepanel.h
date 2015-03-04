#ifndef DRIVEPANEL_H
#define DRIVEPANEL_H

#include "udisks2wrapper.h"
#include "drivepropertiesmodel.h"
#include "storageunitpanel.h"


namespace Ui {
class DrivePanel;
}

class DrivePanel : public StorageUnitPanel
{
    Q_OBJECT

public:
    explicit DrivePanel(QWidget *parent = 0);
    ~DrivePanel();

  void setDrive(Drive* drive);
  Drive* getDrive();

protected:
  virtual void updateUI();
  virtual bool isOperationRunning();

private:
  Ui::DrivePanel *ui;

  QString localizeSelfTestStatus(QString status) const;

public slots:
  void enableSmart();
  void startShortSelfTest();
  void startExtendedSelfTest();
  void startSelfTest(UDisks2Wrapper::SMARTSelfTestType type);
};

#endif // DRIVEPANEL_H
