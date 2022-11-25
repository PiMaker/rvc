################################################################################
#
# bat
#
################################################################################

BAT_VERSION = 0.19.0
BAT_SITE = $(call github,sharkdp,bat,v$(BAT_VERSION))
BAT_LICENSE = Apache-2.0 or MIT
BAT_LICENSE_FILES = LICENSE-APACHE LICENSE-MIT

$(eval $(cargo-package))
