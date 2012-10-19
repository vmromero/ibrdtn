/*
 * socketstream.h
 *
 * Copyright (C) 2011 IBR, TU Braunschweig
 *
 * Written-by: Johannes Morgenroth <morgenroth@ibr.cs.tu-bs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef SOCKETSTREAM_H_
#define SOCKETSTREAM_H_

#include "ibrcommon/net/socket.h"
#include "ibrcommon/net/vsocket.h"
#include <streambuf>
#include <iostream>

namespace ibrcommon
{
	class socketstream : public std::basic_streambuf<char, std::char_traits<char> >, public std::iostream
	{
	public:
		enum stream_error
		{
			ERROR_NONE = 0,
			ERROR_EPIPE = 1,
			ERROR_CLOSED = 2,
			ERROR_WRITE = 3,
			ERROR_READ = 4,
			ERROR_RESET = 5
		};

		socketstream(basesocket *sock, size_t buffer_size = 5120);
		virtual ~socketstream();

		void close();

		stream_error errmsg;

	protected:
		virtual int sync();
		virtual std::char_traits<char>::int_type overflow(std::char_traits<char>::int_type = std::char_traits<char>::eof());
		virtual std::char_traits<char>::int_type underflow();

	private:
		vsocket _socket;
		const size_t _bufsize;

		// Input buffer
		char *in_buf_;
		// Output buffer
		char *out_buf_;
	};
} /* namespace ibrcommon */
#endif /* SOCKETSTREAM_H_ */
