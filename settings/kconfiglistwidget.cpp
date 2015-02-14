#include "kconfiglistwidget.h"

#include <KConfigDialogManager>



/*
 * Constructor
 */
KConfigListWidget::KConfigListWidget(QWidget* parent) : QListWidget(parent)
{
  //register change signal to KConfigDialogManager
  if(!KConfigDialogManager::changedMap() -> contains("KConfigListWidget"))
    KConfigDialogManager::changedMap() -> insert("KConfigListWidget", SIGNAL(changed(const QList<int>&)));
}



/*
 * Destructor
 */
KConfigListWidget::~KConfigListWidget()
{

}



/*
 * Property getter for KConfigDialogManager
 */
QList<int> KConfigListWidget::items()
{
  QList<int> res;

  for(int i = 0; i < count(); i++)
    res << item(i) -> text().toInt();

  return res;
}



/*
 * Property setter for KConfigDialogManager
 */
void KConfigListWidget::setItems(const QList<int>& items)
{
  QStringList newItems;


  foreach(int i, items)
    newItems << QString::number(i);

  clear();
  addItems(newItems);
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::addItem(QListWidgetItem* item)
{
  QListWidget::addItem(item);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::addItem(const QString& label)
{
  QListWidget::addItem(label);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::addItems(const QStringList& labels)
{
  QListWidget::addItems(labels);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::insertItem(int row, QListWidgetItem* item)
{
  QListWidget::insertItem(row, item);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::insertItem(int row, const QString& label)
{
  QListWidget::insertItem(row, label);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::insertItems(int row, const QStringList& labels)
{
  QListWidget::insertItems(row, labels);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::removeItemWidget(QListWidgetItem* item)
{
  QListWidget::removeItemWidget(item);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
QListWidgetItem*KConfigListWidget::takeItem(int row)
{
  QListWidgetItem* item = QListWidget::takeItem(row);
  emit changed(items());
  return item;
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::clear()
{
  QListWidget::clear();
  emit changed(items());
}


