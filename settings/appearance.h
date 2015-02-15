#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "ui_appearance.h"

#include "invisiblebuttongroup.h"

namespace Settings {

  /*
   * Config page for general appearance settings
   */
  class Appearance : public QWidget, public Ui::Appearance
  {
  public:
    explicit Appearance(QWidget *parent);

  private:
    InvisibleButtonGroup* iconModeButtonGroup;
  };

}



#endif //APPEARANCE_H
