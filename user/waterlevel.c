#include "user_config.h"
#include "debug.h"

#include <eagle_soc.h>
#include <c_types.h>
#include <gpio.h>
#include <ets_sys.h>

#define MAXWET() (!GPIO_INPUT_GET(MAXWET_PIN))
#define MIDWET() (!GPIO_INPUT_GET(MIDWET_PIN))
#define MINWET() (!GPIO_INPUT_GET(MINWET_PIN))

#define VAPORIZER_SET(v) GPIO_OUTPUT_SET(VAPORIZER_PIN, (v))
#define PUMP_SET(v) GPIO_OUTPUT_SET(PUMP_PIN, (v))

#define ON  0
#define OFF 1

ICACHE_FLASH_ATTR
void waterlevel_check() {
    if (!MINWET()) {
        /* Turn off everything */
        VAPORIZER_SET(OFF);
        PUMP_SET(OFF);
        return;
    }
    else {
        VAPORIZER_SET(ON);
    }
    
    if (MAXWET()) {
        PUMP_SET(OFF);
        return;
    }

    if (!MIDWET()) {
        PUMP_SET(ON);
        return;
    }
}

void gpio_intr(void *arg) {
	unsigned int gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);
    waterlevel_check();
    DEBUG("INTR");
    DEBUG("MAXWET: %d", MAXWET());
    DEBUG("MIDWET: %d", MIDWET());
    DEBUG("MINWET: %d", MINWET());
	// Clear interrupt status
	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);
}



void ICACHE_FLASH_ATTR
waterlevel_init() {
	ETS_GPIO_INTR_DISABLE();

	PIN_PULLUP_EN(MAXWET_MUX);
	PIN_FUNC_SELECT(MAXWET_MUX, MAXWET_FUNC);
	GPIO_DIS_OUTPUT(MAXWET_NUM);
	gpio_pin_intr_state_set(GPIO_ID_PIN(MAXWET_NUM), GPIO_PIN_INTR_ANYEDGE);

	PIN_PULLUP_EN(MIDWET_MUX);
	PIN_FUNC_SELECT(MIDWET_MUX, MIDWET_FUNC);
	GPIO_DIS_OUTPUT(MIDWET_NUM);
	gpio_pin_intr_state_set(GPIO_ID_PIN(MIDWET_NUM), GPIO_PIN_INTR_ANYEDGE);

	PIN_PULLUP_EN(MINWET_MUX);
	PIN_FUNC_SELECT(MINWET_MUX, MINWET_FUNC);
	GPIO_DIS_OUTPUT(MINWET_NUM);
	gpio_pin_intr_state_set(GPIO_ID_PIN(MINWET_NUM), GPIO_PIN_INTR_ANYEDGE);

	PIN_PULLUP_EN(VAPORIZER_MUX);
	PIN_FUNC_SELECT(VAPORIZER_MUX, VAPORIZER_FUNC);
	GPIO_OUTPUT_SET(VAPORIZER_NUM, 0);

	PIN_PULLUP_EN(PUMP_MUX);
	PIN_FUNC_SELECT(PUMP_MUX, PUMP_FUNC);
	GPIO_OUTPUT_SET(PUMP_NUM, 0);

	ETS_GPIO_INTR_ATTACH(gpio_intr, NULL);
	ETS_GPIO_INTR_ENABLE();
}

