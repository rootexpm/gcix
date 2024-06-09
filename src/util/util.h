#pragma once

namespace util
{
	bool isDllLoaded(const char* dllName) noexcept;
	void waitForDll(const char* dllName) noexcept;
}