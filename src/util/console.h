#pragma once

namespace console
{
	void Setup() noexcept;
	void Destroy() noexcept;
	void Print(const char* format, ...) noexcept;
}