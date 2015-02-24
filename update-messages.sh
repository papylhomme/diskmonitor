#!/bin/sh
BASEDIR=`pwd`  # root of translatable sources
PROJECT="diskmonitor"  # project name
APPLET="plasma_applet_org.papylhomme.diskmonitor"  # project name
BUGADDR="https://github.com/papylhomme/diskmonitor/issues"  # MSGID-Bugs
WDIR="${BASEDIR}/translations"    # working dir
 
 
echo "Preparing rc files"
# we use simple sorting to make sure the lines do not jump around too much from system to system
find ./app -name '*.rc' -o -name '*.ui' -o -name '*.kcfg' | sort > ${WDIR}/app/rcfiles.list
find ./settings -name '*.rc' -o -name '*.ui' -o -name '*.kcfg' | sort >> ${WDIR}/app/rcfiles.list
xargs --arg-file=${WDIR}/app/rcfiles.list extractrc > ${WDIR}/app/rc.cpp

# additional string for KAboutData
echo 'i18nc("NAME OF TRANSLATORS","Your names");' >> ${WDIR}/app/rc.cpp
echo 'i18nc("EMAIL OF TRANSLATORS","Your emails");' >> ${WDIR}/app/rc.cpp
echo "Done preparing rc files"
 
 
echo "Extracting messages"
# see above on sorting

#app
find ./app -name '*.cpp' -o -name '*.h' -o -name '*.c' | sort > ${WDIR}/app/infiles.list
find ./settings -name '*.cpp' -o -name '*.h' -o -name '*.c' | sort >> ${WDIR}/app/infiles.list
echo "rc.cpp" >> ${WDIR}/app/infiles.list

find ./notifier -name '*.cpp' -o -name '*.h' -o -name '*.c' -o -name '*.qml' | sort > ${WDIR}/applet/infiles.list

cd ${WDIR}
xgettext --from-code=UTF-8 -C -kde -ci18n -ki18n:1 -ki18nc:1c,2 -ki18np:1,2 -ki18ncp:1c,2,3 -ktr2i18n:1 \
  -kI18N_NOOP:1 -kI18N_NOOP2:1c,2 -kaliasLocale -kki18n:1 -kki18nc:1c,2 -kki18np:1,2 -kki18ncp:1c,2,3 \
  --msgid-bugs-address="${BUGADDR}" \
  --files-from=app/infiles.list -D ${BASEDIR} -D ${WDIR}/app -o app/${PROJECT}.pot || { echo "error while calling xgettext. aborting."; exit 1; }

xgettext --from-code=UTF-8 -C -kde -ci18n -ki18n:1 -ki18nc:1c,2 -ki18np:1,2 -ki18ncp:1c,2,3 -ktr2i18n:1 \
  -kI18N_NOOP:1 -kI18N_NOOP2:1c,2 -kaliasLocale -kki18n:1 -kki18nc:1c,2 -kki18np:1,2 -kki18ncp:1c,2,3 \
  --msgid-bugs-address="${BUGADDR}" \
  --files-from=applet/infiles.list -D ${BASEDIR} -D ${WDIR}/applet -o applet/${APPLET}.pot || { echo "error while calling xgettext. aborting."; exit 1; }
echo "Done extracting messages"
 
 
echo "Merging translations"
catalogs=`find ./app -name '*.po'`
for cat in $catalogs; do
  echo $cat
  msgmerge -o $cat.new $cat app/${PROJECT}.pot
  mv $cat.new $cat
done
catalogs=`find ./applet -name '*.po'`
for cat in $catalogs; do
  echo $cat
  msgmerge -o $cat.new $cat applet/${APPLET}.pot
  mv $cat.new $cat
done

echo "Done merging translations"
 
 
echo "Cleaning up"
cd ${WDIR}
rm app/rcfiles.list
rm app/infiles.list
rm app/rc.cpp
rm applet/infiles.list
echo "Done"
