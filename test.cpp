#include <iostream>
#include "TraceBack.h"



int main() {

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 1824);
	int offset[2] = { 0x331C50 , 0x868 };
	int		size = sizeof(offset) / sizeof(offset[0]);		//offsets array size

	std::cout << std::hex << std::uppercase << "0x0" << DereferencePointer(hProc, (void*)0x0400000, offset, size);




	std::cin.get();
}