#ifndef APPLET_H
#define APPLET_H

#include "ui_applet.h"

namespace Settings {

  /*
   * Config page for general appearance settings
   */
  class Applet : public QWidget, public Ui::Applet
  {
  public:
      Applet(QWidget* parent = NULL);
      ~Applet();
  };

}

#endif // APPLET_H
