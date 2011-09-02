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
 *
 * $Id$
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_FREERTOS__TASK_HPP
#define XPCC_FREERTOS__TASK_HPP

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

/**
 * \brief	Create a timed periodic loop
 * 
 * Example:
 * \code
 * void
 * Task::run()
 * {
 *     TIME_LOOP(20 * MILLISECONDS)
 *     {
 *         // will be executed every 20ms
 *     }
 * }
 * \endcode
 * 
 * \param	frequency	Frequency in ticks
 * 
 * \see		MILLISECONDS
 * \see		vTaskDelayUntil() from FreeRTOS
 * 
 * \hideinitializer
 * \ingroup	freertos
 */
#define	TIME_LOOP(frequency)										\
		for(portTickType lastTime = xTaskGetTickCount() ;			\
			vTaskDelayUntil(&lastTime,								\
					static_cast<portTickType>(frequency)), true ;	\
			)

/**
 * \brief	Convert between scheduler ticks and milliseconds
 * 
 * For example 20 ms in scheduler ticks might be written as:
 * \code
 * 20 * MILLISECONDS
 * \endcode
 * 
 * This should only be used with constant values as the calculation is done
 * using floating point. For constant values the compiler will do the calculation
 * at compile time.
 * 
 * For non constant value use the following formula:
 * \code
 * static_cast<portTickType>((time * configTICK_RATE_HZ) / 1000)
 * \endcode
 * The parentheses are important because otherwise the division might be done
 * first which will lead to wrong results.
 * 
 * \hideinitializer
 * \ingroup	freertos
 */
#define	MILLISECONDS		(configTICK_RATE_HZ / 1000.0)

namespace xpcc
{
	namespace freertos
	{
		/**
		 * \brief	Task
		 * 
		 * \ingroup	freertos
		 */
		class Task
		{
		public:
			/**
			 * \brief	Create a task
			 * 
			 * \param	priority	Priority (default is 0)
			 * \param	stackDepth	Stack size for the task
			 * \param	name		Name of the task (only used for debugging,
			 * 						can be left empty)
			 * 
			 * \warning	Tasks may not be created while the scheduler is running!
			 * 			Create them be before calling Scheduler::schedule() or
			 * 			stop the scheduler and restart it afterwards.
			 */
			Task(unsigned portBASE_TYPE priority = 0,
					unsigned short stackDepth = configMINIMAL_STACK_SIZE,
					const char* name = NULL);
			
			/// Delete the task
			virtual ~Task();
			
			/// Obtain the priority of the task
			unsigned portBASE_TYPE
			getPriority() const;
			
			/**
			 * \brief	Set the priority of the task
			 * 
			 * Might cause a context switch if the priority is set to lower
			 * value than the highest priority of a task ready to run.
			 */
			void
			setPriority(unsigned portBASE_TYPE priority);
			
			/**
			 * \brief	Suspend the Task
			 * 
			 * The task won't be executed until the next call of resume() or
			 * resumeFromInterrupt().
			 */
			void
			suspend();
			
			/**
			 * \brief	Resume execution of the task
			 * 
			 * \warning	Must \b not be called from within an interrupt!
			 */
			void
			resume();
			
			/**
			 * \brief	Resume execution from within an interrupt context
			 */
			void
			resumeFromInterrupt();
			
			/**
			 * \brief	Suspends all real time kernel activity while keeping
			 * 			interrupts (including the kernel tick) enabled.
			 * 
			 * After calling suspendAll() the calling task will continue
			 * to execute without risk of being swapped out until a call to
			 * resumeAll() has been made.
			 * 
			 * API functions that have the potential to cause a context switch
			 * (for example, delay()) must not be called while the scheduler
			 * is suspended.
			 * 
			 * \see		resumeAll()
			 */
			void
			suspendAll();
			
			/// Resumes real time kernel activity following a call to suspendAll()
			void
			resumeAll();
			
		protected:
			/**
			 * \brief	Delay for the number of ticks
			 * 
			 * Use the MILLISECONDS macro to convert ticks to milliseconds:
			 * \code
			 * delay(10 * MILLISECONDS);
			 * \endcode 
			 * 
			 * \param	ticks	Number of scheduler ticks to delay for
			 * \see		MILLISECONDS
			 */
			static inline void
			delay(portTickType ticks)
			{
				vTaskDelay(ticks);
			}
			
			// TODO
			//delayUntil();
			
			/**
			 * \brief	Force a context switch
			 * 
			 * Gives control to other tasks ready to run.
			 */
			static inline void
			yield()
			{
				taskYIELD();
			}
			
			/**
			 * \brief	Worker function
			 * 
			 * Must be implemented to never return (i.e. continuous loop)
			 */
			virtual void
			run() = 0;
			
		private:
			static void
			wrapper(void *object);
			
			// disable copy constructor
			Task(const Task& other);
			
			// disable assignment operator
			Task&
			operator = (const Task& other);
			
			xTaskHandle handle;
		};
	}
}

#endif // XPCC_FREERTOS__TASK_HPP