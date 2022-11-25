################################################################################
#
# polkit
#
################################################################################

POLKIT_VERSION = a2bf5c9c83b6ae46cbd5c779d3055bff81ded683
POLKIT_SITE = https://gitlab.freedesktop.org/polkit/polkit/-/archive/$(POLKIT_VERSION)
POLKIT_LICENSE = GPL-2.0
POLKIT_LICENSE_FILES = COPYING
POLKIT_CPE_ID_VENDOR = polkit_project
POLKIT_INSTALL_STAGING = YES

# Fix was comitted in a2bf5c9c83b6ae46cbd5c779d3055bff81ded683
POLKIT_IGNORE_CVE = CVE-2021-4034

POLKIT_DEPENDENCIES = \
	duktape libglib2 host-intltool expat $(TARGET_NLS_DEPENDENCIES)

POLKIT_SELINUX_MODULES = policykit

POLKIT_LDFLAGS = $(TARGET_NLS_LIBS)

POLKIT_CONF_OPTS = \
	-Dman=false \
	-Dexamples=false \
	-Dsession_tracking=ConsoleKit \
	-Djs_engine=duktape

ifeq ($(BR2_PACKAGE_GOBJECT_INTROSPECTION),y)
POLKIT_CONF_OPTS += -Dintrospection=true
POLKIT_DEPENDENCIES += gobject-introspection
else
POLKIT_CONF_OPTS += -Dintrospection=false
endif

ifeq ($(BR2_PACKAGE_LINUX_PAM),y)
POLKIT_DEPENDENCIES += linux-pam
POLKIT_CONF_OPTS += -Dauthfw=pam
else
POLKIT_CONF_OPTS += -Dauthfw=shadow
endif

# polkit.{its,loc} are needed for gvfs and must be installed in $(HOST_DIR)
# and not $(STAGING_DIR)
define POLKIT_INSTALL_ITS
	$(INSTALL) -D -m 644 $(@D)/gettext/its/polkit.its \
		$(HOST_DIR)/share/gettext/its/polkit.its
	$(INSTALL) -D -m 644 $(@D)/gettext/its/polkit.loc \
		$(HOST_DIR)/share/gettext/its/polkit.loc
endef
POLKIT_POST_INSTALL_TARGET_HOOKS += POLKIT_INSTALL_ITS

define POLKIT_USERS
	polkitd -1 polkitd -1 * - - - Polkit Daemon
endef

define POLKIT_PERMISSIONS
	/etc/polkit-1 r 750 root polkitd - - - - -
	/usr/share/polkit-1 r 750 root polkitd - - - - -
	/usr/bin/pkexec f 4755 root root - - - - -
endef

define POLKIT_INSTALL_INIT_SYSTEMD
	$(INSTALL) -D -m 644 $(POLKIT_PKGDIR)/polkit.service \
		$(TARGET_DIR)/usr/lib/systemd/system/polkit.service

endef

define POLKIT_INSTALL_INIT_SYSV
	$(INSTALL) -D -m 0755 package/polkit/S50polkit \
		$(TARGET_DIR)/etc/init.d/S50polkit
endef

$(eval $(meson-package))
