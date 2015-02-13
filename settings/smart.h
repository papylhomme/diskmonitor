#ifndef SMART_H
#define SMART_H

#include "ui_smart.h"


/*
 * Config page for SMART settings
 */
class SMART : public QWidget, public Ui::SMART
{
  Q_OBJECT

public:
    explicit SMART(QWidget *parent); 

public slots:
  void add();
  void remove();
  void clear();
};



#endif //SMART_H
