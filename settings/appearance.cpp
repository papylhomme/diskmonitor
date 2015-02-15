#include "appearance.h"

#include "iconmode.h"

using namespace Settings;



/*
 * Constructor
 */
Appearance::Appearance(QWidget *parent) : QWidget(parent) {
  setupUi(this);

  iconModeButtonGroup = new InvisibleButtonGroup(this);
  iconModeButtonGroup -> setObjectName("kcfg_IconMode");
  iconModeButtonGroup -> addButton(emotesIconModeRadioButton, int(DiskMonitor::IconMode::Emotes));
  iconModeButtonGroup -> addButton(dialogsIconModeRadioButton, int(DiskMonitor::IconMode::Dialogs));
  iconModeButtonGroup -> addButton(customIconModeRadioButton, int(DiskMonitor::IconMode::Custom));
}


