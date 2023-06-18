/*
 *   Copyright (C) 2016,2017,2018,2020,2021 by Jonathan Naylor G4KLX & Tony Corbett G0WFV
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "GPIO.h"
#include "Log.h"

#include <wiringPi.h>
#include <softPwm.h>
#include <lcd.h>
#include <pthread.h>

#include <cstdio>
#include <cassert>
#include <cstring>
#include "Modem.h"


GPIOStat::GPIOStat(CModem* modem, bool enabled, unsigned int gpiopin, bool debug) :
m_modem(modem),
m_statusTimer(1000U, 0U, 10U),
m_amplifierTimer(1000U, 0U, 5000U),
m_gpiopin(gpiopin),
m_debug(debug),
m_currentStatus(false)
{
}


bool GPIOStat::open()
{
        ::wiringPiSetup();

        pinMode (m_gpiopin, OUTPUT) ;

        digitalWrite (m_gpiopin, HIGH) ; delay (500) ;
        digitalWrite (m_gpiopin,  LOW) ; delay (500) ;

        return true;
}

void GPIOStat::enable(bool enabled)
{
        m_enabled=enabled;
        if(enabled) {
                m_statusTimer.start();
         } else {
                m_statusTimer.stop();
                m_amplifierTimer.stop();
         }
}


void GPIOStat::clock(unsigned int ms)
{
        m_statusTimer.clock(ms);
        if (m_statusTimer.hasExpired()) {
                bool status=m_modem->hasTX();
                if(status) {
                        m_amplifierTimer.start();
                        if(!getAmplifierPower())
                                setAmplifierPower(status);
                }
                if(m_debug)
                        LogMessage("GPIO statusTimer expired. Status: %i", status);
                m_statusTimer.start();

        }

        m_amplifierTimer.clock(ms);
        if (m_amplifierTimer.hasExpired()) {
                bool status=m_modem->hasTX();
                if(!status)
                        setAmplifierPower(false);
                if(m_debug)
                        LogMessage("GPIO amplifierTimer expired. Status: %i", status);
                m_amplifierTimer.start();
        }
}

bool GPIOStat::getAmplifierPower() {
        return m_currentStatus;
}

void GPIOStat::setAmplifierPower(bool enabled) {
        if(m_enabled) {
                if(m_currentStatus != enabled) {
                        m_currentStatus=enabled;
                        if (enabled) {
                                digitalWrite (m_gpiopin, HIGH);
                                LogMessage("GPIO Amplifier ON!");
                        } else {
                                digitalWrite (m_gpiopin, LOW);
                                LogMessage("GPIO Amplifier OFF!");

                        }
                }

        }
}
