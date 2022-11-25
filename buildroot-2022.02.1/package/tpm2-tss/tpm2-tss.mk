################################################################################
#
# tpm2-tss
#
################################################################################

TPM2_TSS_VERSION = 3.1.0
TPM2_TSS_SITE = https://github.com/tpm2-software/tpm2-tss/releases/download/$(TPM2_TSS_VERSION)
TPM2_TSS_LICENSE = BSD-2-Clause
TPM2_TSS_LICENSE_FILES = LICENSE
TPM2_TSS_CPE_ID_VENDOR = tpm2_software_stack_project
TPM2_TSS_CPE_ID_PRODUCT = tpm2_software_stack
TPM2_TSS_INSTALL_STAGING = YES
TPM2_TSS_DEPENDENCIES = openssl host-pkgconf

# 0001-configure-Only-use-CXX-when-fuzzing.patch
TPM2_TSS_AUTORECONF = YES

# systemd-sysusers and systemd-tmpfiles are only used at install time
# to trigger the creation of users adn tmpfiles, which we do not care
# about at build time. groupadd, useradd, and setfacl are used in the
# fallback path when systemd-sysusers or systemd-tmpfiles are missing
# and their failure is ignored anyway.
TPM2_TSS_CONF_OPTS = \
	ac_cv_prog_result_groupadd=yes \
	ac_cv_prog_result_setfacl=yes \
	ac_cv_prog_systemd_sysusers=no \
	ac_cv_prog_systemd_tmpfiles=no \
	ac_cv_prog_result_useradd=yes \
	--with-crypto=ossl \
	--disable-doxygen-doc \
	--disable-defaultflags

# uses C99 code but forgets to pass -std=c99 when --disable-defaultflags is used
TPM2_TSS_CONF_ENV += CFLAGS="$(TARGET_CFLAGS) -std=c99"

ifeq ($(BR2_PACKAGE_TPM2_TSS_FAPI),y)
TPM2_TSS_DEPENDENCIES += json-c libcurl
TPM2_TSS_CONF_OPTS += --enable-fapi
else
TPM2_TSS_CONF_OPTS += --disable-fapi
endif

$(eval $(autotools-package))
