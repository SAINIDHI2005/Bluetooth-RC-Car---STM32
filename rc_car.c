/*
 * rc_car.c
 *
 *  Created on: Dec 30, 2025
 *      Author: Sainidhi Karthikeyan
 */

#include <stdint.h>

#define RCC_BASEADDR		0x40023800U
#define RCC_APB2ENR	    	(RCC_BASEADDR + 0x44)
#define RCC_AHB1ENR			(RCC_BASEADDR + 0x30)

#define GPIOA_BASEADDR		0x40020000U
#define GPIOA_MODER			(GPIOA_BASEADDR + 0x0)
#define GPIOA_ODR			(GPIOA_BASEADDR + 0x14)
#define GPIOA_AFRH			(GPIOA_BASEADDR + 0x24)
#define GPIOA_PUPDR			(GPIOA_BASEADDR + 0x0C)

#define GPIOB_BASEADDR		0x40020400U
#define GPIOB_MODER			(GPIOB_BASEADDR + 0x0)
#define GPIOB_ODR			(GPIOB_BASEADDR + 0x14)

#define USART1_BASEADDR		0x40011000U
#define USART1_CR1			(USART1_BASEADDR + 0x0C)
#define USART1_CR2			(USART1_BASEADDR + 0x10)
#define USART1_BRR			(USART1_BASEADDR + 0x08)
#define USART1_SR   		(USART1_BASEADDR + 0x00)
#define USART1_DR   		(USART1_BASEADDR + 0x04)

// PA6, PA7 for left motor and PB8, PB9 for right motor

int main(void)
{

	// Motor Interfacing

	volatile uint32_t *AHB1ENR = (volatile uint32_t*)RCC_AHB1ENR;
	// Enabling clock for GPIOA and GPIOB peripheral
	*AHB1ENR &= ~(0x3 << 0);
	*AHB1ENR |= (0x03 << 0);

	volatile uint32_t *GPIOA_MODE_REG = (volatile uint32_t*)GPIOA_MODER;
	// Configuring PA6 and PA7 as Output Mode
	*GPIOA_MODE_REG &= ~(0xF << 12);
	*GPIOA_MODE_REG |=  (0x5 << 12);

	volatile uint32_t *GPIOB_MODE_REG = (volatile uint32_t*)GPIOB_MODER;
	// Configuring PB8 and PB9 as Output Mode
	*GPIOB_MODE_REG &= ~(0xF << 16);
	*GPIOB_MODE_REG |=  (0x5 << 16);



	// Bluetooth Interfacing

	volatile uint32_t *APB2ENR = (volatile uint32_t*)RCC_APB2ENR;
	// Enabling clock for USART1 peripheral
	*APB2ENR |= (0x01 << 4);

	// Configuring PA9 and PA10 as Alternate Function Mode
	*GPIOA_MODE_REG &= ~(0xF << 18);
	*GPIOA_MODE_REG |=  (0xA << 18);

	volatile uint32_t *GPIOA_AFH_REG = (volatile uint32_t*)GPIOA_AFRH;
	// Configuring Alternate Function High Registers for PA9 and PA10 as AF7
	*GPIOA_AFH_REG &= ~(0xFF << 4);
	*GPIOA_AFH_REG |=  (0x77 << 4);

	volatile uint32_t *GPIOA_PUPD_REG = (volatile uint32_t*)GPIOA_PUPDR;
	// Configuring PA10 as pull up
	*GPIOA_PUPD_REG &= ~(0x3 << 20);
	*GPIOA_PUPD_REG |=  (0x01 << 20);

	volatile uint32_t *USART1_CR1_REG = (volatile uint32_t*)USART1_CR1;

	*USART1_CR1_REG &= ~(1 << 13);   // Disable USART1 before configuration
	*USART1_CR1_REG &= ~(1 << 12);	 // 1 Start bit, 8 Data bits, n Stop bit
	*USART1_CR1_REG &= ~(1 << 10);   // Disabled parity

	volatile uint32_t *USART1_CR2_REG = (volatile uint32_t*)USART1_CR2;
	*USART1_CR2_REG &= ~(3 << 12); 	 // 1 stop bit

	volatile uint32_t *USART1_BRR_REG = (volatile uint32_t*)USART1_BRR;
	*USART1_BRR_REG = 0x0683;   // 9600 baud  0683

	*USART1_CR1_REG |= (1 << 3);   // TE enable
	*USART1_CR1_REG |= (1 << 2);   // RE enable

	*USART1_CR1_REG |= (1 << 13);  // UE = 1

	volatile uint32_t *USART1_SR_REG = (volatile uint32_t*)USART1_SR;
	volatile uint32_t *USART1_DR_REG = (volatile uint32_t*)USART1_DR;

	volatile uint32_t *GPIOA_ODR_REG = (volatile uint32_t*)GPIOA_ODR;
	volatile uint32_t *GPIOB_ODR_REG = (volatile uint32_t*)GPIOB_ODR;


	*GPIOA_ODR_REG &= ~(1 << 6);	// PA6
	*GPIOA_ODR_REG &= ~(1 << 7);	// PA7

	*GPIOB_ODR_REG &= ~(1 << 8);	// PB8
	*GPIOB_ODR_REG &= ~(1 << 9);	// PB9

	while (1)
	{
		uint8_t rx_data;



	    while ( !(*USART1_SR_REG & (1 << 5)) );
	    rx_data = (uint8_t)(*USART1_DR_REG);

	    if (rx_data == 'w'){		// Forward

	    	*GPIOA_ODR_REG &= ~(1 << 6);	// PA6
	    	*GPIOA_ODR_REG |=  (1 << 7);	// PA7

	    	*GPIOB_ODR_REG &= ~(1 << 8);	// PB8
	    	*GPIOB_ODR_REG |=  (1 << 9);	// PB9

	    }
	    else if (rx_data == 's'){	// Reverse

	    	*GPIOA_ODR_REG |=  (1 << 6);	// PA6
	    	*GPIOA_ODR_REG &= ~(1 << 7);	// PA7

	    	*GPIOB_ODR_REG |=  (1 << 8);	// PB8
	    	*GPIOB_ODR_REG &= ~(1 << 9);	// PB9

	    }

	    else if (rx_data == 'a'){	// Left

	    	*GPIOA_ODR_REG |=  (1 << 6);	// PA6
	    	*GPIOA_ODR_REG &= ~(1 << 7);	// PA7

	    	*GPIOB_ODR_REG &= ~(1 << 8);	// PB8
	    	*GPIOB_ODR_REG |=  (1 << 9);	// PB9

	    }
	    else if (rx_data == 'd') {	// Right
	    	*GPIOA_ODR_REG &= ~(1 << 6);	// PA6
	    	*GPIOA_ODR_REG |=  (1 << 7);	// PA7

	    	*GPIOB_ODR_REG |=  (1 << 8);	// PB8
	    	*GPIOB_ODR_REG &= ~(1 << 9);	// PB9
	    }
	    else{

	    	*GPIOA_ODR_REG &= ~(1 << 6);	// PA6
			*GPIOA_ODR_REG &= ~(1 << 7);	// PA7

			*GPIOB_ODR_REG &= ~(1 << 8);	// PB8
			*GPIOB_ODR_REG &= ~(1 << 9);	// PB9

	    }
	}

}
