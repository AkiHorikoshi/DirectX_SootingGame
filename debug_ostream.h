/*=================================================================

		簡単デバック出力 [debug_ostream.h]

											Author : Youhei Sato
											Date   : 2025/4/21

=================================================================*/

#ifndef DEBUG_OSTERAM_H
#define DEBUG_OSTREAM_H

#include <Windows.h>
#include <sstream>

namespace hal
{
	class debugbuf : public std::basic_stringbuf<char, std::char_traits<char>>
	{
	public:
		virtual ~debugbuf()
		{
			sync();
		}

	protected:
		int sync()
		{
			OutputDebugStringA(str().c_str());
			str(std::basic_string<char>());
			return 0;
		}
	};

	class debug_ostream : public std::basic_ostream<char, std::char_traits<char>>
	{
	public:
		debug_ostream() 
			: std::basic_ostream<char, std::char_traits<char>>(new debugbuf()){}
		~debug_ostream() { delete rdbuf(); }
	};

	extern debug_ostream dout;
}

#endif //DEBUG_OSTERAM_H