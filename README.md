# DisKMonitor
KDE tools to monitor SMART devices and MDRaid health status. Features a full application and a Plasma applet.

# Installation

## Arch Linux

DisKMonitor is available on the AUR:
* `diskmonitor` for the latest release
* `diskmonitor-git` for the current master branch

## Kubuntu

Thanks to @hleroy, DiskMonitor is also available as a PPA for KUbuntu users. You can install the latest version using:

    sudo add-apt-repository ppa:hleroy/kde-diskmonitor
    sudo apt update
    sudo apt install diskmonitor

## Compilation from sources

### Dependencies
* **Qt**
  * qt5-base
  * qt5-declarative
* **KF5**
  * kwindowsystem
  * kiconthemes
  * knotifications
  * kxmlgui
  * plasma-framework
* **UDisks2** >= 2.1

Additionally, **cmake** and **extra-cmake-modules** are required to build the package. 

### Build
    mkdir build && cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=$(kf5-config --prefix) \
           -DCMAKE_BUILD_TYPE=Release \
           -DKDE_INSTALL_USE_QT_SYS_PATHS=ON

    make

# Features

## Application

- Display S.M.A.R.T. attributes for harddrives supporting it
- Start and monitor progress of S.M.A.R.T. Short and Extended self test 

![SMART properties](https://github.com/papylhomme/diskmonitor/blob/gh-pages/screenshots/screenshot2.png)

- Display properties for MDRaid arrays
- Start and monitor progress of data scrubbing on MDRaid arrays

![MDRaid properties](https://github.com/papylhomme/diskmonitor/blob/gh-pages/screenshots/screenshot1.png)

## Applet

- Display basic health status for storage units
- Can be used on the desktop, on a panel or as a systray icon (see systray settings to activate)
- Use KDE notification for health status change
- Highly configurable interface

![Applet - Desktop](https://github.com/papylhomme/diskmonitor/blob/gh-pages/screenshots/applet1.png)

![Applet - Tray](https://github.com/papylhomme/diskmonitor/blob/gh-pages/screenshots/applet2.png)

# Getting involved

If you like this software, contribution is welcome! You can submit new features or bugfixes using github pull request. You can also help translating DisKMonitor in your language using Transifex at https://www.transifex.com/orgpapylhomme/diskmonitor/

# Test health status change

The easiest way to test the monitoring is by using a "fake" raid array. The idea is to create a small array
using loop devices :

```
# you may need to load the 'loop' module
modprobe loop

# then create two files for use as block devices
dd if=/dev/zero of=/root/raid/r0 bs=1M count=20
dd if=/dev/zero of=/root/raid/r1 bs=1M count=20

# attach the files to loop devices
losetup /dev/loop0 /root/raid/r0
losetup /dev/loop1 /root/raid/r1

# to check everything went ok
losetup -a

# now create a new raid array
mdadm --create /dev/md0 --level=1 --raid-devices=2 /dev/loop0 /dev/loop1

# check the raid status
cat /proc/mdstat
```

Then you can fail and restore raid devices at will :
```
# fail the loop0 device
mdadm --manage /dev/md0 -f /dev/loop0

# restore the raid by removing and readding the device
mdadm --manage /dev/md0 -r /dev/loop0
mdadm --manage /dev/md0 -a /dev/loop0
```
