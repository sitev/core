#include "cj.h"

namespace cj {

//#pragma comment ( lib, "ws2_32.lib" )  // добавил сам стротроку. т.к не находил библиотеку без этой строки хоть в консоли и прописывал "ws2_2.lib"
//#include <stdio.h>
//#include <windows.h>

//--------------------------------------------------------------------------------------------------
//----------          Socket         ---------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
Socket::Socket() {
	m_sock = -1;
	init();
}

Socket::Socket(SOCKET sock) {
	m_sock = sock;
	init();
}

void Socket::init() {
	memset(&m_addr, 0, sizeof(m_addr));
	fNonBlocking = false;
	error = false;
	sendRequest = false;
}

Socket::~Socket() {
	if (isValid()) {
#ifdef OS_LINUX
		::close(m_sock);
#endif
		m_sock = -1;
	}
}

bool Socket::create() {
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	bool flag = isValid();
	if (flag) {
		int on = 1;
#ifdef OS_LINUX
		flag = (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == 0);
#endif
	}
	return flag;
}

bool Socket::create(int domain, int type, int protocol) {
	m_sock = socket(domain, type, protocol);
	bool flag = isValid();
	if (flag) {
		int on = 1;
#ifdef OS_LINUX
		flag = (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == 0);
#endif
	}
	return flag;
}

int Socket::getCurSize() {
	if (!isValid()) return 0;
	int len;
	char buf[MAXRECV];
	len = ::recv(m_sock, buf, MAXRECV, MSG_PEEK);
	return len;
}
int Socket::recv(String &s) {
	if (!isValid()) return 0;
	char buf[MAXRECV + 1];
	memset(buf, 0, MAXRECV + 1);
	int len = ::recv(m_sock, buf, MAXRECV, 0);
	s = buf;
	return len;
}

int Socket::recv(void *buffer, int size) {
	if (!isValid()) return 0;
	memset(buffer, 0, size);
	int len = 0;
	if (fNonBlocking) {
//#ifdef OS_LINUX
		len = ::recv(m_sock, (char*)buffer, size, 0 /*MSG_DONTWAIT*/);
//#endif
	}
	else {
//#ifdef OS_LINUX1
		len = ::recv(m_sock, (char*)buffer, size, 0);
//#endif
	}
	return len;
}

int Socket::recv(Memory &memory) {
	int size = this->getCurSize();
	int pos = memory.getPos();
	memory.setSize(size + pos);
	int len = this->recv(((char*)memory.data) + pos, size);
	return len;
}


int Socket::send(String s) {
	if (!isValid()) return 0;
//	int len = ::send(m_sock, s.toChars(), s.getLength(), 0);
	int len = send((void*)s.toString8().c_str(), s.getLength());
	return len;
}

int Socket::send(void *buffer, int size) {
	if (!isValid()) return 0;
	int len = ::send(m_sock, (char*)buffer, size, 0);
	printf(" send %d\n", len);
	if (len == -1) error = true;
	return len;
}

int Socket::send(Memory &memory) {
	return this->send(memory.data, memory.getSize());
}

bool Socket::sendAll(void *buffer, int size) {
	if (!isValid()) return 0;
	char *ptr = (char*) buffer;

	int counter = 0;
	while (size > 0)
	{
		int sz = ::send(m_sock, ptr, size, 0);
		usleep(1000);
		if (sz < 1) {
			counter++;
			if (counter > 10000) return false;
			continue;
		}
		ptr += sz;
		size -= sz;
	}
	return true;
}

bool Socket::sendAll(Memory &memory) {
	return this->sendAll(memory.data, memory.getSize());
}

void Socket::setNonBlocking(bool b) {
	if (!isValid()) return;
	fNonBlocking = b;

	int opts = 0;
#ifdef OS_LINUX
	opts = fcntl(m_sock, F_GETFL);
#endif
	if (opts < 0) return;

#ifdef OS_LINUX
	if (b)
		opts = (opts | O_NONBLOCK);
	else
		opts = (opts & ~O_NONBLOCK);

	fcntl(m_sock, F_SETFL, opts);
	//fcntl(m_sock, F_SETFL, O_NONBLOCK);
#endif

#ifdef OS_WINDOWS
	u_long iMode = fNonBlocking;
	ioctlsocket(m_sock, FIONBIO, &iMode);
#endif
}
bool Socket::isValid() {
	return m_sock != -1;
}
bool Socket::isError() {
	return error;
}
void Socket::setError(bool error) {
	this->error = error;
}
bool Socket::getSendRequest() {
	return sendRequest;
}
void Socket::setSendRequest(bool value) {
	sendRequest = value;
}

void Socket::close() {
	if (isValid()) {
#ifdef OS_LINUX
		::close(m_sock);
#endif
#ifdef OS_WINDOWS
		::closesocket(m_sock);
#endif
		m_sock = -1;
	}
}


//--------------------------------------------------------------------------------------------------
//----------          ClientSocket         ---------------------------------------------------------
//--------------------------------------------------------------------------------------------------
/*
 ClientSocket::ClientSocket() {
 }

 ClientSocket::~ClientSocket() {
 }

 bool ClientSocket::init() {
 // Шаг 1 - инициализация библиотеки Winsock
 char buff[1024];
 if (WSAStartup(0x202, (WSADATA *)&buff[0]))
 {
 //printf("WSAStart error %d\n", WSAGetLastError());
 return false;
 }
 return true;
 }
 int ClientSocket::getLastError() {
 return WSAGetLastError();
 }

 bool ClientSocket::create() {
 // Шаг 2 - создание сокета
 //SOCKET my_sock;

 my_sock = socket(AF_INET, SOCK_STREAM, 0);
 if (my_sock < 0)
 {
 //printf("Socket() error %d\n", WSAGetLastError());
 return false;
 }
 return true;
 }

 bool ClientSocket::connect(String serveraddr, int port) {
 // Шаг 3 - установка соединения
 // заполнение структуры sockaddr_in - указание адреса и порта сервера
 sockaddr_in dest_addr;
 dest_addr.sin_family = AF_INET;
 dest_addr.sin_port = htons(port);
 HOSTENT *hst;

 // преобразование IP адреса из символьного в сетевой формат
 if (inet_addr(serveraddr.toChars()) != INADDR_NONE)
 dest_addr.sin_addr.s_addr = inet_addr(serveraddr.toChars());
 else
 {
 // попытка получить IP адрес по доменному имени сервера
 if (hst = gethostbyname(serveraddr.toChars()))
 // hst->h_addr_list содержит не массив адресов,
 // а массив указателей на адреса
 ((unsigned long *)&dest_addr.sin_addr)[0] =
 ((unsigned long **)hst->h_addr_list)[0][0];
 else
 {
 //printf("Invalid address %s\n", SERVERADDR);
 closesocket(my_sock);
 WSACleanup();
 return false;
 }
 }

 // адрес сервера получен - пытаемся установить соединение
 if (::connect(my_sock, (sockaddr *)&dest_addr, sizeof(dest_addr)))
 {
 //printf("Connect error %d\n", WSAGetLastError());
 return false;
 }
 return true;
 }

 int ClientSocket::send(String s) {
 char buff[1024];
 // Шаг 4 - чтение
 // передаем строку клиента серверу
 ::send(my_sock, &buff[0], strlen(&buff[0]), 0);
 return 0;
 }

 String ClientSocket::recv() {
 char buff[1024];
 // Шаг 4 - чтение
 int nsize;
 while ((nsize = ::recv(my_sock, &buff[0], sizeof(buff) - 1, 0)) != SOCKET_ERROR)
 {
 // ставим завершающий ноль в конце строки
 buff[nsize] = 0;

 // выводим на экран
 //printf("S=>C:%s", buff);

 // читаем пользовательский ввод с клавиатуры
 //printf("S<=C:"); fgets(&buff[0], sizeof(buff) - 1, stdin);

 // проверка на "quit"
 if (!strcmp(&buff[0], "quit\n"))
 {
 // Корректный выход
 //printf("Exit...");
 closesocket(my_sock);
 WSACleanup();
 return "";
 }
 }
 return buff;
 }

 String ClientSocket::recvall() {
 String s = "";
 while (true) {
 String subs = recv();
 if (subs.getLength() == 0) break;
 s += subs;
 }
 return s;
 }
 */

ClientSocket::ClientSocket() {

}

ClientSocket::ClientSocket(SOCKET sock) : Socket(sock) {

}

ClientSocket::~ClientSocket() {

}

bool ClientSocket::connect(String host, int port) {
	if (!isValid())
		return false;

	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(port);

	int status = 0;
#ifdef OS_LINUX
	status = inet_pton(AF_INET, host.toString8().c_str(), &m_addr.sin_addr);
#endif

//	if (errno == EAFNOSUPPORT)
//		return false;

	status = ::connect(m_sock, (sockaddr *) &m_addr, sizeof(m_addr));

	if (status == 0)
		return true;
	else
		return false;
}


ServerSocket1::ServerSocket1() {
}

ServerSocket1::ServerSocket1(SOCKET sock) {

}

ServerSocket1::~ServerSocket1() {
}

//--------------------------------------------------------------------------------------------------
//----------          ServerSocket         ---------------------------------------------------------
//--------------------------------------------------------------------------------------------------

ServerSocket::ServerSocket() : Socket() {
}

ServerSocket::ServerSocket(SOCKET sock) : Socket(sock) {

}

ServerSocket::~ServerSocket() {
}

bool ServerSocket::create() {
#ifdef OS_WINDOWS
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"Error at WSAStartup()\n");
		return 1;
	}
