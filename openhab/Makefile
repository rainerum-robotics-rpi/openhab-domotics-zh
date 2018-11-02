.PHONY: install, uninstall

PREFIX := /etc/openhab2

install:
	install -m 644 rpidevicesproxy.items $(PREFIX)/items/
	install -m 644 default.sitemap $(PREFIX)/sitemaps/
	install -m 644 cam-not-available.jpg $(PREFIX)/html/
	ln -s -f $(PREFIX)/html/cam-not-available.jpg $(PREFIX)/html/cam0.jpg
	install -m 755 devices-proxy-cam.sh /usr/local/bin/
	install -m 644 devices-proxy-cam.service /usr/lib/systemd/system/
	install -m 644 devices-proxy-cam.timer /usr/lib/systemd/system/
	systemctl daemon-reload
	systemctl start devices-proxy-cam.timer

uninstall:
	- systemctl stop devices-proxy-cam.timer
	- rm /usr/lib/systemd/system/devices-proxy-cam.timer
	- rm /usr/lib/systemd/system/devices-proxy-cam.service
	- rm /usr/local/bin/devices-proxy-cam.sh
	- unlink $(PREFIX)/html/cam0.jpg
	- rm $(PREFIX)/items/rpidevicesproxy.items
	- rm $(PREFIX)/sitemaps/default.sitemap
	- rm $(PREFIX)/html/cam-not-available.jpg
	- rm $(PREFIX)/html/cam_dev_video0.jpg
