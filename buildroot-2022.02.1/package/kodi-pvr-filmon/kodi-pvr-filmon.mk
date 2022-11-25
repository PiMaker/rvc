################################################################################
#
# kodi-pvr-filmon
#
################################################################################

KODI_PVR_FILMON_VERSION = 19.0.1-Matrix
KODI_PVR_FILMON_SITE = $(call github,kodi-pvr,pvr.filmon,$(KODI_PVR_FILMON_VERSION))
KODI_PVR_FILMON_LICENSE = GPL-2.0+
KODI_PVR_FILMON_LICENSE_FILES = LICENSE.md
KODI_PVR_FILMON_DEPENDENCIES = jsoncpp kodi

$(eval $(cmake-package))
