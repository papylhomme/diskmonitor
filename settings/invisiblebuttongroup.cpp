#include "invisiblebuttongroup.h"

#include <kconfigdialogmanager.h>


using namespace Settings;




InvisibleButtonGroup::InvisibleButtonGroup(QWidget* parent) :
  QWidget(parent),
  d(new InvisibleButtonGroupPrivate)
{
  hide();
  d -> mGroup = new QButtonGroup(this);
  d -> mGroup -> setExclusive(true);
  connect(d -> mGroup, SIGNAL(buttonClicked(int)), SIGNAL(selectionChanged(int)) );

  const QString name = metaObject() -> className();
  if (!KConfigDialogManager::propertyMap() -> contains(name)) {
    KConfigDialogManager::propertyMap() -> insert(name, "current");
    KConfigDialogManager::changedMap() -> insert(name, SIGNAL(selectionChanged(int)));
  }
}


InvisibleButtonGroup::~InvisibleButtonGroup() {
  delete d;
}


int InvisibleButtonGroup::selected() const {
  return d->mGroup->checkedId();
}


void InvisibleButtonGroup::addButton(QAbstractButton* button, int id) {
  d->mGroup->addButton(button, id);
}


void InvisibleButtonGroup::setSelected(int id) {
  QAbstractButton* button = d->mGroup->button(id);
  if (button) {
    button->setChecked(true);
  }
}
