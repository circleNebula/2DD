#ifndef CLIENT2_H
#define CLIENT2_H
#include <string>
#include <winsock2.h>


class client2
{
	public:
		int init(void);
		void sendMessage(char* szBuffer);
		void recieve(void);
		std::string line;
	protected:
	private:
    // Put here the IP address of the server
		int nServerPort;                    // The server port that will be used by                                            // clients to talk with the server
		bool InitWinSock2_0(void) ;
		SOCKET hClientSocket;
		void closeSocket(void);
};

#endif //Client2