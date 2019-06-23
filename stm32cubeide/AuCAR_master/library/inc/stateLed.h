/*
 * stateLed.h
 *
 *  Created on: 2019. 6. 23.
 *      Author: colson
 */

#ifndef INC_STATELED_H_
#define INC_STATELED_H_

#include "main.h"

class StateLed {
protected:
	GPIO_TypeDef *GPIOx;			/**< GPIOx*/
	uint16_t GPIO_Pin;				/**< GPIOx_Pin*/
	GPIO_PinState PinState;			/**< GPIOx_State*/
	uint16_t period;				/**< GPIOx_period (uint 1ms)*/
	uint32_t nowtick;				/**< GPIOx_time control*/
	uint32_t pasttick;				/**< GPIOx_time control*/

public:

	StateLed(){	}
	StateLed(GPIO_TypeDef *GPIOx_, uint16_t GPIO_Pin_, uint16_t period_):
		GPIOx(GPIOx_), GPIO_Pin(GPIO_Pin_), PinState(GPIO_PIN_RESET), period(period_){
	}

	void init(){reset();}

	void reset(void){period = 1000;}

	void setPeriod(uint16_t period_){period = period_;}

	void toggle(void){HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);}

	void run(void){
		nowtick = HAL_GetTick();
		if(nowtick - pasttick > period)
		{
			toggle();
			pasttick = nowtick;
		}
	}
};




#endif /* INC_STATELED_H_ */
