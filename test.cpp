#include "TraceBack.h"

int main() {
	//this test check for Plants vs. Zombies Steam GOTY  Edition Sun address
	//base bodule address = 0x0400000
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 1824);
	int offset[2] = { 0x331C50 , 0x868, 0x5578 };
	int		size = sizeof(offset) / sizeof(offset[0]);

	std::cout << std::hex << std::uppercase << "0x0" << DereferencePointer(hProc, (void*)0x0400000, offset, size);
	std::cin.get();
}
