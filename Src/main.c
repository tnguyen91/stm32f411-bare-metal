#include <stdint.h>
#include <string.h>

#define RCC_AHB1ENR          (*(volatile uint32_t *)0x40023830u)
#define RCC_AHB1ENR_GPIOAEN  (1u << 0)
#define RCC_AHB1ENR_GPIOBEN  (1u << 1)
#define RCC_APB1ENR          (*(volatile uint32_t *)0x40023840u)
#define RCC_APB1ENR_USART2EN (1u << 17)
#define RCC_APB1ENR_I2C1EN   (1u << 21)

#define GPIOA_MODER          (*(volatile uint32_t *)0x40020000u)
#define GPIOA_MODER5_POS     10u
#define GPIOA_MODER5_MASK    (3u << GPIOA_MODER5_POS)
#define GPIOA_MODER2_POS     4u
#define GPIOA_MODER2_MASK    (3u << GPIOA_MODER2_POS)
#define GPIOA_MODER3_POS     6u
#define GPIOA_MODER3_MASK    (3u << GPIOA_MODER3_POS)

#define GPIO_MODE_OUTPUT     1u
#define GPIO_MODE_ALTERNATE  2u

#define GPIOA_ODR            (*(volatile uint32_t *)0x40020014u)
#define GPIOA_ODR_ODR5       (1u << 5)

#define GPIOA_AFRL           (*(volatile uint32_t *)0x40020020u)
#define GPIOA_AFRL2_POS      8u
#define GPIOA_AFRL2_MASK     (0xFu << GPIOA_AFRL2_POS)
#define GPIOA_AFRL3_POS      12u
#define GPIOA_AFRL3_MASK     (0xFu << GPIOA_AFRL3_POS)
#define GPIO_AF_USART2       7u

#define GPIOB_MODER          (*(volatile uint32_t *)0x40020400u)
#define GPIOB_MODER8_POS     16u /* PB8, D15, SCL */
#define GPIOB_MODER8_MASK    (3u << GPIOB_MODER8_POS)
#define GPIOB_MODER9_POS     18u /* PB9, D14, SDA */
#define GPIOB_MODER9_MASK    (3u << GPIOB_MODER9_POS)
#define GPIOB_OTYPER         (*(volatile uint32_t *)0x40020404u)
#define GPIOB_OTYPER_OT8     (1u << 8)
#define GPIOB_OTYPER_OT9     (1u << 9)
#define GPIOB_AFRH           (*(volatile uint32_t *)0x40020424u)
#define GPIOB_AFRH8_POS      0u
#define GPIOB_AFRH8_MASK     (0xFu << GPIOB_AFRH8_POS)
#define GPIOB_AFRH9_POS      4u
#define GPIOB_AFRH9_MASK     (0xFu << GPIOB_AFRH9_POS)
#define GPIO_AF_I2C1         4u

#define I2C1_CR1             (*(volatile uint32_t *)0x40005400u)
#define I2C1_CR1_PE          (1u << 0)
#define I2C1_CR1_START       (1u << 8)
#define I2C1_CR1_STOP        (1u << 9)
#define I2C1_CR1_ACK         (1u << 10)
#define I2C1_CR2             (*(volatile uint32_t *)0x40005404u)
#define I2C1_DR              (*(volatile uint32_t *)0x40005410u)
#define I2C1_SR1             (*(volatile uint32_t *)0x40005414u)
#define I2C1_SR1_SB          (1u << 0)
#define I2C1_SR1_ADDR        (1u << 1)
#define I2C1_SR1_BTF         (1u << 2)
#define I2C1_SR1_RXNE        (1u << 6)
#define I2C1_SR1_TXE         (1u << 7)
#define I2C1_SR1_AF          (1u << 10)
#define I2C1_SR2             (*(volatile uint32_t *)0x40005418u)
#define I2C1_CCR             (*(volatile uint32_t *)0x4000541Cu)
#define I2C1_TRISE           (*(volatile uint32_t *)0x40005420u)

