################################################################################
# Cargo package infrastructure
#
# This file implements an infrastructure that eases development of package
# .mk files for Cargo packages. It should be used for all packages that use
# Cargo as their build system.
#
# See the Buildroot documentation for details on the usage of this
# infrastructure
#
# In terms of implementation, this Cargo infrastructure requires the .mk file
# to only specify metadata information about the package: name, version,
# download URL, etc.
#
# We still allow the package .mk file to override what the different steps
# are doing, if needed. For example, if <PKG>_BUILD_CMDS is already defined,
# it is used as the list of commands to perform to build the package,
# instead of the default Cargo behaviour. The package can also define some
# post operation hooks.
#
################################################################################

PKG_COMMON_CARGO_ENV = \
	CARGO_HOME=$(HOST_DIR)/share/cargo

# __CARGO_TEST_CHANNEL_OVERRIDE_DO_NOT_USE_THIS is needed to allow
# passing the -Z target-applies-to-host, which is needed together with
# CARGO_TARGET_APPLIES_TO_HOST to fix build problems when target
# architecture == host architecture.

# __CARGO_TEST_CHANNEL_OVERRIDE_DO_NOT_USE_THIS="nightly" is to allow
# using nighly features on stable releases, i.e features that are not
# yet considered stable.
#
# CARGO_UNSTABLE_TARGET_APPLIES_TO_HOST="true" "enables the nightly
# configuration option target-applies-to-host value to be set
#
# CARGO_TARGET_APPLIES_TO_HOST="false" is actually setting the value
# for this feature, which we disable, to make sure builds where target
# arch == host arch work correctly
PKG_CARGO_ENV = \
	$(PKG_COMMON_CARGO_ENV) \
	__CARGO_TEST_CHANNEL_OVERRIDE_DO_NOT_USE_THIS="nightly" \
	CARGO_UNSTABLE_TARGET_APPLIES_TO_HOST="true" \
	CARGO_TARGET_APPLIES_TO_HOST="false" \
	CARGO_BUILD_TARGET="$(RUSTC_TARGET_NAME)" \
	CARGO_TARGET_$(call UPPERCASE,$(RUSTC_TARGET_NAME))_LINKER=$(notdir $(TARGET_CROSS))gcc

#
# This is a workaround for https://github.com/rust-lang/compiler-builtins/issues/420
# and should be removed when fixed upstream
#
ifeq ($(NORMALIZED_ARCH),arm)
	PKG_CARGO_ENV += RUSTFLAGS="-Clink-arg=-Wl,--allow-multiple-definition"
endif

HOST_PKG_CARGO_ENV = \
	$(PKG_COMMON_CARGO_ENV)

################################################################################
# inner-cargo-package -- defines how the configuration, compilation and
# installation of a cargo package should be done, implements a few hooks
# to tune the build process for cargo specifities and calls the generic
# package infrastructure to generate the necessary make targets
#
#  argument 1 is the lowercase package name
#  argument 2 is the uppercase package name, including a HOST_ prefix
#             for host packages
#  argument 3 is the uppercase package name, without the HOST_ prefix
#             for host packages
#  argument 4 is the type (target or host)
################################################################################

define inner-cargo-package

# We need host-rustc to run cargo at download time (for vendoring),
# and at build and install time.
$(2)_DOWNLOAD_DEPENDENCIES += host-rustc
$(2)_DEPENDENCIES += host-rustc

$(2)_DOWNLOAD_POST_PROCESS = cargo
$(2)_DL_ENV += CARGO_HOME=$$(HOST_DIR)/share/cargo

# If building in a sub directory, use that to find the Cargo.toml
ifneq ($$($(2)_SUBDIR),)
$(2)_DL_ENV += BR_CARGO_MANIFEST_PATH=$$($(2)_SUBDIR)/Cargo.toml
endif

# Due to vendoring, it is pretty likely that not all licenses are
# listed in <pkg>_LICENSE.
$(2)_LICENSE += , vendored dependencies licenses probably not listed

