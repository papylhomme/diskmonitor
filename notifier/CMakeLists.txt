set(NOTIFIER_SRCS
  storageunitqmlmodel.cpp
  iconprovider.cpp
  qmlplugins.cpp
)

add_library(diskmonitor_qmlplugins SHARED ${NOTIFIER_SRCS})

target_link_libraries(diskmonitor_qmlplugins
  libdiskmonitor
  Qt5::Core
  Qt5::DBus
  Qt5::Quick
)


install(TARGETS diskmonitor_qmlplugins DESTINATION ${QML_INSTALL_DIR}/org/papylhomme/diskmonitor)
install(FILES qmldir DESTINATION ${QML_INSTALL_DIR}/org/papylhomme/diskmonitor)

add_subdirectory( applet )
