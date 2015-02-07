#include "humanize.h"

#include <QStringList>


/*
 *
 */
Humanize::Humanize()
{

}


/*
 *
 */
Humanize::~Humanize()
{

}



/*
 * Format a size given in octet
 */
QString Humanize::size(qint64 size)
{
  float num = size;
  QStringList list;
  list << "KB" << "MB" << "GB" << "TB";

  QStringListIterator i(list);
  QString unit("bytes");

  while(num >= 1024.0 && i.hasNext())
   {
      unit = i.next();
      num /= 1024.0;
  }

  return QString().setNum(num, 'f', 2) + " " + unit;
}



/*
 * Format a duration given in unit inputUnit, keeping only units starting
 * from keepFrom
 *
 * available units are 'us', 'ms', 's', 'm', 'h' and 'd'
 */
QString Humanize::duration(qint64 duration, QString inputUnit, QString keepFrom)
{
  QStringList units;
  units << "us" << "ms" << "s" << "m" << "h" << "d";
  QList<int> unitAmount;
  unitAmount << 1000 << 1000 << 60 << 60 << 24 << 1;


  QStringList res;

  int idx = units.indexOf(inputUnit);
  int keepFromIdx = units.indexOf(keepFrom);

  if(idx == -1)
    qFatal("Humanize::duration:  Unknown input unit");

  int currentAmount = unitAmount.first();
  QString unit = units.first();

  while(idx < units.size() && duration >= currentAmount) {
    int r = duration % currentAmount;
    duration /= currentAmount;

    if(r > 0 && idx >= keepFromIdx)
      res.push_front(QString::number(r) + " " + unit);

    if(++idx == units.size())
      break;

    unit = units.at(idx);
    currentAmount = unitAmount.at(idx);
  }

  res.push_front(QString::number(duration) + " " + unit);
  return res.join(" ");
}



/*
 * Format a percentage given as a double between 0.0 and 1.0
 */
QString Humanize::percentage(double percent)
{
  return QString().setNum(percent * 100, 'f', 2) + " %";
}

