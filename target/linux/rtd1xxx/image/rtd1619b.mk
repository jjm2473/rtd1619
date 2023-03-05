define Device/rtd1619b
  FILESYSTEMS := squashfs ext4
  KERNEL := kernel-bin
  DEVICE_NAME := realtek
  DEVICE_VENDOR := Realtek
  DEVICE_DTS_DIR := $(DTS_DIR)/realtek
  DEVICE_DTS := rtd1619b-$(1) rtd1619b-rescue
  DEVICE_PACKAGES := nas
  PROFILES := Default $$(DEVICE_NAME)
  IMAGES := install.img
  IMAGE/install.img := rtkimg
  SOC := stark
  VIDEO_FW_NAME := bluecore.video.$$(SOC).zip
  VIDEO_FW3_NAME := bluecore.ve3.$$(SOC).zip
  SYSTEM_MAP_FILE := System.map.audio.$$(SOC)
  BOARD_NAME :=
  AUDIO_FW_NAME :=
  FLASH_SIZE :=
  CLEAR_OVERLAY := n
  IMAGE_FORMAT :=
  NAS_SUFFIX ?= nas
endef
DEVICE_VARS += AUDIO_FW_NAME VIDEO_FW_NAME SYSTEM_MAP_FILE BOARD_NAME FLASH_SIZE CLEAR_OVERLAY IMAGE_FORMAT NAS_SUFFIX
DEVICE_VARS += VIDEO_FW3_NAME

define Device/bleedingedge-emmc
  $(Device/rtd1619b)
  DEVICE_MODEL := BleedingEdge eMMC board
  DEVICE_PACKAGES += kmod-rtk-emmc kmod-rtk-tee
  BOARD_NAME := emmc
  AUDIO_FW_NAME := bluecore.audio.$$(SOC).PB.zip
  FLASH_SIZE := 8gb
  CLEAR_OVERLAY := y
endef

define Device/bleedingedge-emmc-2gb
  $(Device/bleedingedge-emmc)
  DEVICE_PACKAGES += kmod-rtk-codec
  DEVICE_VARIANT := 2GB
endef

TARGET_DEVICES += bleedingedge-emmc-2gb

# 加入 路由器需要的 依赖包.
DEFAULT_PACKAGES.rt1619b_with = \
kmod-rtl8125 kmod-rtl8152 kmod-rtkwifiu kmod-rtkwifiu-rtl8822cs kmod-rtkwifiu-rtl8852bs \
kmod-random-core kmod-lib-lz4 kmod-lib-lzo kmod-loop kmod-lib-crc16 kmod-lib-crc32 \
shortcut-fe \
ethtool rtk-bluecore curl etherwake netperf \
blkid blkdev fio hdparm \
keyutils resize2fs swap-utils tune2fs \
fdt-utils flock f2fsck lscpu lsof mount-utils \
usbutils usbids \
kmod-fs-ext4 \
kmod-fs-f2fs \
logrotate \
jshn \
netdata veth wireless-regdb \
pciutils \
iwinfo hostapd-utils hostapd-common wpa-cli wpad-mesh-openssl \
luci

define Device/bleedingedge-emmc-2gb-router
  $(Device/bleedingedge-emmc)
  DEVICE_MODEL += for Router
  DEVICE_PACKAGES += $(DEFAULT_PACKAGES.router) $(DEFAULT_PACKAGES.rt1619b_with)
  DEVICE_VARIANT := 2GB
  CLEAR_OVERLAY := n
  KCONFIG:= \
  CONFIG_DRIVER_11AX_SUPPORT=y

  SUPPORTED_DEVICES := realtek,bleeding-edge-emmc-router
  IMAGE/install.img := rtkimg | append-metadata
endef

TARGET_DEVICES += bleedingedge-emmc-2gb-router

# 加入 docker 依赖包.
DEFAULT_PACKAGES.rt1619b_with_docker = docker-compose dockerd docker luci-app-dockerman kmod-rtk-docker rtktranscode 

define Device/bleedingedge-emmc-2gb-router-with-docker
  $(Device/bleedingedge-emmc-2gb-router)
  DEVICE_DTS := rtd1619b-bleedingedge-emmc-2gb-router rtd1619b-rescue
  DEVICE_MODEL += for Router(Docker)
  DEVICE_PACKAGES += $(DEFAULT_PACKAGES.rt1619b_with_docker)
endef

TARGET_DEVICES += bleedingedge-emmc-2gb-router-with-docker

define Device/bleedingedge-spi
  $(Device/rtd1619b)
  KERNEL := kernel-bin | lzma
  DEVICE_MODEL := BleedingEdge SPI board
  DEVICE_PACKAGES += kmod-rtk-spi
  BOARD_NAME := spi
  AUDIO_FW_NAME := bluecore.audio.$$(SOC)_slim.zip
  FLASH_SIZE := 16MB
  IMAGE_FORMAT := .lzma
endef

define Device/bleedingedge-spi-2gb
  $(Device/bleedingedge-spi)
  DEVICE_PACKAGES += kmod-rtk-codec
  DEVICE_VARIANT := 2GB
endef

TARGET_DEVICES += bleedingedge-spi-2gb

define Device/bleedingedge-spi-2gb-purenas
  $(Device/bleedingedge-spi)
  DEVICE_MODEL += for Pure NAS
  DEVICE_VARIANT := 2GB
  NAS_SUFFIX := purenas
endef

TARGET_DEVICES += bleedingedge-spi-2gb-purenas
