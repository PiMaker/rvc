################################################################################
#
# wlroots
#
################################################################################

WLROOTS_VERSION = 0.12.0
WLROOTS_SITE = https://github.com/swaywm/wlroots/releases/download/$(WLROOTS_VERSION)
WLROOTS_LICENSE = MIT
WLROOTS_LICENSE_FILES = LICENSE
WLROOTS_INSTALL_STAGING = YES

WLROOTS_DEPENDENCIES = \
	host-pkgconf \
	host-wayland \
	libinput \
	libxkbcommon \
	libegl \
	libgles \
	pixman \
	udev \
	wayland \
	wayland-protocols

WLROOTS_CONF_OPTS = -Dexamples=false -Dxcb-errors=disabled -Dlibseat=disabled

ifeq ($(BR2_PACKAGE_FFMPEG),y)
WLROOTS_DEPENDENCIES += ffmpeg
endif

ifeq ($(BR2_PACKAGE_LIBPNG),y)
WLROOTS_DEPENDENCIES += libpng
endif

ifeq ($(BR2_PACKAGE_SYSTEMD_LOGIND),y)
WLROOTS_CONF_OPTS += -Dlogind=enabled -Dlogind-provider=systemd
WLROOTS_DEPENDENCIES += systemd
else
WLROOTS_CONF_OPTS += -Dlogind=disabled
endif

ifeq ($(BR2_PACKAGE_WLROOTS_X11),y)
WLROOTS_CONF_OPTS += -Dx11-backend=enabled
WLROOTS_DEPENDENCIES += xlib_libX11
else
WLROOTS_CONF_OPTS += -Dx11-backend=disabled
endif

ifeq ($(BR2_PACKAGE_LIBXCB),y)
WLROOTS_CONF_OPTS += -Dxwayland=enabled
WLROOTS_DEPENDENCIES += libxcb
else
WLROOTS_CONF_OPTS += -Dxwayland=disabled
endif

ifeq ($(BR2_PACKAGE_XCB_UTIL_WM),y)
WLROOTS_CONF_OPTS += -Dxcb-icccm=enabled
WLROOTS_DEPENDENCIES += xcb-util-wm
else
WLROOTS_CONF_OPTS += -Dxcb-icccm=disabled
endif

$(eval $(meson-package))
