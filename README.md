# DisKMonitor
KDE tools to monitor SMART devices and MDRaid health status. Features a full application and a Plasma applet.

# Requirements
* **KF5**
* **UDisks2** >= 2.1

# Build
    mkdir build && cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=$(kf5-config --prefix) \
           -DCMAKE_BUILD_TYPE=Release \
           -DKDE_INSTALL_USE_QT_SYS_PATHS=ON

    make

# Screenshots

DisKMonitor displaying MDRaid properties
![MDRaid properties](https://github.com/papylhomme/diskmonitor/blob/gh-pages/screenshots/screenshot1.png)


DisKMonitor displaying SMART properties
![SMART properties](https://github.com/papylhomme/diskmonitor/blob/gh-pages/screenshots/screenshot2.png)


DisKMonitor applet on the desktop
![Applet - Desktop](https://github.com/papylhomme/diskmonitor/blob/gh-pages/screenshots/applet1.png)


DisKMonitor applet on the tray
![Applet - Tray](https://github.com/papylhomme/diskmonitor/blob/gh-pages/screenshots/applet2.png)




