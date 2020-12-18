#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "Kid4Relay.h"

// vTaskDelay(500 / portTICK_RATE_MS);

Kid4Relay::Kid4Relay(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
}

void Kid4Relay::init(void) {
	state = s_detect;
}

int Kid4Relay::prop_count(void) {
	// not supported
	return 0;
}

bool Kid4Relay::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool Kid4Relay::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool Kid4Relay::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool Kid4Relay::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool Kid4Relay::prop_write(int index, char *value) {
	// not supported
	return false;
}

void Kid4Relay::process(Driver *drv) {
	i2c = (I2CDev *)drv;

	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				// Set mode to OUTPUT
				uint8_t dataSend[2] = {
					3,   // Configuration register
					0x00 // All to OUTPUT
				};
				if (i2c->write(channel, address, dataSend, 2) == ESP_OK) {
					error = false;
					initialized = true;
					dataUpdateFlag = true;
					state = s_poll;
				} else {
					state = s_error;
				}
			} else {
				state = s_error;
			}
			break;

		case s_poll:
			if (dataUpdateFlag) {
				// Set port data
				uint8_t dataSend[2] = {
					1, // Output Port register
					this->data // Port data
				};
				if (i2c->write(channel, address, dataSend, 2) == ESP_OK) {
					dataUpdateFlag = false;
				} else {
					state = s_error;
				}
			}
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

		case s_wait:
			// delay 1000ms before retry detect
			if (is_tickcnt_elapsed(tickcnt, 1000)) {
				state = s_detect;
			}
			break;
	}
}

void Kid4Relay::set(uint8_t ch, bool value) {
	if (ch < 1 || ch > 4) return;

	if (value) {
		this->data |= 1 << (ch - 1);
	} else {
		this->data &= ~(1 << (ch - 1));
	}
	this->dataUpdateFlag = true;
}
