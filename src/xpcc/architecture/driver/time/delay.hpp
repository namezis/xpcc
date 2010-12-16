// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2009, Roboterclub Aachen e.V.
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
 *
 * $Id$
 */
// ----------------------------------------------------------------------------

#ifndef	XPCC__DELAY_HPP
#define	XPCC__DELAY_HPP

#ifdef __DOXYGEN__

namespace xpcc
{
	/**
	 * \brief	Delay us microseconds
	 * \ingroup	architecture
	 */
	void
	delay_us(float us);
	
	/**
	 * \brief	Delay ms milliseconds
	 * \ingroup	architecture
	 */
	void
	delay_ms(float ms);
}

#else // !__DOXYGEN__

#if defined(__AVR__)
	
	#include <util/delay.h>
	#include <xpcc/architecture/platform.hpp>
	
	namespace xpcc
	{
		ALWAYS_INLINE void
		delay_us(float us)
		{
			_delay_us(us);
		}
		
		ALWAYS_INLINE void
		delay_ms(float ms)
		{
			_delay_ms(ms);
		}
	}

#elif defined(__unix__)

	#include <unistd.h>
	#include <xpcc/architecture/platform.hpp>
	
	namespace xpcc
	{
		ALWAYS_INLINE void
		delay_us(int us)
		{
			usleep(us);
		}
		
		ALWAYS_INLINE void
		delay_ms(int ms)
		{
			usleep(ms*1000);
		}
	}
	
#elif defined(_WIN32)
	#include <xpcc/architecture/platform.hpp>
	
	namespace xpcc
	{
		// FIXME implement this functions
		inline void
		delay_us(int /*us*/)
		{
		}
		
		inline void
		delay_ms(int /*ms*/)
		{
		}
	}
	
#else
	#error "Unknown architecture, please add some specific delay functions!"
#endif

#endif	// !__DOXYGEN__
#endif	// XPCC__DELAY_HPP