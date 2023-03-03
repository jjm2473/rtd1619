# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2015-2021 Realtek Semiconductor Corp.

include $(TOPDIR)/rules.mk

BOARDNAME:=Realtek RTD1619b Based Boards

define Target/Description
	Build NAS firmware image for Realtek RTD1619B SoC boards.
endef

DEFAULT_PACKAGES += kmod-rtl8125 kmod-rtl8152 kmod-rtkwifiu kmod-rtkwifiu-rtl8822cs