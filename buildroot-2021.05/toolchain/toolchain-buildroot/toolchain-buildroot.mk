################################################################################
#
# toolchain-buildroot
#
################################################################################

BR_LIBC = $(call qstrip,$(BR2_TOOLCHAIN_BUILDROOT_LIBC))

# Triggering the build of the host-gcc-final will automatically do the
# build of binutils, uClibc, kernel headers and all the intermediate
# gcc steps.

TOOLCHAIN_BUILDROOT_DEPENDENCIES = host-gcc-final

TOOLCHAIN_BUILDROOT_ADD_TOOLCHAIN_DEPENDENCY = NO

$(eval $(virtual-package))
