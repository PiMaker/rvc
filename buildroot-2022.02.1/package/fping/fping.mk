################################################################################
#
# fping
#
################################################################################

FPING_VERSION = 5.1
FPING_SITE = http://fping.org/dist
FPING_LICENSE = BSD-like
FPING_LICENSE_FILES = COPYING
FPING_SELINUX_MODULES = netutils

$(eval $(autotools-package))
