#ifndef MDRAIDPANEL_H
#define MDRAIDPANEL_H


#include "mdraidpropertiesmodel.h"
#include "storageunitpanel.h"



namespace Ui {
class MDRaidPanel;
}

class MDRaidPanel : public StorageUnitPanel
{
  Q_OBJECT

public:
  explicit MDRaidPanel(QWidget *parent = 0);
  ~MDRaidPanel();

  void setMDRaid(MDRaid* raid);
  MDRaid* getMDRaid();

protected:
  virtual void updateUI();
  virtual bool isOperationRunning();

private:
  Ui::MDRaidPanel* ui;

public slots:
  void startScrubbing();
};

#endif // MDRAIDPANEL_H