#define USART2_SR            (*(volatile uint32_t *)0x40004400u)
#define USART2_SR_TXE        (1u << 7)
#define USART2_SR_RXNE       (1u << 5)
#define USART2_SR_ORE        (1u << 3)
#define USART2_DR            (*(volatile uint32_t *)0x40004404u)
#define USART2_BRR           (*(volatile uint32_t *)0x40004408u)
#define USART2_CR1           (*(volatile uint32_t *)0x4000440Cu)
#define USART2_CR1_RE        (1u << 2)
#define USART2_CR1_TE        (1u << 3)
#define USART2_CR1_RXNEIE    (1u << 5)
#define USART2_CR1_UE        (1u << 13)

#define STK_CTRL             (*(volatile uint32_t *)0xE000E010u)
#define STK_CTRL_ENABLE      (1u << 0)
#define STK_CTRL_TICKINT     (1u << 1)
#define STK_CTRL_CLKSOURCE   (1u << 2)
#define STK_LOAD             (*(volatile uint32_t *)0xE000E014u)
#define STK_VAL              (*(volatile uint32_t *)0xE000E018u)

#define SYSCLK_HZ 16000000u /* internal oscillator (HSI) after reset */
#define SYSTICK_PERIOD_CYCLES (SYSCLK_HZ / 1000u) /* 1 ms */

#define PCLK1_HZ SYSCLK_HZ
#define USART2_BAUD 115200u
#define USART2_CYCLES_PER_BIT ((PCLK1_HZ + (USART2_BAUD / 2u)) / USART2_BAUD)

#define PCLK1_MHZ (PCLK1_HZ / 1000000u)
#define I2C1_SCL_HZ 80000u // standard mode, at or below 88 kHz for ES0287 2.9.4 (repeated START)
#define I2C1_CYCLES_PER_SCL_HALF (PCLK1_HZ / (2u * I2C1_SCL_HZ))
#define I2C_SM_MAX_RISE_US 1u // standard mode's rise-time limit, 1000 ns
#define I2C1_TRISE_CYCLES (I2C_SM_MAX_RISE_US * PCLK1_MHZ + 1u) // +1 is RM0383's rule
#define I2C1_TIMEOUT_MS 10u
#define I2C_READ_BIT 1u // R/W, bit 0 of the address byte, 1 for read, 0 for write

#define CAP1188_I2C_ADDRESS 0x29u // with the breakout's 150 kOhm on ADDR_COMM
#define CAP1188_REG_PRODUCT_ID 0xFDu
#define CAP1188_REG_MANUFACTURER_ID 0xFEu
#define CAP1188_REG_REVISION 0xFFu

#define LINE_BUFFER_SIZE 32u
#define ASCII_DEL 127u
#define UINT32_TEXT_SIZE 11u /* "4294967295" + null terminator */

#define NVIC_ISER1           (*(volatile uint32_t *)0xE000E104u)
#define NVIC_ISER1_USART2    (1u << (38u - 32u)) /* IRQ 38, ISER1 holds IRQs 32 to 63 */

#define RX_RING_SIZE         64u /* a power of 2, so an index wraps with a mask */
#define RX_RING_MASK         (RX_RING_SIZE - 1u)

static volatile uint32_t elapsed_ms;

void SysTick_Handler(void)
{
    elapsed_ms++;
}

uint32_t millis(void)
{
    return elapsed_ms;
}

static void systick_start_1ms(void)
{
    STK_LOAD = SYSTICK_PERIOD_CYCLES - 1u;
    STK_VAL = 0u;
    STK_CTRL = STK_CTRL_ENABLE | STK_CTRL_TICKINT | STK_CTRL_CLKSOURCE;
}