# Note: in all the steps below, we "cd" into the build directory to
# execute the "cargo" tool instead of passing $(@D)/Cargo.toml as the
# manifest-path. Indeed while the latter seems to work, it in fact
# breaks in subtle ways as the way cargo searches for its
# configuration file is based (among other rules) on the current
# directory. This means that if cargo is started outside of a package
# directory, its configuration file will not be taken into account.
#
# Also, we pass:
#  * --offline to prevent cargo from downloading anything: all
#    dependencies should have been built by the download post
#    process logic
#  * --locked to force cargo to use the Cargo.lock file, which ensures
#    that a fixed set of dependency versions is used

#
# Build step. Only define it if not already defined by the package .mk
# file.
#
ifndef $(2)_BUILD_CMDS
ifeq ($(4),target)
define $(2)_BUILD_CMDS
	cd $$($$(PKG)_SRCDIR) && \
	$$(TARGET_MAKE_ENV) \
		$$(TARGET_CONFIGURE_OPTS) \
		$$(PKG_CARGO_ENV) \
		$$($(2)_CARGO_ENV) \
		cargo build \
			--offline \
			$$(if $$(BR2_ENABLE_DEBUG),,--release) \
			--manifest-path Cargo.toml \
			--locked \
			$$($(2)_CARGO_BUILD_OPTS)
endef
else # ifeq ($(4),target)
define $(2)_BUILD_CMDS
	cd $$($$(PKG)_SRCDIR) && \
	$$(HOST_MAKE_ENV) \
		RUSTFLAGS="$$(addprefix -C link-args=,$$(HOST_LDFLAGS))" \
		$$(HOST_CONFIGURE_OPTS) \
		$$(HOST_PKG_CARGO_ENV) \
		$$($(2)_CARGO_ENV) \
		cargo build \
			--offline \
			--release \
			--manifest-path Cargo.toml \
			--locked \
			$$($(2)_CARGO_BUILD_OPTS)
endef
endif # ifeq ($(4),target)
endif # ifndef $(2)_BUILD_CMDS

#
# Target installation step. Only define it if not already defined by
# the package .mk file.
#
ifndef $(2)_INSTALL_TARGET_CMDS
define $(2)_INSTALL_TARGET_CMDS
	cd $$($$(PKG)_SRCDIR) && \
	$$(TARGET_MAKE_ENV) \
		$$(TARGET_CONFIGURE_OPTS) \
		$$(PKG_CARGO_ENV) \
		$$($(2)_CARGO_ENV) \
		cargo install \
			--offline \
			--root $$(TARGET_DIR)/usr/ \
			--bins \
			--path ./ \
			--force \
			--locked \
			-Z target-applies-to-host \
			$$($(2)_CARGO_INSTALL_OPTS)
endef
endif

ifndef $(2)_INSTALL_CMDS
define $(2)_INSTALL_CMDS
	cd $$($$(PKG)_SRCDIR) && \
	$$(HOST_MAKE_ENV) \
		RUSTFLAGS="$$(addprefix -C link-args=,$$(HOST_LDFLAGS))" \
		$$(HOST_CONFIGURE_OPTS) \
		$$(HOST_PKG_CARGO_ENV) \
		$$($(2)_CARGO_ENV) \
		cargo install \
			--offline \
			--root $$(HOST_DIR) \
			--bins \
			--path ./ \
			--force \
			--locked \
			$$($(2)_CARGO_INSTALL_OPTS)
endef
endif

# Call the generic package infrastructure to generate the necessary
# make targets
$(call inner-generic-package,$(1),$(2),$(3),$(4))

endef

################################################################################
# cargo-package -- the target generator macro for Cargo packages
################################################################################

cargo-package = $(call inner-cargo-package,$(pkgname),$(call UPPERCASE,$(pkgname)),$(call UPPERCASE,$(pkgname)),target)
host-cargo-package = $(call inner-cargo-package,host-$(pkgname),$(call UPPERCASE,host-$(pkgname)),$(call UPPERCASE,$(pkgname)),host)
