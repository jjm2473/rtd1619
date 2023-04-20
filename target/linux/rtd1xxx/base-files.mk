define Package/base-files/postinst
#!/bin/sh

HOST_SED="$(subst ${STAGING_DIR_HOST},$${STAGING_DIR_HOST},$(SED))"
HOST_LN="$(subst ${STAGING_DIR_HOST},$${STAGING_DIR_HOST},$(LN))"

[ -n "$${IPKG_INSTROOT}" ] && {
	$${HOST_SED} '/^src\/gz openwrt_\(base\|luci\|packages\|routing\|telephony\) /!d' \
		-e 's/aarch64_cortex-a55/aarch64_cortex-a53/g' \
		"$${IPKG_INSTROOT}/etc/opkg/distfeeds.conf"

	$${HOST_SED} 's/"192.168.1.1"/"192.168.100.1"/' \
		"$${IPKG_INSTROOT}/bin/config_generate"

	$${HOST_SED} "s/'192\\.168\\.1\\.1'/'192.168.100.1'/; s/'openwrt\\.lan'/window.location.host/" \
		"$${IPKG_INSTROOT}/www/luci-static/resources/view/system/flash.js"

}
true

endef
