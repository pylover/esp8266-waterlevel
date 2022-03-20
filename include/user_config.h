#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#define USE_OPTIMIZE_PRINTF

#define __name__ "waterlevel"
#define __version__ "0.1.0"

#define PARAMS_DEFAULT_ZONE "dev"
#define PARAMS_DEFAULT_NAME __name__

// LED
#define LED_MUX		        PERIPHS_IO_MUX_GPIO2_U	
#define LED_NUM			    2
#define LED_FUNC		    FUNC_GPIO2

#define MAXWET_MUX		    PERIPHS_IO_MUX_MTMS_U	
#define MAXWET_NUM		    14
#define MAXWET_FUNC		    FUNC_GPIO14
#define MAXWET_PIN		    GPIO_ID_PIN(MAXWET_NUM)

#define MIDWET_MUX		    PERIPHS_IO_MUX_GPIO4_U	
#define MIDWET_NUM		    4
#define MIDWET_FUNC		    FUNC_GPIO4
#define MIDWET_PIN		    GPIO_ID_PIN(MIDWET_NUM)

#define MINWET_MUX		    PERIPHS_IO_MUX_GPIO5_U	
#define MINWET_NUM		    5
#define MINWET_FUNC		    FUNC_GPIO5
#define MINWET_PIN		    GPIO_ID_PIN(MINWET_NUM)

#define VAPORIZER_MUX		PERIPHS_IO_MUX_MTDI_U	
#define VAPORIZER_NUM		12
#define VAPORIZER_FUNC		FUNC_GPIO12
#define VAPORIZER_PIN		GPIO_ID_PIN(VAPORIZER_NUM)

#define PUMP_MUX		    PERIPHS_IO_MUX_MTCK_U	
#define PUMP_NUM		    13
#define PUMP_FUNC		    FUNC_GPIO13
#define PUMP_PIN		    GPIO_ID_PIN(PUMP_NUM)
#endif

