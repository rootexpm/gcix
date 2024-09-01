#pragma once

namespace console
{
    extern bool console_initialized;

    void Setup() noexcept;
    void Destroy() noexcept;
    void Print(const char* format, ...) noexcept;
    void DebugPrint(const char* format, ...) noexcept;
    void PrintImportant(const char* format, ...) noexcept;
    void AgoraPrint(int a1, int a2, int a3, int a4, char* Format, ...) noexcept;
}