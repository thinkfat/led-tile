#ifndef HW_DEFS_38X38_REV_0_4_H
#define HW_DEFS_38X38_REV_0_4_H


#ifndef HW_38x38_rev_0_4
#error The matching HW selection macro not defined
#endif

/**************************************
 *	Display Definitions
 **************************************/

#define DISP_ROWS_NUM 8
#define DISP_COLS_NUM 8
#define DISP_COLOR_DEPTH 32

/* shutdown pin */
#define DISP_GPIOP_SDB	GPIOB
#define DISP_GPIO_SDB	GPIO4

#define DISP_GPIOP_I2C	GPIOB
#define DISP_GPIO_SDA	GPIO14
#define DISP_GPIO_SCL	GPIO13

#define DISP_GPIOS_RCC RCC_GPIOB
#define DISP_I2C_RCC   RCC_I2C2

/**************************************
 *	USARTs Definitions
 **************************************/

#define USART_BAUDRATE 115200

#define USART_A 0
#define USART_A_REG USART1
#define USART_A_RCC RCC_USART1
#define USART_A_IRQ NVIC_USART1_IRQ
#define USART_A_RX_RCC RCC_GPIOB
#define USART_A_RX_PORT GPIOB
#define USART_A_RX_PIN GPIO7
#define USART_A_RX_AF_NUM GPIO_AF0
#define USART_A_TX_RCC RCC_GPIOB
#define USART_A_TX_PORT GPIOB
#define USART_A_TX_PIN GPIO6
#define USART_A_TX_AF_NUM GPIO_AF0

#define USART_B 1
#define USART_B_REG USART2
#define USART_B_RCC RCC_USART2
#define USART_B_IRQ NVIC_USART2_IRQ
#define USART_B_RX_RCC RCC_GPIOA
#define USART_B_RX_PORT GPIOA
#define USART_B_RX_PIN GPIO3
#define USART_B_RX_AF_NUM GPIO_AF1
#define USART_B_TX_RCC RCC_GPIOA
#define USART_B_TX_PORT GPIOA
#define USART_B_TX_PIN GPIO2
#define USART_B_TX_AF_NUM GPIO_AF1

#define USART_C 2
#define USART_C_REG USART3
#define USART_C_RCC RCC_USART3
#define USART_C_IRQ NVIC_USART3_4_IRQ
#define USART_C_RX_RCC RCC_GPIOB
#define USART_C_RX_PORT GPIOB
#define USART_C_RX_PIN GPIO11
#define USART_C_RX_AF_NUM GPIO_AF4
#define USART_C_TX_RCC RCC_GPIOB
#define USART_C_TX_PORT GPIOB
#define USART_C_TX_PIN GPIO10
#define USART_C_TX_AF_NUM GPIO_AF4

#define USART_D 3
#define USART_D_REG USART4
#define USART_D_RCC RCC_USART4
#define USART_D_IRQ NVIC_USART3_4_IRQ
#define USART_D_RX_RCC RCC_GPIOA
#define USART_D_RX_PORT GPIOA
#define USART_D_RX_PIN GPIO1
#define USART_D_RX_AF_NUM GPIO_AF4
#define USART_D_TX_RCC RCC_GPIOA
#define USART_D_TX_PORT GPIOA
#define USART_D_TX_PIN GPIO0
#define USART_D_TX_AF_NUM GPIO_AF4

#define USART_DIR_UP USART_C
#define USART_DIR_DOWN USART_D
#define USART_DIR_LEFT USART_B
#define USART_DIR_RIGHT USART_A


#endif
