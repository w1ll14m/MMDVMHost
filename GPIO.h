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

/*
 * GPIO written in 2023 by PD9WP
 */

#if !defined(GPIO_H)
#define GPIO_H

#include "Timer.h"
#include "Modem.h"

#include <string>
#include <vector>

//class CModem;

class GPIOStat
{
public:
        GPIOStat(CModem* modem, bool enabled, unsigned int gpiopin, bool debug);

        bool open();

        void clock(unsigned int ms);
        void enable(bool enabled);
        void amplifierPower(bool enabled);

private:
        CModem*         m_modem;

        CTimer m_statusTimer;
        CTimer m_amplifierTimer;

        unsigned int m_gpiopin;
        bool m_enabled;
        bool m_debug;
};
#endif
