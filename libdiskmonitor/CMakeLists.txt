set(LIBDISKMONITOR_SRCS
  types.cpp
  storageunit.cpp
  drive.cpp
  drivemonitor.cpp
  mdraid.cpp
  mdraidmonitor.cpp
  udisks2wrapper.cpp
)

add_library( libdiskmonitor STATIC ${LIBDISKMONITOR_SRCS} )

target_link_libraries( libdiskmonitor
  Qt5::Core
  Qt5::DBus
  KF5::I18n
)

