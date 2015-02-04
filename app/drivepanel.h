#ifndef DRIVEPANEL_H
#define DRIVEPANEL_H

#include <QWidget>

#include "drivepropertiesmodel.h"


namespace Ui {
class DrivePanel;
}

class DrivePanel : public QWidget
{
    Q_OBJECT

public:
    explicit DrivePanel(QWidget *parent = 0);
    ~DrivePanel();

  void setDrive(Drive* drive);
  void refresh();

private:
    Ui::DrivePanel *ui;
    DrivePropertiesModel* model;

public slots:
    void startSelfTest();
};

#endif // DRIVEPANEL_H
