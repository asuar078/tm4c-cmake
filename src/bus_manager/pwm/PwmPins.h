//
// Created by bigbywolf on 7/25/18.
//

#ifndef TM4C_CMAKE_PWMPINS_H
#define TM4C_CMAKE_PWMPINS_H

#include <stdint.h>

namespace pwm
{
    struct Buspins {
        uint32_t pwm_periph;
        uint32_t periph_port;
        uint32_t pwma_config;
        uint32_t pwmb_config;
        uint32_t port_base;
        uint8_t pwma_pin;
        uint8_t pwmb_pin;
        uint32_t pwm_base;
        uint32_t pwm_gen;
        uint32_t pwma_out;
        uint32_t pwmb_out;
        uint32_t pwma_out_bit;
        uint32_t pwmb_out_bit;
    };


#ifdef PART_TM4C123GH6PM

    static const uint8_t NUM_OF_PWM = 8;
    static const Buspins MCU_PWM[NUM_OF_PWM] = {

            /* pwm_periph, periph_port, pwma_config, pwmb_config, port_base,
             * pwma_pin, pwmb_pin, pwm_base, pwm_gen, pwma_out, pwmb_out, pwma_out_bit, pwmb_out_bit */
            {SYSCTL_PERIPH_PWM0, SYSCTL_PERIPH_GPIOB, GPIO_PB6_M0PWM0, GPIO_PB7_M0PWM1, GPIO_PORTB_BASE,
                    GPIO_PIN_6, GPIO_PIN_7, PWM0_BASE, PWM_GEN_0, PWM_OUT_0, PWM_OUT_1, PWM_OUT_0_BIT, PWM_OUT_1_BIT},

            {SYSCTL_PERIPH_PWM0, SYSCTL_PERIPH_GPIOB, GPIO_PB4_M0PWM2, GPIO_PB5_M0PWM3, GPIO_PORTB_BASE,
                    GPIO_PIN_4, GPIO_PIN_5, PWM0_BASE, PWM_GEN_1, PWM_OUT_2, PWM_OUT_3, PWM_OUT_2_BIT, PWM_OUT_3_BIT},

            {SYSCTL_PERIPH_PWM0, SYSCTL_PERIPH_GPIOE, GPIO_PE4_M0PWM4, GPIO_PE5_M0PWM5, GPIO_PORTE_BASE,
                    GPIO_PIN_4, GPIO_PIN_5, PWM0_BASE, PWM_GEN_2, PWM_OUT_4, PWM_OUT_5, PWM_OUT_4_BIT, PWM_OUT_5_BIT},

            {SYSCTL_PERIPH_PWM0, SYSCTL_PERIPH_GPIOC, GPIO_PC4_M0PWM6, GPIO_PC5_M0PWM7, GPIO_PORTC_BASE,
                    GPIO_PIN_4, GPIO_PIN_5, PWM0_BASE, PWM_GEN_3, PWM_OUT_6, PWM_OUT_7, PWM_OUT_6_BIT, PWM_OUT_7_BIT},

            {SYSCTL_PERIPH_PWM1, SYSCTL_PERIPH_GPIOD, GPIO_PD0_M1PWM0, GPIO_PD1_M1PWM1, GPIO_PORTD_BASE,
                    GPIO_PIN_0, GPIO_PIN_1, PWM1_BASE, PWM_GEN_0, PWM_OUT_0, PWM_OUT_1, PWM_OUT_0_BIT, PWM_OUT_1_BIT},

            {SYSCTL_PERIPH_PWM1, SYSCTL_PERIPH_GPIOA, GPIO_PA6_M1PWM2, GPIO_PA7_M1PWM3, GPIO_PORTA_BASE,
                    GPIO_PIN_6, GPIO_PIN_7, PWM1_BASE, PWM_GEN_1, PWM_OUT_2, PWM_OUT_3, PWM_OUT_2_BIT, PWM_OUT_3_BIT},

            {SYSCTL_PERIPH_PWM1, SYSCTL_PERIPH_GPIOF, GPIO_PF0_M1PWM4, GPIO_PF1_M1PWM5, GPIO_PORTF_BASE,
                    GPIO_PIN_0, GPIO_PIN_1, PWM1_BASE, PWM_GEN_2, PWM_OUT_4, PWM_OUT_5, PWM_OUT_4_BIT, PWM_OUT_5_BIT},

            {SYSCTL_PERIPH_PWM1, SYSCTL_PERIPH_GPIOF, GPIO_PF2_M1PWM6, GPIO_PF3_M1PWM7, GPIO_PORTF_BASE,
                    GPIO_PIN_2, GPIO_PIN_3, PWM1_BASE, PWM_GEN_3, PWM_OUT_6, PWM_OUT_7, PWM_OUT_6_BIT, PWM_OUT_7_BIT}
    };

#else
#error "microcontroller not supported"
#endif

}

#endif //TM4C_CMAKE_PWMPINS_H
