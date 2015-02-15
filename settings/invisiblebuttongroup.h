#ifndef INVISIBLEBUTTONGROUP_H
#define INVISIBLEBUTTONGROUP_H

#include <QWidget>
#include <QButtonGroup>
#include <QAbstractButton>


class QAbstractButton;

namespace Settings {

  class InvisibleButtonGroupPrivate;
  class InvisibleButtonGroup : public QWidget {
    Q_OBJECT
    Q_PROPERTY(int current READ selected WRITE setSelected)
  public:
    explicit InvisibleButtonGroup(QWidget* parent = 0);
    ~InvisibleButtonGroup();

    int selected() const;

    void addButton(QAbstractButton* button, int id);

  public Q_SLOTS:
    void setSelected(int id);

  Q_SIGNALS:
    void selectionChanged(int id);

  private:
    InvisibleButtonGroupPrivate* const d;
  };


  class InvisibleButtonGroupPrivate {
  public:
    QButtonGroup* mGroup;
  };

}

#endif /* INVISIBLEBUTTONGROUP_H */
