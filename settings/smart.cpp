#include "smart.h"


/*
 * Constructor
 */
SMART::SMART(QWidget *parent) : QWidget(parent) {
  setupUi(this);

  connect(this -> clearButton, SIGNAL(clicked()), this, SLOT(clear()));
  connect(this -> addButton, SIGNAL(clicked()), this, SLOT(add()));
  connect(this -> removeButton, SIGNAL(clicked()), this, SLOT(remove()));
}



/*
 * Add the value from the spinbox to the list
 */
void SMART::add()
{
  this -> kcfg_SensitiveAttributes -> addItem(new QListWidgetItem(QString::number(this -> spinBox -> value())));
}



/*
 * Remove the current item from the list
 */
void SMART::remove()
{
  int row = this -> kcfg_SensitiveAttributes -> currentRow();

  if(row >= 0) {
    QListWidgetItem* item = this -> kcfg_SensitiveAttributes -> takeItem(row);
    delete item;
  }
}



/*
 * Empty the list
 */
void SMART::clear()
{
  this -> kcfg_SensitiveAttributes -> clear();
}

