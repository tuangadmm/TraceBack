#include <Windows.h>
#include <iostream>

#ifndef TRACEBACK_H


uintptr_t	DereferencePointer(HANDLE processHandle, void* address, int offset[], size_t size);


//Return address that given pointer points to
//Require processHandle has PROCESS_VM_READ
//Pointer : "process" + offset1 ] + offset2 ] + ... + offsetN
//Take baseAddress as base module address and offset[]
uintptr_t DereferencePointer(HANDLE processHandle, void* baseAddress, int offset[], size_t size) {


	uintptr_t	addr = reinterpret_cast<uintptr_t>(baseAddress);	//module base address
	uintptr_t	currentAddr = addr + (uintptr_t)offset[0];		//offset1 is added to module base address
	uintptr_t	tempAddr = 0;	//hold recent address returned by ReadProcessMemory

	if (size == 1) {	//pointer has 1 offset
		if (ReadProcessMemory(processHandle, (LPCVOID)currentAddr, &tempAddr, sizeof(uintptr_t), NULL)) {
			return tempAddr;
		}
		else {
			std::cerr << "[TraceBack] {size = 1; error = " << GetLastError() << "}" << std::endl;
			return 0;
		}
	}
	else if (size == 2) {		//pointer has 2 offsets
		std::cout << std::hex << currentAddr << std::endl;
		if (ReadProcessMemory(processHandle, (LPCVOID)currentAddr, &tempAddr, sizeof(uintptr_t), NULL)) {
			std::cout << std::hex << tempAddr << std::endl;

			return tempAddr + offset[1];
		}
		else {
			std::cerr << "[TraceBack] {size = 2; error = " << GetLastError() << "}" << std::endl;
			return 0;
		}
	}
	else {		//pointer has more than 2 offsets 
		for (size_t i = 1; i < (size); ++i) {
			if (ReadProcessMemory(processHandle, (LPCVOID)currentAddr, &tempAddr, sizeof(uintptr_t), NULL)) {
				currentAddr = tempAddr + offset[i];
			}
			else {
				std::cerr << "[TraceBack] {size = " << size << "; error = " << GetLastError() << "; level = " << i + 1 << "}" << std::endl;
				return 0;
			}
		}
		return currentAddr;	
	}
}
#endif

