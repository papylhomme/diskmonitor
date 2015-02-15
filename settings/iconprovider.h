#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QObject>


namespace Settings {

  /*
   * Component to provide icons depending on the configuration
   */
  class IconProvider : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QString healthy READ healthy NOTIFY healthyChanged)
    Q_PROPERTY(QString failing READ failing NOTIFY failingChanged)
    Q_PROPERTY(QString unknown READ unknown NOTIFY unknownChanged)

  public:
    explicit IconProvider(QObject *parent = 0);
    ~IconProvider();

    QString healthy() const;
    QString failing() const;
    QString unknown() const;

  signals:
    void healthyChanged();
    void failingChanged();
    void unknownChanged();

  public slots:
    void configChanged();
  };

}

#endif // ICONPROVIDER_H
