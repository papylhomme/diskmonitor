import QtQuick 2.0

Item {

  property string healthy: {
    if(plasmoid.configuration.iconsFaces)
      return "face-cool";
    else if(plasmoid.configuration.iconsDialog)
      return "dialog-ok";
    else
      return plasmoid.configuration.iconHealthy; 
  }

  property string failing: {
    if(plasmoid.configuration.iconsFaces)
      return "face-sick";
    else if(plasmoid.configuration.iconsDialog)
      return "dialog-error";
    else
      return plasmoid.configuration.iconFailing; 
  }

  property string unknown: {
    if(plasmoid.configuration.iconsFaces)
      return "face-confused";
    else if(plasmoid.configuration.iconsDialog)
      return "unknown";
    else
      return plasmoid.configuration.iconUnknown; 
  }


}