static void usart2_init(void)
{
    RCC_APB1ENR |= RCC_APB1ENR_USART2EN;
    (void)RCC_APB1ENR; // same errata wait as GPIOA's

    GPIOA_AFRL = (GPIOA_AFRL & ~GPIOA_AFRL2_MASK)
                | ((GPIO_AF_USART2 << GPIOA_AFRL2_POS) & GPIOA_AFRL2_MASK);
    GPIOA_AFRL = (GPIOA_AFRL & ~GPIOA_AFRL3_MASK)
                | ((GPIO_AF_USART2 << GPIOA_AFRL3_POS) & GPIOA_AFRL3_MASK);

    GPIOA_MODER = (GPIOA_MODER & ~GPIOA_MODER2_MASK)
                | ((GPIO_MODE_ALTERNATE << GPIOA_MODER2_POS) & GPIOA_MODER2_MASK);
    GPIOA_MODER = (GPIOA_MODER & ~GPIOA_MODER3_MASK)
                | ((GPIO_MODE_ALTERNATE << GPIOA_MODER3_POS) & GPIOA_MODER3_MASK);

    USART2_BRR = USART2_CYCLES_PER_BIT;
    USART2_CR1 = USART2_CR1_RE | USART2_CR1_TE | USART2_CR1_UE | USART2_CR1_RXNEIE;

    NVIC_ISER1 = NVIC_ISER1_USART2;
}

static void usart2_write_byte(char byte)
{
    while ((USART2_SR & USART2_SR_TXE) == 0u) {
    }
    USART2_DR = (uint8_t)byte;
}

static void usart2_write_string(const char *str)
{
    while (*str != '\0') {
        usart2_write_byte(*str);
        str++;
    }
}

static void usart2_write_decimal(uint32_t value)
{
    char text[UINT32_TEXT_SIZE];
    uint32_t first_digit = UINT32_TEXT_SIZE - 1u;

    text[first_digit] = '\0';
    do {
        first_digit--;
        text[first_digit] = (char)('0' + (value % 10u));
        value /= 10u;
    } while (value != 0u);

    usart2_write_string(&text[first_digit]);
}

static void usart2_write_hex_byte(uint8_t value)
{
    static const char hex_digits[] = "0123456789ABCDEF";
    
    usart2_write_byte(hex_digits[(value >> 4u) & 0xFu]);
    usart2_write_byte(hex_digits[value & 0xFu]);
}

static volatile char rx_ring[RX_RING_SIZE];
static volatile uint32_t rx_head; // written only by handler
static volatile uint32_t rx_tail; // written only by main
static volatile uint32_t rx_dropped_count;
static volatile uint32_t rx_overrun_count;

void USART2_IRQHandler(void)
{
    uint32_t status = USART2_SR;
    if ((status & (USART2_SR_RXNE | USART2_SR_ORE)) == 0u) {
        return; // ignore the interrupt if neither RXNE nor ORE is set
    }

    char received = (char)USART2_DR; // after the SR read, this clears ORE as well as RXNE

    if ((status & USART2_SR_ORE) != 0u) {
        rx_overrun_count++;
    }
    if ((status & USART2_SR_RXNE) == 0u) {
        return; // ORE alone, so DR holds a byte this handler already took
    }

    uint32_t next_head = (rx_head + 1u) & RX_RING_MASK;
    if (next_head == rx_tail) {
        rx_dropped_count++;
        return;
    }
    rx_ring[rx_head] = received;
    rx_head = next_head;
}

static char usart2_read_byte(void)
{
    while (rx_head == rx_tail) {
    }

    char received = rx_ring[rx_tail];
    rx_tail = (rx_tail + 1u) & RX_RING_MASK;
    return received;
}

