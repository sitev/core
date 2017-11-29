#pragma once

namespace core {

	class String;

	int round(real value);
	void swap(int &A, int &B);
	void swap(real &A, real &B);
	void showMessage(String msg);
	real random(); // 0..1
	int random(int count); // 0..count-1
	String generateUUID();
	String generateSimpleUUID();
#ifdef OS_WINDOWS
	void usleep(big usec);
#endif
#ifdef OS_LINUX
	ulong GetTickCount();
#endif
	ulong getUsageMemory();
	void sendMail(String toEMail, String fromEMail, String subject, String message);
	void sendMail_s(string toEMail, string fromEMail, string subject, string message);
	String dtRus(String dtUsa, int format);

}