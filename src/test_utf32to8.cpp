#include <string>
#include <vector>
#include <iostream>


using namespace std;


int main(int argc, _TCHAR* argv[])
{
	vector<int> u32 = { 1055, 1088, 1080, 1074, 1077, 1090, 44, 32, 1084, 1080, 1088, 33 };
	string s = "";
	for (auto i = 0; i < u32.size(); i++) {

		int v = u32[i];
		cout << v << " " << endl;

		if (v <= 0x7f) {
			s += (char)(v & 0x7f);
		}
		else if (v <= 0x7ff) {
			int a = 0xc0 + ((v & 0x7c0) >> 6);
			int b = 0x80 + (v & 0x3f);
			s += (char)a;
			s += (char)b;
		}
	}
	cout << s << endl;

	vector<int> u32a;
	int i = 0;
	int len = s.length();
	while (i < len) {
		unsigned char a = s[i];
		if (a <= 0x7f) {
			u32a.push_back(a);
		}
		else {
			i++;
			unsigned char b = s[i];
			int v = ((a & 0x1f) << 6) + (b & 0x3f);
			u32a.push_back(v);
		}
		i++;
	}

	return 0;
}

