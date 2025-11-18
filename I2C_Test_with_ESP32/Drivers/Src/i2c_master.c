#include "i2c_master.h"

I2C_Handle_t I2C1_Handle = {0};

void I2C1_GPIO_Init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    GPIOB->MODER &= ~((3 << (I2C1_SCL_PIN*2)) | (3 << (I2C1_SDA_PIN*2)));
    GPIOB->MODER |=  ((2 << (I2C1_SCL_PIN*2)) | (2 << (I2C1_SDA_PIN*2)));

    GPIOB->OTYPER |= (1 << I2C1_SCL_PIN) | (1 << I2C1_SDA_PIN);
    GPIOB->OSPEEDR |= (3 << (I2C1_SCL_PIN*2)) | (3 << (I2C1_SDA_PIN*2));
    GPIOB->PUPDR &= ~((3 << (I2C1_SCL_PIN*2)) | (3 << (I2C1_SDA_PIN*2)));
    GPIOB->PUPDR |= ((1 << (I2C1_SCL_PIN*2)) | (1 << (I2C1_SDA_PIN*2)));

    GPIOB->AFR[0] |= (4 << (I2C1_SCL_PIN*4)) | (4 << (I2C1_SDA_PIN*4));
}

void I2C1_Init(void)
{
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
    I2C1->CR1 &= ~I2C_CR1_PE;

    I2C1->TIMINGR = (1 << 28) | (2 << 20) | (2 << 16) | (0xF << 8) | (0x13);

    I2C1->CR1 |= I2C_CR1_PE;
}

void I2C1_Interrupt_Init(void)
{
    I2C1->CR1 |= I2C_CR1_TXIE | I2C_CR1_RXIE | I2C_CR1_TCIE | I2C_CR1_STOPIE;
    NVIC_EnableIRQ(I2C1_EV_IRQn);
}

void I2C1_Master_Transmit_IT(uint8_t slave, uint8_t *data, uint8_t len)
{
    I2C1_Handle.state = I2C_BUSY_TX;
    I2C1_Handle.slave_addr = slave;
    I2C1_Handle.tx_buf = data;
    I2C1_Handle.tx_len = len;

    I2C1->CR2 = (slave << 1) | (len << 16) | I2C_CR2_START;
}

void I2C1_Master_Receive_IT(uint8_t slave, uint8_t *data, uint8_t len)
{
    I2C1_Handle.state = I2C_BUSY_RX;
    I2C1_Handle.slave_addr = slave;
    I2C1_Handle.rx_buf = data;
    I2C1_Handle.rx_len = len;

    I2C1->CR2 = (slave << 1) | (len << 16) | I2C_CR2_RD_WRN | I2C_CR2_START;
}

void I2C1_EV_IRQHandler(void)
{
    // TRANSMITTING
    if ((I2C1->ISR & I2C_ISR_TXIS) && I2C1_Handle.state == I2C_BUSY_TX)
    {
        I2C1->TXDR = *(I2C1_Handle.tx_buf++);
        I2C1_Handle.tx_len--;
    }

    // RECEIVING
    if ((I2C1->ISR & I2C_ISR_RXNE) && I2C1_Handle.state == I2C_BUSY_RX)
    {
        *(I2C1_Handle.rx_buf++) = I2C1->RXDR;
        I2C1_Handle.rx_len--;
    }

    // TRANSFER COMPLETE
    if (I2C1->ISR & I2C_ISR_TC)
        I2C1->CR2 |= I2C_CR2_STOP;

    // STOP = communication done
    if (I2C1->ISR & I2C_ISR_STOPF)
    {
        I2C1->ICR |= I2C_ICR_STOPCF;
        I2C1_Handle.state = I2C_READY;
    }
}
