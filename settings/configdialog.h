#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <KConfigDialog>


namespace Settings {


  /*
   * Override KConfigDialog to provide reloadable facility
   */
  class ConfigDialog : public KConfigDialog
  {
  public:
      ConfigDialog(QWidget* parent = NULL);
      ~ConfigDialog();

      static bool showDialog(QWidget* parent = NULL, bool appletConfig = false);
  };

}

#endif // CONFIGDIALOG_H