static void i2c1_init(void)
{
    RCC_APB1ENR |= RCC_APB1ENR_I2C1EN;
    (void)RCC_APB1ENR; // same errata wait as GPIOA's
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    (void)RCC_AHB1ENR; // same errata wait as GPIOA's

    GPIOB_OTYPER |= GPIOB_OTYPER_OT8 | GPIOB_OTYPER_OT9;

    GPIOB_AFRH = (GPIOB_AFRH & ~GPIOB_AFRH8_MASK)
                | ((GPIO_AF_I2C1 << GPIOB_AFRH8_POS) & GPIOB_AFRH8_MASK);
    GPIOB_AFRH = (GPIOB_AFRH & ~GPIOB_AFRH9_MASK)
                | ((GPIO_AF_I2C1 << GPIOB_AFRH9_POS) & GPIOB_AFRH9_MASK);

    // MODER last, so each pin switches to I2C1 only after its type and AF are set
    GPIOB_MODER = (GPIOB_MODER & ~GPIOB_MODER8_MASK)
                | ((GPIO_MODE_ALTERNATE << GPIOB_MODER8_POS) & GPIOB_MODER8_MASK);
    GPIOB_MODER = (GPIOB_MODER & ~GPIOB_MODER9_MASK)
                | ((GPIO_MODE_ALTERNATE << GPIOB_MODER9_POS) & GPIOB_MODER9_MASK);

    I2C1_CR2 = PCLK1_MHZ; // FREQ is bits 5:0
    I2C1_CCR = I2C1_CYCLES_PER_SCL_HALF; // F/S stays 0, so standard mode
    I2C1_TRISE = I2C1_TRISE_CYCLES; // =, not |=, so the reset value's bit 1 doesn't stay
    I2C1_CR1 = I2C1_CR1_PE; // enable the peripheral last, CCR and TRISE writes only while PE is 0
}

typedef enum {
    I2C1_OK,
    I2C1_NACK,
    I2C1_TIMEOUT,
} i2c1_result_t;

/* Waits for an SR1 flag. Returns I2C1_NACK if AF sets first, I2C1_TIMEOUT after I2C1_TIMEOUT_MS. */
static i2c1_result_t i2c1_wait_for_sr1(uint32_t flag)
{
    uint32_t start_ms = millis();

    while ((I2C1_SR1 & flag) == 0u) {
        if ((I2C1_SR1 & I2C1_SR1_AF) != 0u) {
            return I2C1_NACK;
        }
        if ((millis() - start_ms) >= I2C1_TIMEOUT_MS) {
            return I2C1_TIMEOUT;
        }
    }
    return I2C1_OK;
}

static i2c1_result_t i2c1_wait_for_stop_done(void)
{
    uint32_t start_ms = millis();

    while ((I2C1_CR1 & I2C1_CR1_STOP) != 0u) {
        if ((millis() - start_ms) >= I2C1_TIMEOUT_MS) {
            return I2C1_TIMEOUT;
        }
    }
    return I2C1_OK;
}

static i2c1_result_t i2c1_abort_transfer(i2c1_result_t result)
{
    I2C1_SR1 &= ~I2C1_SR1_AF; // clear the NACK flag if it was set
    I2C1_CR1 |= I2C1_CR1_STOP;
    return result;
}

/* Reads one register of a target: START, address+W, register, repeated START, address+R,
 * one byte answered with a NACK, STOP. Returns I2C1_OK with the byte in *value, or
 * I2C1_NACK or I2C1_TIMEOUT with a STOP requested and *value unchanged. */
static i2c1_result_t i2c1_read_register(uint8_t target_address, uint8_t reg, uint8_t *value)
{
    i2c1_result_t result = i2c1_wait_for_stop_done(); // RM0383: no CR1 write while STOP is pending
    if (result != I2C1_OK) {
        return result;
    }

    I2C1_CR1 |= I2C1_CR1_START;
    result = i2c1_wait_for_sr1(I2C1_SR1_SB);
    if (result != I2C1_OK) {
        return i2c1_abort_transfer(result);
    }
    I2C1_DR = (uint32_t)target_address << 1u; // write, bit 0 = 0

    result = i2c1_wait_for_sr1(I2C1_SR1_ADDR);
    if (result != I2C1_OK) {
        return i2c1_abort_transfer(result);
    }
    (void)I2C1_SR2; // completes ADDR's clearing, after the wait's read of SR1

    result = i2c1_wait_for_sr1(I2C1_SR1_TXE);
    if (result != I2C1_OK) {
        return i2c1_abort_transfer(result);
    }
    I2C1_DR = reg;

    result = i2c1_wait_for_sr1(I2C1_SR1_BTF);
    if (result != I2C1_OK) {
        return i2c1_abort_transfer(result);
    }
    I2C1_CR1 |= I2C1_CR1_START; // repeated START

    result = i2c1_wait_for_sr1(I2C1_SR1_SB);
    if (result != I2C1_OK) {
        return i2c1_abort_transfer(result);
    }
    I2C1_DR = ((uint32_t)target_address << 1) | I2C_READ_BIT; // read, bit 0 = 1

    result = i2c1_wait_for_sr1(I2C1_SR1_ADDR);
    if (result != I2C1_OK) {
        return i2c1_abort_transfer(result);
    }
    I2C1_CR1 &= ~I2C1_CR1_ACK; // RM0383's one-byte rule: ACK off before ADDR clears
    (void)I2C1_SR2;
    I2C1_CR1 |= I2C1_CR1_STOP; // during the byte, so STOP follows it

    result = i2c1_wait_for_sr1(I2C1_SR1_RXNE);
    if (result != I2C1_OK) {
        return result; // no need to abort, STOP is already requested
    }
    *value = (uint8_t)I2C1_DR;
    return I2C1_OK;
}

