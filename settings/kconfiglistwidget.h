#ifndef KCONFIGLISTWIDGET_H
#define KCONFIGLISTWIDGET_H

#include <QListWidget>

namespace Settings {

  /*
   * Wrapper around QListWidget providing support for KConfigDialogManager
   */
  class KConfigListWidget : public QListWidget
  {
    Q_OBJECT
    Q_PROPERTY( QList<int> items READ items WRITE setItems USER true )
  public:
    KConfigListWidget(QWidget* parent = NULL);
    ~KConfigListWidget();

    QList<int> items();
    void setItems(const QList<int>& items);

    void addItem(QListWidgetItem* item);
    void addItem(const QString &label);
    void addItems(const QStringList &labels);

    void insertItem(int row, QListWidgetItem* item);
    void insertItem(int row, const QString &label);
    void insertItems(int row, const QStringList &labels);

    void removeItemWidget(QListWidgetItem *item);
    QListWidgetItem* takeItem(int row);
    void clear();

  signals:
    void changed( const QList<int>& newItems );
  };

}

#endif // KCONFIGLISTWIDGET_H
