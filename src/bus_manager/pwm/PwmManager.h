/*
 * PwmManager.h
 *
 *  Created on: Jul 21, 2018
 *      Author: bigbywolf
 */

#ifndef LIB_PWM_PWMMANAGER_H_
#define LIB_PWM_PWMMANAGER_H_

#include <stdint.h>
#include <stdbool.h>

namespace pwm
{

    enum PWMBlock {
        M0PWM0_1 = 0, M0PWM2_3, M0PWM4_5, M0PWM6_7, M1PWM0_1, M1PWM2_3, M1PWM4_5, M1PWM6_7
    };

    enum class PWMOutput {
        pwm_a = 0, pwm_b
    };

    class PwmManager
    {
    public:
        PwmManager(PWMBlock pwmBlock);
        virtual ~PwmManager();

        void begin();

        PWMBlock getPWMBlock(void) {
            return m_pwmBlock;
        }

        uint32_t getFreqHz(void);
        uint32_t getDutyPct(PWMOutput out);

        /**
         * Set the frequency for generator and duty cycle for specific output.
         * @param out: which pwm output to use. Freq is the same for both outputs, only duty cycle different.
         * @param freq_hz: frequency in Hz of PWM output desired
         * @param duty_pct:  duty cycle 0-100
         * @param enable: enable pwm output
         * @return true if successful, false otherwise
         */
        bool setPWM(PWMOutput out, uint32_t freq_hz, uint32_t duty_pct, bool enable = true);

    private:
        PWMBlock m_pwmBlock;
    };

} /* namespace pwm */

#endif /* LIB_PWM_PWMMANAGER_H_ */
