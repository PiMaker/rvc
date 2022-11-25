################################################################################
#
# qpdf
#
################################################################################

QPDF_VERSION = 10.5.0
QPDF_SITE = http://downloads.sourceforge.net/project/qpdf/qpdf/$(QPDF_VERSION)
QPDF_INSTALL_STAGING = YES
QPDF_LICENSE = Apache-2.0 or Artistic-2.0
QPDF_LICENSE_FILES = LICENSE.txt Artistic-2.0
QPDF_CPE_ID_VENDOR = qpdf_project
QPDF_DEPENDENCIES = host-pkgconf zlib jpeg

QPDF_CONF_OPTS = --with-random=/dev/urandom

ifeq ($(BR2_USE_WCHAR),)
QPDF_CONF_ENV += CXXFLAGS="$(TARGET_CXXFLAGS) -DQPDF_NO_WCHAR_T"
endif

ifeq ($(BR2_PACKAGE_GNUTLS),y)
QPDF_CONF_OPTS += --enable-crypto-gnutls
QPDF_DEPENDENCIES += gnutls
else
QPDF_CONF_OPTS += --disable-crypto-gnutls
endif

ifeq ($(BR2_PACKAGE_OPENSSL),y)
QPDF_CONF_OPTS += --enable-crypto-openssl
QPDF_DEPENDENCIES += openssl
else
QPDF_CONF_OPTS += --disable-crypto-openssl
endif

$(eval $(autotools-package))
