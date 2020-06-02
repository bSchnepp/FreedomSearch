/*
Copyright (c) 2020, Brian Schnepp

Permission is hereby granted, free of charge, to any person or organization 
obtaining  a copy of the software and accompanying documentation covered by 
this license (the "Software") to use, reproduce, display, distribute, execute, 
and transmit the Software, and to prepare derivative works of the Software, 
and to permit third-parties to whom the Software is furnished to do so, all 
subject to the following:

The copyright notices in the Software and this entire statement, including 
the above license grant, this restriction and the following disclaimer, must 
be included in all copies of the Software, in whole or in part, and all 
derivative works of the Software, unless such copies or derivative works are 
solely in the form of machine-executable object code generated by a source 
language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY 
DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.
 */
 
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <unordered_map>

#include "HTTPMethod.hpp"
#include "Server.hpp"

using tcp = boost::asio::ip::tcp;

FreedomHTTP::Server::Server() 
	: FreedomHTTP::Server::Server(8080)
{

}

FreedomHTTP::Server::Server(uint16_t Port)
{
	this->Port = Port;
}
	
void FreedomHTTP::Server::Run()
{
	boost::asio::io_context IOContext;
	tcp::acceptor Acceptor(IOContext,
		tcp::endpoint(tcp::v4(), this->Port));
			
	for (;;)
	{
		try
		{
			tcp::socket Socket(IOContext);
			Acceptor.accept(Socket);
			boost::system::error_code IgnoredError;
			
			std::string Message = "Hello, world!\n";
			
			boost::asio::write(
				Socket, boost::asio::buffer(Message), 
				IgnoredError);
		} catch (std::exception &Exception) {
			std::cerr << Exception.what() << std::endl;
		}
	}
}

bool FreedomHTTP::Server::Mount(std::string Location, EndpointHandler Handler)
{
	return false;
}

bool FreedomHTTP::Server::Umount(std::string Location)
{
	return false;
}
