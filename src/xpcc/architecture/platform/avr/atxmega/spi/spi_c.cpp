// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2011, Roboterclub Aachen e.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Roboterclub Aachen e.V. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
// ----------------------------------------------------------------------------
/*
 * WARNING: This file is generated automatically, do not edit!
 * Please modify the corresponding *.in file instead and rebuild this file. 
 */
// ----------------------------------------------------------------------------

#include "spi_c.hpp"
#include <avr/interrupt.h>
#include <xpcc/architecture/driver/gpio.hpp>

#ifdef SPIC

namespace
{
	GPIO__OUTPUT(SCK, C, 7);
	GPIO__INPUT(MISO, C, 6);
	GPIO__OUTPUT(MOSI, C, 5);
	GPIO__OUTPUT(SS, C, 4);
}

// ----------------------------------------------------------------------------
void
xpcc::atxmega::SpiMasterC::initialize(SPI_PRESCALER_t prescaler, 
		bool doubleSpeed, SPI_MODE_t mode)
{
	SS::setOutput();
	MOSI::setOutput();
	SCK::setOutput();
	MISO::setInput(PULLUP);
	
	SPIC_CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | mode;
	
	setPrescaler(prescaler, doubleSpeed);
}

uint8_t
xpcc::atxmega::SpiMasterC::write(uint8_t data)
{
	SPIC_STATUS;
	SPIC_DATA = data;
	
	while (!(SPIC_STATUS & SPI_IF_bm))
		;
	
	return SPIC_DATA;
}

#endif // SPIC