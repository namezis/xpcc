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
 * $Id: bounded_stack_test.cpp 607 2011-09-13 19:51:03Z dergraaf $
 */
// ----------------------------------------------------------------------------

#include <xpcc/container/stack.hpp>

#include "bounded_stack_test.hpp"

void
BoundedStackTest::testStack()
{
	xpcc::BoundedStack<int16_t, 3> stack;
	
	TEST_ASSERT_TRUE(stack.isEmpty());
	TEST_ASSERT_EQUALS(stack.getMaxSize(), 3);
	
	TEST_ASSERT_TRUE(stack.push(1));
	TEST_ASSERT_TRUE(stack.push(2));
	TEST_ASSERT_TRUE(stack.push(3));
	
	TEST_ASSERT_FALSE(stack.push(4));
	TEST_ASSERT_TRUE(stack.isFull());
	
	TEST_ASSERT_EQUALS(stack.get(), 3);
	stack.pop();
	
	TEST_ASSERT_EQUALS(stack.get(), 2);
	stack.pop();
	
	TEST_ASSERT_TRUE(stack.push(4));
	TEST_ASSERT_TRUE(stack.push(5));
	TEST_ASSERT_TRUE(stack.isFull());
	
	TEST_ASSERT_EQUALS(stack.get(), 5);
	stack.pop();
	
	TEST_ASSERT_EQUALS(stack.get(), 4);
	stack.pop();
	
	TEST_ASSERT_EQUALS(stack.get(), 1);
	stack.pop();
	
	TEST_ASSERT_TRUE(stack.isEmpty());
}
