#ifndef HUMANIZE_H
#define HUMANIZE_H


#include <QString>


/*
 * Helpers class for formatting values to human friendly versions
 */
class Humanize
{
public:
    Humanize();
    ~Humanize();

    static QString size(qint64 size);
    static QString duration(qint64 duration, QString inputUnit = "ms", QString keepFrom = "");
    static QString percentage(double percent);
    static QString temperature(qint64 temp);
};

#endif // HUMANIZE_H
