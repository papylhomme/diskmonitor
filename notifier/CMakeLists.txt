set(NOTIFIER_SRCS
  iconsprovider.cpp
  storageunitqmlmodel.cpp
  storageunitmonitor.cpp
  qmlplugins.cpp
)

add_definitions(-DTRANSLATION_DOMAIN="plasma_applet_org.papylhomme.diskmonitor")

add_library(diskmonitor_qmlplugins SHARED ${NOTIFIER_SRCS})

target_link_libraries(diskmonitor_qmlplugins
  libdiskmonitor
  Qt5::Core
  Qt5::DBus
  Qt5::Quick
  KF5::I18n
  KF5::Notifications
)


install(TARGETS diskmonitor_qmlplugins DESTINATION ${QML_INSTALL_DIR}/org/papylhomme/diskmonitor)
install(FILES qmldir DESTINATION ${QML_INSTALL_DIR}/org/papylhomme/diskmonitor)
install(FILES diskmonitor.notifyrc DESTINATION ${KNOTIFYRC_INSTALL_DIR})

add_subdirectory( applet )
