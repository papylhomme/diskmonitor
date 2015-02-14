project(diskmonitor)

cmake_minimum_required(VERSION 2.8.12)
set (QT_MIN_VERSION "5.2.0")

find_package(ECM 1.6.0 REQUIRED NO_MODULE)
set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

add_definitions(-DTRANSLATION_DOMAIN="diskmonitor")

include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)
include(ECMMarkAsTest)
include(FeatureSummary)

find_package (Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
  Core
  DBus
  Widgets
  Quick
)

find_package(KF5 REQUIRED COMPONENTS
  CoreAddons
  I18n
  IconThemes
  XmlGui
  Notifications
  ConfigWidgets
  Plasma
)


kde_enable_exceptions()


include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/libdiskmonitor )

add_subdirectory( libdiskmonitor )
add_subdirectory( settings )
add_subdirectory( app )
add_subdirectory( notifier )


feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

