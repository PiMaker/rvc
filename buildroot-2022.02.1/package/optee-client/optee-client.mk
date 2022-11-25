################################################################################
#
# optee-client
#
################################################################################

OPTEE_CLIENT_VERSION = 3.15.0
OPTEE_CLIENT_SITE = $(call github,OP-TEE,optee_client,$(OPTEE_CLIENT_VERSION))
OPTEE_CLIENT_LICENSE = BSD-2-Clause
OPTEE_CLIENT_LICENSE_FILES = LICENSE
OPTEE_CLIENT_INSTALL_STAGING = YES

OPTEE_CLIENT_CONF_OPTS = \
	-DCFG_TEE_FS_PARENT_PATH=$(BR2_PACKAGE_OPTEE_CLIENT_TEE_FS_PATH) \
	-DCFG_WERROR=OFF

ifeq ($(BR2_PACKAGE_OPTEE_CLIENT_RPMB_EMU),y)
OPTEE_CLIENT_CONF_OPTS += -DRPMB_EMU=ON
else
OPTEE_CLIENT_CONF_OPTS += -DRPMB_EMU=OFF
endif

ifeq ($(BR2_PACKAGE_OPTEE_CLIENT_SUPP_PLUGINS),y)
OPTEE_CLIENT_CONF_OPTS += -DCFG_TEE_SUPP_PLUGINS=ON
else
OPTEE_CLIENT_CONF_OPTS += -DCFG_TEE_SUPP_PLUGINS=OFF
endif

define OPTEE_CLIENT_INSTALL_INIT_SYSV
	$(INSTALL) -m 0755 -D $(OPTEE_CLIENT_PKGDIR)/S30optee \
		$(TARGET_DIR)/etc/init.d/S30optee
endef

$(eval $(cmake-package))
