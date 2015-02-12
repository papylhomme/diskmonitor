#include "iconprovider.h"

/*
 * Constructor
 */
IconProvider::IconProvider(QObject *parent) : QObject(parent)
{

}


/*
 * Destructor
 */
IconProvider::~IconProvider()
{

}



/*
 * Get the healthy status icon name
 */
QString IconProvider::healthy() const
{
  return "face-cool";
}



/*
 * Get the failing status icon name
 */
QString IconProvider::failing() const
{
  return "face-sick";
}



/*
 * Get the unknown status icon name
 */
QString IconProvider::unknown() const
{
  return "face-confused";
}

