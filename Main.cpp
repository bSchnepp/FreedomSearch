/* clang++ Main.cpp -lpthread */

#include <cstdint>
#include <iostream>

#include <boost/asio.hpp>
#include <unordered_map>

/* May refactor this to it's own library in the future... */
namespace FreedomHTTP
{

using tcp = boost::asio::ip::tcp;

typedef enum HTTPMethod
{
	HTTP_METHOD_GET,
	HTTP_METHOD_HEAD,
	HTTP_METHOD_POST,
	HTTP_METHOD_PUT,
	HTTP_METHOD_DELETE,
	HTTP_METHOD_TRACE,
	HTTP_METHOD_CONNECT,
}HTTPMethod;

typedef std::string (*EndpointHandler)(void *Data, std::string Input);

class Server
{
public:
	Server()
	{
		this->Port = 8080;
	}
	
	Server(uint16_t Port)
	{
		this->Port = Port;
	}
	
	virtual ~Server()
	{
	
	}
	
	
	void Run()
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
	
	bool Mount(std::string Location, EndpointHandler Handler)
	{
		return false;
	}
	
	bool Umount(std::string Location)
	{
		return false;
	}
	
protected:
	std::unordered_map<std::string, EndpointHandler> Mounts;
	uint16_t Port;
};

}

int main(int argc, char **argv)
{
	FreedomHTTP::Server Server(80);
	Server.Run();
	return 0;
}
