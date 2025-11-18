#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include "stm32l476xx.h"
#include <stdint.h>

#define I2C1_SCL_PIN  6   // PB6
#define I2C1_SDA_PIN  7   // PB7

typedef enum {
    I2C_READY = 0,
    I2C_BUSY_TX,
    I2C_BUSY_RX
} I2C_State_t;

typedef struct {
    uint8_t  slave_addr;
    uint8_t *tx_buf;
    uint8_t  tx_len;

    uint8_t *rx_buf;
    uint8_t  rx_len;

    I2C_State_t state;
} I2C_Handle_t;

extern I2C_Handle_t I2C1_Handle;

void I2C1_GPIO_Init(void);
void I2C1_Init(void);
void I2C1_Interrupt_Init(void);
void I2C1_Master_Transmit_IT(uint8_t slave, uint8_t *data, uint8_t len);
void I2C1_Master_Receive_IT(uint8_t slave, uint8_t *data, uint8_t len);

#endif
