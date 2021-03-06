/*  Sirikata
 *  asyncCraqUtil.hpp
 *
 *  Copyright (c) 2010, Behram Mistree
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of Sirikata nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __SET_ASYNC_THREE_UTIL_HPP__
#define __SET_ASYNC_THREE_UTIL_HPP__

#include "../craq_oseg/asyncUtil.hpp"
#include <string>

namespace Sirikata
{
  const int  STREAM_CRAQ_DATA_KEY_QUERY_SIZE       = CRAQ_DATA_KEY_SIZE + CRAQ_DATA_PREFIX_SIZE + CRAQ_DATA_SUFFIX_SIZE + 1;//have to add +1 for Z suffix
  typedef char StreamCraqDataKeyQuery[STREAM_CRAQ_DATA_KEY_QUERY_SIZE];  //this is what actually goes out to the router.


  const char STREAM_CRAQ_TO_SET_SUFFIX[]         =  "YZ";


  //good
  const int STREAM_CRAQ_DATA_SET_SIZE       = CRAQ_DATA_SET_PREFIX_SIZE + CRAQ_DATA_KEY_SIZE + CRAQ_DATA_TO_SET_SIZE_SIZE + CRAQ_DATA_SET_END_LINE_SIZE + CRAQ_DATA_VALUE_SIZE + CRAQ_DATA_SET_END_LINE_SIZE +1 + 1; //another + 1 for adding Z suffix

  typedef char StreamCraqDataSetQuery[STREAM_CRAQ_DATA_SET_SIZE];  //this is what actually goes out to the router.


  //good
  //  const char STREAM_CRAQ_NOT_FOUND_RESP[]    = "NOT_FOUND";
  const char STREAM_CRAQ_STORED_RESP[]       =    "STORED";
  const char STREAM_CRAQ_VALUE_RESP[]        =     "VALUE";
  const char STREAM_CRAQ_ERROR_RESP[]        =     "ERROR";

  //good
  const int STREAM_CRAQ_NOT_FOUND_RESP_SIZE  =           9;
  const int STREAM_CRAQ_STORED_RESP_SIZE     =           6;
  const int STREAM_CRAQ_VALUE_RESP_SIZE      =           5;
  const int STREAM_CRAQ_ERROR_RESP_SIZE      =           5;

  //good
  const char STREAM_DATA_KEY_SUFFIX = 'Z';

  const int STREAM_SIZE_SIZE_TAG_GET_RESPONSE =2;


  const int STREAM_CRAQ_NUM_CONNECTIONS_SET        = 30;
  const int STREAM_CRAQ_NUM_CONNECTIONS_GET        = 50;

  const int STREAM_ASYNC_GET_TIMEOUT_MILLISECONDS  = 400000; //this is in ms
  const int STREAM_ASYNC_SET_TIMEOUT_MILLISECONDS  = 400000; //essentially infinity

  const char STREAM_CRAQ_READ_RESULT_UNTIL_REGEX[] = "YY\r\n";
  const char STREAM_CRAQ_READ_ERROR_RESULT_UNTIL_REGEX[] = "ERROR\r\n";


  const int MAX_GET_PREV_READ_FRAG_SIZE    = 200;
  const int CUT_GET_PREV_READ_FRAG         = 100;

  const int MAX_SET_PREV_READ_FRAG_SIZE    = 200;
  const int CUT_SET_PREV_READ_FRAG         = 100;


}//namespace

#endif
