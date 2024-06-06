#include <winsock2.h>
#include "client2.h"
#include <iostream>
#include <string>

     // Put here the IP address of the server
char szServerIPAddr[ 20 ] = "192.168.1.16" ;     // Put here the IP address of the server
int nServerPort = 5050 ;                     // The server port that will be used by                                            // clients to talk with the server

bool InitWinSock2_0(void) ;
SOCKET hClientSocket;
void closeSocket(void);
void sendMessage(char* szBuffer);
int init(void);
void recieve(void);

using namespace std;

string line;

/*inittialises the client by using the IP and port which is always 5050

	Winsock connect function is used to create an inputstream from the server to client
	init(void) - asks for IP, and utilises winsock API to connect to the server

*/
int client2::init()
{
    cout << "Enter the server IP Address. Or type 0 for offline: " ;
    cin >> szServerIPAddr ;
	//88.111.26.107
    //cout << "Enter the server port number: " ;
    //cin >> nServerPort ;
	//cout << "Enter the server IP Address: " ;
    //cin >> szServerIPAddr ;
    //cout << "Enter the server port number: " ;
   // cin >> nServerPort ; 

		if ( ! InitWinSock2_0( ) )
		{
			cout << "Unable to Initialize Windows Socket environment" << WSAGetLastError( ) << endl ;
			return -1 ;
		}


		hClientSocket = socket(
			AF_INET,        // The address family. AF_INET specifies TCP/IP
			SOCK_STREAM,    // Protocol type. SOCK_STREM specified TCP
			0               // Protoco Name. Should be 0 for AF_INET address family
			) ;
		if ( hClientSocket == INVALID_SOCKET )
		{
			cout << "Unable to create Server socket" << endl ;
			// Cleanup the environment initialized by WSAStartup()
			WSACleanup( ) ;
			return -1 ;
		}

		nServerPort = 5050 ; 
		// Create the structure describing various Server parameters
		struct sockaddr_in serverAddr ;

		serverAddr . sin_family = AF_INET ;     // The address family. MUST be AF_INET
		serverAddr . sin_addr . s_addr = inet_addr( szServerIPAddr ) ;
		serverAddr . sin_port = htons( nServerPort ) ;

		// Connect to the server
		if ( connect( hClientSocket, ( struct sockaddr * ) &serverAddr, sizeof( serverAddr ) ) < 0 )
		{
			cout << "Unable to connect to " << szServerIPAddr << " on port " << nServerPort << endl ;
			closesocket( hClientSocket ) ;
			WSACleanup( ) ;
			return -1 ;
		}

	   // char szBuffer[ 1024 ] = "" ;
		
		string word = "hello";
		int n = word.length();  
		  
		// declaring character array 
		char szBuffer[n+1]; 
		  
		// copying the contents of the  
		// string to char array 
		strcpy(szBuffer, word.c_str());
		cout << "connected" << endl;
		sendMessage(szBuffer);
	//}else{
	//	cout << "Unable to connect to " << szServerIPAddr << " on port " << nServerPort << endl ;
     //   closesocket( hClientSocket ) ;
      //  WSACleanup( ) ;
	//	return 0;
	//}
   return 1;
   // return 0 ;
}
/*
	sendMessage(char array of string to send) - sets up the socket to be able to send the message
	first using a buffer and using winsock "send function"
*/
void client2::sendMessage(char* szBuffer){
	//cout << "Enter the string to send (QUIT) to stop: " ;
        //cin >> szBuffer ;
		

        int nLength = strlen( szBuffer ) ;

        // send( ) may not be able to send the complete data in one go.
        // So try sending the data in multiple requests
        int nCntSend = 0 ;
        char *pBuffer = szBuffer ;

        while ( ( nCntSend = send( hClientSocket, pBuffer, nLength, 0 ) != nLength ) )
        {
            if ( nCntSend == -1 )
            {
                cout << "Error sending the data to server" << endl ;
                break ;
            }
            if ( nCntSend == nLength )
                break ;

            pBuffer += nCntSend ;
            nLength -= nCntSend ;

        }

        strupr( szBuffer ) ;        
}
void client2::recieve(){
	char szBuffer[ 1024 ] = "" ;
	 int nLength = strlen( szBuffer ) ;
	nLength = recv( hClientSocket, szBuffer, sizeof( szBuffer ), 0 ) ;
        if ( nLength > 0 )
        {
            szBuffer[ nLength ] = '\0' ;
			//cout << "Received " << szBuffer << " from server" << endl ;
			line = szBuffer;
		 
		}
}
// closes the socket, and cleans up the pointers
void client2::closeSocket(){
	 closesocket( hClientSocket ) ;
    WSACleanup( ) ;

}
//makes sure that winsock can be used on the computer, normally if the program is compiled it should work
bool client2::InitWinSock2_0( )
{
    WSADATA wsaData ;
    WORD wVersion = MAKEWORD( 2, 0 ) ;

    if ( ! WSAStartup( wVersion, &wsaData ) )
        return true ;

    return false ;
}
