#pragma once
#include <windows.h>
#include <vector>

namespace mem
{
	bool WriteCalltoMemory(BYTE* dataAddr, const void* JMPAddr, DWORD count = 5);
	void Patch(BYTE* dst, BYTE* src, unsigned int size);
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void Nop(BYTE* dst, unsigned int size);
	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);
	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
	bool WriteJMPtoMemory(BYTE* dataAddr, const void* JMPAddr, DWORD count = 5);
	bool UpdateMemoryAddress(void* dataAddr, const void* dataBytes, size_t dataSize);
}