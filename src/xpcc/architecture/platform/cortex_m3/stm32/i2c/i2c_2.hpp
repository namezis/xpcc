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

#ifndef XPCC_STM32__I2C_2_HPP
#define XPCC_STM32__I2C_2_HPP

#include <stdint.h>
#include <xpcc/driver/connectivity/i2c/master.hpp>

#include "../device.h"

namespace xpcc
{
	namespace stm32
	{
		/**
		 * @brief		I2C2 Module.
		 * 
		 * @author		Georgi Grinshpun
		 * @author		Niklas Hauser
		 * @ingroup		stm32
		 */
		class I2c2 : ::xpcc::i2c::Master
		{
		public:
			enum Mapping
			{
#if defined(STM32F2XX) || defined(STM32F4XX)
				REMAP_PB10_PB11,	///< SCL mapped to PB10, SDA mapped to PB11
				REMAP_PF1_PF0,		///< SCL mapped to PF1, SDA mapped to PF0
				REMAP_PH4_PH5,		///< SCL mapped to PH4, SDA mapped to PH5
#else
				REMAP_PB10_PB11,						///< SCL mapped to PB10, SDA mapped to PB11
#endif
			};
			
			/**
			 * Configure the IO Pins for I2C2
			 */
			static void
			configurePins(Mapping mapping);
			
			/**
			 * @brief	Initialize I2C module
			 * \param ccrPrescaler: I2CFrequency = STM32_APB1_FREQUENCY / (2 * ccrPrescaler)
			 */
			static void
			initialize(uint16_t ccrPrescaler);
			
			static void
			reset();
			
		public:
			static bool
			start(uint8_t slaveAddress);
			
			static void
			restart(uint8_t slaveAddress);
			
			static void
			read(uint8_t *data, std::size_t size, xpcc::i2c::OperationParameter param = xpcc::i2c::READ_STOP);
			
			static void
			write(uint8_t *data, std::size_t size, xpcc::i2c::OperationParameter param = xpcc::i2c::READ_STOP);
			
			static void
			writeRead(uint8_t *data, std::size_t writeSize, std::size_t readSize, xpcc::i2c::OperationParameter param = xpcc::i2c::READ_STOP);
			
			static void
			attachDelegate(xpcc::i2c::Delegate *object);
			
			static xpcc::i2c::ErrorState
			getErrorState();
			
			static xpcc::i2c::BusyState
			getBusyState();
			
			static xpcc::i2c::BusState
			getBusState();
			
		public:
			ALWAYS_INLINE
			static bool
			startWrite(uint8_t slaveAddress, uint8_t *data, std::size_t size, xpcc::i2c::OperationParameter param = xpcc::i2c::WRITE_STOP)
			{
				if (start(slaveAddress)) {
					writeRead(data, size, 0, (param == xpcc::i2c::WRITE_RESTART), false);
					return true;
				}
				return false;
			}
			
			ALWAYS_INLINE
			static bool
			startRead(uint8_t slaveAddress, uint8_t *data, std::size_t size, xpcc::i2c::OperationParameter param = xpcc::i2c::READ_STOP)
			{
				if (start(slaveAddress)) {
					writeRead(data, 0, size, false, (param == xpcc::i2c::READ_RESTART));
					return true;
				}
				return false;
			}
			
			ALWAYS_INLINE
			static bool
			startWriteRead(uint8_t slaveAddress, uint8_t *data, std::size_t writeSize, std::size_t readSize, xpcc::i2c::OperationParameter param = xpcc::i2c::READ_STOP)
			{
				if (start(slaveAddress)) {
					writeRead(data, writeSize, readSize, false, (param == xpcc::i2c::READ_RESTART));
					return true;
				}
				return false;
			}
			
		public:
			ALWAYS_INLINE
			static void
			stop();
			
		private:
			static void
			writeRead(uint8_t *data, std::size_t writeSize, std::size_t readSize, bool restartW, bool restartR);
		};
	}
}

#endif // XPCC_STM32__I2C_2_HPP