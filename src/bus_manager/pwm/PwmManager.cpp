/*
 * PwmManager.cpp
 *
 *  Created on: Jul 21, 2018
 *      Author: bigbywolf
 */

#include "PwmManager.h"

#include <inc/hw_memmap.h>
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/interrupt.h>
#include "driverlib/debug.h"

#include "PwmPins.h"

namespace pwm
{

    PwmManager::PwmManager(PWMBlock pwmBlock) :
            m_pwmBlock(pwmBlock){
    }

    void PwmManager::begin() {
        SysCtlPeripheralEnable( MCU_PWM[m_pwmBlock].pwm_periph );
        SysCtlPeripheralEnable( MCU_PWM[m_pwmBlock].periph_port );

        GPIOPinConfigure( MCU_PWM[m_pwmBlock].pwma_config );
        GPIOPinConfigure( MCU_PWM[m_pwmBlock].pwmb_config  );

        GPIOPinTypePWM( MCU_PWM[m_pwmBlock].port_base, MCU_PWM[m_pwmBlock].pwma_pin);
        GPIOPinTypePWM( MCU_PWM[m_pwmBlock].port_base, MCU_PWM[m_pwmBlock].pwmb_pin );

        PWMGenConfigure( MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwm_gen,
                         PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    }

    PwmManager::~PwmManager() {

    }

    bool PwmManager::setPWM(PWMOutput out, uint32_t freq_hz, uint32_t duty_pct, bool enable) {
        if ((0 == freq_hz) || (duty_pct > 100)) {
            return false;
        }

        // use the following equation: N = (SysClk / f)
        PWMGenPeriodSet(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwm_gen, SysCtlClockGet() / freq_hz);

        if(out == PWMOutput::pwm_a){
            // duty = (period * percent) / 100
            PWMPulseWidthSet(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwma_out,
                             (PWMGenPeriodGet(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwm_gen) * duty_pct) / 100);

            // enable output
            PWMOutputState(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwma_out_bit, enable);
        }
        else {
            PWMPulseWidthSet(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwmb_out,
                             (PWMGenPeriodGet(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwm_gen) * duty_pct) / 100);

            PWMOutputState(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwmb_out_bit, enable);
        }

        // enable generator block
        PWMGenEnable( MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwm_gen);

        return true;
    }

    uint32_t PwmManager::getFreqHz(void) {
        // f = SysClock / N
        return SysCtlClockGet() / PWMGenPeriodGet(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwm_gen);
    }

    uint32_t PwmManager::getDutyPct(PWMOutput out) {
        // percent = (duty * 100) / period
        if(out == PWMOutput::pwm_a){
            return (PWMPulseWidthGet(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwma_out) * 100) /
                   PWMGenPeriodGet(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwm_gen);
        }
        else {
            return (PWMPulseWidthGet(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwmb_out) * 100) /
                   PWMGenPeriodGet(MCU_PWM[m_pwmBlock].pwm_base, MCU_PWM[m_pwmBlock].pwm_gen);
        }
    }


} /* namespace pwm */
