include $(TOPDIR)/rules.mk

PKG_NAME:=gcompat
PKG_VERSION:=1.1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://git.adelielinux.org/adelie/gcompat/-/archive/$(PKG_VERSION)/
PKG_HASH:=82e56d2ecda3f11a93efe61001394a6e5db39c91127d0812d7ad5b0bda558010

PKG_MAINTAINER:=JJm2473 <jjm2473@gmail.com>
PKG_LICENSE:=NCSA open source license

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/gcompat
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=gcompat for musl
  DEPENDS:=@USE_MUSL
  URL:=https://git.adelielinux.org/adelie/gcompat
  ABI_VERSION:=0
endef

define Package/gcompat/description
 A library which provides glibc-compatible APIs for use on musl libc systems.
 add fcntl64
 add pthread_cond_clockwait
endef

TARGET_CFLAGS += -I$(BUILD_DIR_TOOLCHAIN)/musl/src/internal \
	-I$(BUILD_DIR_TOOLCHAIN)/musl/arch/$(ARCH)

MAKE_FLAGS += \
	LINKER_PATH=/lib/ld-musl-$(ARCH).so.1 \
	LOADER_NAME=ld-linux-$(ARCH).so.1

define Build/InstallDev
	$(INSTALL_DIR) $(1)/lib/
	$(CP) $(PKG_INSTALL_DIR)/lib/ld-linux-$(ARCH).so.1 $(1)/lib/
	$(CP) $(PKG_INSTALL_DIR)/lib/libgcompat.so.* $(1)/lib/
endef

define Package/gcompat/install
	$(INSTALL_DIR) $(1)/lib
	$(CP) $(PKG_INSTALL_DIR)/lib/ld-linux-$(ARCH).so.1 $(1)/lib/
	$(CP) $(PKG_INSTALL_DIR)/lib/libgcompat.so.* $(1)/lib/
endef

$(eval $(call BuildPackage,gcompat))
