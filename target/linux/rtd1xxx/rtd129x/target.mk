# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2015-2021 Realtek Semiconductor Corp.

include $(TOPDIR)/rules.mk

BOARDNAME:=Realtek RTD129X Based Boards
CPU_TYPE:=cortex-a53

define Target/Description
	Build NAS firmware image for Realtek RTD129X SoC boards.
endef

