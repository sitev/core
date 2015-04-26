#pragma once

#include "cj.h"

namespace cj {

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 1024;

class Socket : public Object {
protected:
#ifdef OS_LINUX
#define SOCKET int
#endif
	SOCKET m_sock;
	sockaddr_in m_addr;
	bool fNonBlocking, error, sendRequest;
public:
	Socket();
	Socket(SOCKET sock);
	virtual void init();
	virtual ~Socket();
	virtual bool create();
	virtual bool create(int domain, int type, int protocol);

	virtual int getCurSize();
	virtual int recv(String &s);
	virtual int recv(void *buffer, int size);
	virtual int recv(Memory &memory);
	virtual int send(String s);
	virtual int send(void *buffer, int size);
	virtual int send(Memory &memory);

	virtual bool sendAll(void *buffer, int size);
	virtual bool sendAll(Memory &memory);

	virtual void setNonBlocking(bool);
	virtual bool isValid();
	virtual bool isError();
	virtual void setError(bool error);

	virtual bool getSendRequest();
	virtual void setSendRequest(bool value);

	virtual void close();
};

class ClientSocket : public Socket {
public:
	ClientSocket();
	ClientSocket(SOCKET sock);
	virtual ~ClientSocket();

	virtual bool connect(String host, int port);
};

class ServerSocket : public Socket {
public:
	List lstSocket;
	ServerSocket();
	virtual ~ServerSocket();

	virtual bool create();
	virtual bool create(int domain, int type, int protocol);
	virtual bool bind(int port);
	virtual bool bind(int port, ushort family, uint addr);
	virtual bool listen();
	virtual bool listen(int connCount);
	virtual bool accept();
	virtual void setNonBlocking(bool);
};

}
