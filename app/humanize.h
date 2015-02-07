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
    static QString duration(qint64 duration, QString inputUnit = "ms", QString keepFrom = "s");
    static QString percentage(double percent);
};

#endif // HUMANIZE_H
