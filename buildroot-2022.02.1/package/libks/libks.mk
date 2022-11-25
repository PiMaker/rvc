################################################################################
#
# libks
#
################################################################################

LIBKS_VERSION = 1.7.0
LIBKS_SITE = $(call github,signalwire,libks,v$(LIBKS_VERSION))
LIBKS_LICENSE = MIT
LIBKS_LICENSE_FILES = copyright
LIBKS_INSTALL_STAGING = YES
LIBKS_DEPENDENCIES = openssl util-linux

$(eval $(cmake-package))