#endif
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	bool flag = isValid();
	if (flag) {
		int on = 1;
#ifdef OS_LINUX
		flag = (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == 0);
#endif
	}
	return flag;
}

bool ServerSocket::create(int domain, int type, int protocol) {
#ifdef OS_WINDOWS
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"Error at WSAStartup()\n");
		return 1;
	}
#endif
	m_sock = socket(domain, type, protocol);
	bool flag = isValid();
	if (flag) {
		int on = 1;
#ifdef OS_LINUX
		flag = (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == 0);
#endif
	}
	return flag;
}

bool ServerSocket::bind(int port) {
	return bind(port, AF_INET, INADDR_ANY);
}

bool ServerSocket::bind(int port, ushort family, uint addr) {
	if (!isValid()) return false;

	m_addr.sin_port = htons(port);
	m_addr.sin_family = family;
	m_addr.sin_addr.s_addr = htonl(addr);

	int result = ::bind(m_sock, (struct sockaddr*) &m_addr, sizeof(m_addr));
	int err1 = errno;
	printf("error = %s\n", strerror(err1));
	return result >= 0;
}

bool ServerSocket::listen() {
	return listen(MAXCONNECTIONS);
}

bool ServerSocket::listen(int connCount) {
	if (!isValid()) return false;
	int result = ::listen(m_sock, connCount);//MAXCONNECTIONS);
	return result >= 0;
}

bool ServerSocket::accept() {
	int addr_length = sizeof(m_addr);
#ifdef OS_LINUX
	int new_sock = ::accept(m_sock, (sockaddr *) &m_addr, (socklen_t *) &addr_length);
#endif
#ifdef OS_WINDOWS
	int new_sock = ::accept(m_sock, (sockaddr *)&m_addr, &addr_length);
#endif
	if (new_sock <= 0) return false;

	Socket *sock = new Socket(new_sock);
	sock->setNonBlocking(this->fNonBlocking);
	lstSocket.add(sock);
	LOGGER_TRACE("Socket added ...");
	return true;
}
void ServerSocket::setNonBlocking(bool b) {
	Socket::setNonBlocking(b);
}

}