static void cap1188_print_id_register(const char *label, uint8_t reg)
{
    uint8_t value = 0u;
    i2c1_result_t result = i2c1_read_register(CAP1188_I2C_ADDRESS, reg, &value);

    usart2_write_string(label);
    if (result == I2C1_OK) {
        usart2_write_string("0x");
        usart2_write_hex_byte(value);
    }
    else if (result == I2C1_NACK) {
        usart2_write_string("no ACK");
    }
    else {
        usart2_write_string("timeout");
    }
    usart2_write_string("\r\n");
}

static void run_command(const char *line)
{
    if (strcmp(line, "led") == 0) {
        GPIOA_ODR ^= GPIOA_ODR_ODR5;
        if ((GPIOA_ODR & GPIOA_ODR_ODR5) != 0u) {
            usart2_write_string("LD2 ON\r\n");
        }
        else {
            usart2_write_string("LD2 OFF\r\n");
        }
    }
    else if (strcmp(line, "millis") == 0) {
        usart2_write_decimal(millis());
        usart2_write_string(" ms\r\n");
    }
    else if (strcmp(line, "id") == 0) {
        cap1188_print_id_register("Product ID: ", CAP1188_REG_PRODUCT_ID);
        cap1188_print_id_register("Manufacturer ID: ", CAP1188_REG_MANUFACTURER_ID);
        cap1188_print_id_register("Revision: ", CAP1188_REG_REVISION);
    }
    else if (strcmp(line, "help") == 0) {
        usart2_write_string("Commands: led, millis, id, help\r\n");
    }
    else if (line[0] != '\0') {
        usart2_write_string("Unknown command: ");
        usart2_write_string(line);
        usart2_write_string("\r\n");
    }
}

int main(void)
{
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* Errata: the clock can take 2 AHB cycles to start. Reading the enable
    * register back waits that out before GPIOA is touched. */
    (void)RCC_AHB1ENR;

    GPIOA_MODER = (GPIOA_MODER & ~GPIOA_MODER5_MASK)
                | ((GPIO_MODE_OUTPUT << GPIOA_MODER5_POS) & GPIOA_MODER5_MASK);

    i2c1_init();
    usart2_init();

    usart2_write_string("Hello from USART2\r\n");

    systick_start_1ms();

    char line[LINE_BUFFER_SIZE];
    uint32_t line_length = 0u;

    usart2_write_string("> ");
    for (;;) {
        char typed = usart2_read_byte();
        if (typed == '\r') {
            usart2_write_string("\r\n");
            line[line_length] = '\0';
            run_command(line);
            line_length = 0u;
            usart2_write_string("> ");
        }
        else if ((typed == '\b') || (typed == ASCII_DEL)) {
            if (line_length > 0u) {
                line_length--;
                usart2_write_string("\b \b");
            }
        }
        else if (line_length < (LINE_BUFFER_SIZE - 1u)) {
            line[line_length] = typed;
            line_length++;
            usart2_write_byte(typed);
        }
    }
}
