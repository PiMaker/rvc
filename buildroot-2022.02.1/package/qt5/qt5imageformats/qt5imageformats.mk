################################################################################
#
# qt5imageformats
#
################################################################################

QT5IMAGEFORMATS_VERSION = cb82c74310837fe4e832c8ab72176a5d63e4355f
QT5IMAGEFORMATS_SITE = $(QT5_SITE)/qtimageformats/-/archive/$(QT5IMAGEFORMATS_VERSION)
QT5IMAGEFORMATS_SOURCE = qtimageformats-$(QT5IMAGEFORMATS_VERSION).tar.bz2
QT5IMAGEFORMATS_INSTALL_STAGING = YES
QT5IMAGEFORMATS_SYNC_QT_HEADERS = YES

QT5IMAGEFORMATS_LICENSE = GPL-2.0+ or LGPL-3.0, GPL-3.0 with exception(tools), GFDL-1.3 (docs)
QT5IMAGEFORMATS_LICENSE_FILES = LICENSE.GPLv2 LICENSE.GPLv3 LICENSE.GPL3-EXCEPT LICENSE.LGPLv3 LICENSE.FDL

$(eval $(qmake-package))
