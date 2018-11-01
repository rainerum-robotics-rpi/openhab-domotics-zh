.PHONY: install, uninstall

PREFIX := /etc/openhab2

install:
	install -m 644 rpidevicesproxy.items $(PREFIX)/items/
	install -m 644 default.sitemap $(PREFIX)/sitemaps/
	install -m 644 cam-not-available.jpg $(PREFIX)/html/

uninstall:
	- rm $(PREFIX)/items/rpidevicesproxy.items
	- rm $(PREFIX)/sitemaps/default.sitemap
	- rm $(PREFIX)/html/cam-not-available.jpg
