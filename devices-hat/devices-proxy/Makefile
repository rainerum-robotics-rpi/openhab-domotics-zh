src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lwiringPi -lpaho-mqtt3c

devices-proxy: $(obj)
	gcc -o $@ $^ $(LDFLAGS)

.PHONY: clean, install, uninstall
clean:
	rm -f $(obj) devices-proxy

PREFIX := /usr/local

install: devices-proxy
	install -d $(PREFIX)/bin/
	install -m 755 devices-proxy $(PREFIX)/bin/
	install -d /usr/lib/systemd/system/
	install -m 644 devices-proxy.service /usr/lib/systemd/system/
	systemctl daemon-reload
	systemctl enable devices-proxy.service
	systemctl start devices-proxy.service

uninstall:
	- systemctl stop devices-proxy.service
	- systemctl disable devices-proxy.service
	- rm $(PREFIX)/bin/devices-proxy
	- rm /usr/lib/systemd/system/devices-proxy.service
