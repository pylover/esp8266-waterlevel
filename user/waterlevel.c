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
        goto done;
    }
    else {
        VAPORIZER_SET(ON);
    }
    
    if (MAXWET()) {
        PUMP_SET(OFF);
        goto done;
    }

    if (!MIDWET()) {
        PUMP_SET(ON);
        goto done;
    }

done:
    status_update(300, 200, 1, waterlevel_check);
}


void ICACHE_FLASH_ATTR
waterlevel_init() {

	PIN_PULLUP_EN(MAXWET_MUX);
	PIN_FUNC_SELECT(MAXWET_MUX, MAXWET_FUNC);
	GPIO_DIS_OUTPUT(MAXWET_NUM);

	PIN_PULLUP_EN(MIDWET_MUX);
	PIN_FUNC_SELECT(MIDWET_MUX, MIDWET_FUNC);
	GPIO_DIS_OUTPUT(MIDWET_NUM);

	PIN_PULLUP_EN(MINWET_MUX);
	PIN_FUNC_SELECT(MINWET_MUX, MINWET_FUNC);
	GPIO_DIS_OUTPUT(MINWET_NUM);

	PIN_PULLUP_EN(VAPORIZER_MUX);
	PIN_FUNC_SELECT(VAPORIZER_MUX, VAPORIZER_FUNC);
	GPIO_OUTPUT_SET(VAPORIZER_NUM, OFF);

	PIN_PULLUP_EN(PUMP_MUX);
	PIN_FUNC_SELECT(PUMP_MUX, PUMP_FUNC);
	GPIO_OUTPUT_SET(PUMP_NUM, OFF);
}

