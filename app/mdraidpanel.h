#ifndef MDRAIDPANEL_H
#define MDRAIDPANEL_H

#include <QWidget>
#include <QTimer>

#include "mdraidpropertiesmodel.h"



namespace Ui {
class MDRaidPanel;
}

class MDRaidPanel : public QWidget
{
  Q_OBJECT

public:
  explicit MDRaidPanel(QWidget *parent = 0);
  ~MDRaidPanel();

  void setMDRaid(MDRaid* raid);

private:
  Ui::MDRaidPanel* ui;
  MDRaidPropertiesModel* model;
  QTimer* autorefreshTimer;

  void updateAutoRefresh();

public slots:
  void refresh();
  void startScrubbing();
};

#endif // MDRAIDPANEL_H
