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

#if !defined(GPIO_H)
#define GPIO_H

//#include "Display.h"
#include "Timer.h"
#include "Modem.h"

#include <string>
#include <vector>

//#include <mcp23017.h>
//#include <pcf8574.h>

class CModem;

class GPIOStat
{
public:
        GPIOStat(CModem* modem, bool enabled, unsigned int gpiopin, bool debug);
//        virtual ~GPIOSTAT();

        bool open();
        void clock(unsigned int ms);

        void enable(bool enabled);
        void amplifierPower(bool enabled);
//        virtual void close();

//protected:
//        virtual void clearCWInt();

private:
        CModem*         m_modem;

        CTimer m_statusTimer;
        unsigned int m_gpiopin;
        bool m_enabled;
        bool m_debug;



};
#endif
