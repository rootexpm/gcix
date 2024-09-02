#include "console.h"

#include <Windows.h>
#include <cstdio>
#include <cstdarg>
#include <fstream>

bool debug_log = true; // This can be set to 0 or 1 to control the logging behavior
std::ofstream logStream;
bool console::console_initialized = false;

void console::Setup() noexcept
{
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
	freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
	freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w", stderr);

	char title[256];
	sprintf_s(title, sizeof(title), "gcix - %s %s", __DATE__, __TIME__);
	SetConsoleTitleA(title);

	console::console_initialized = true;
}

void console::Destroy() noexcept
{
	fclose(reinterpret_cast<FILE*>(stdout));
	fclose(reinterpret_cast<FILE*>(stdin));
	fclose(reinterpret_cast<FILE*>(stderr));
	FreeConsole();
}
// Function to generate filename
void generate_filename(char* filename, size_t size) {
	strncpy(filename, "logging.log", size);
}

// Function to log messages to a file
void custom_log(const char* message) {
	if (!console::console_initialized || !debug_log) return;

	if (!logStream.is_open()) {
		logStream.open("logging.log", std::ios::app);
		if (!logStream) {
			console::Print("Failed to open log file");
			return;
		}
	}
	logStream << message << std::flush;
}

void console::AgoraPrint(int a1, int a2, int a3, int a4, char* Format, ...) noexcept
{
	if (!console::console_initialized)
		return;

	char Buffer[2564];
	va_list va;

	va_start(va, Format);

	vsprintf_s(Buffer, sizeof(Buffer), Format, va);

	if (Buffer[strlen(Buffer) - 1] != '\n')
		strcat_s(Buffer, "\n");

	printf("Log: %s\n", Buffer);
	custom_log(Buffer);

	va_end(va);
}

void console::Print(const char* format, ...) noexcept
{
	if (!console::console_initialized)
		return;

	va_list args;
	va_start(args, format);

	printf_s("[gcix] ");
	vprintf_s(format, args);
	printf_s("\n");

	va_end(args);
}



void console::DebugPrint(const char* format, ...) noexcept
{
	if (!console::console_initialized)
		return;

	va_list args;
	va_start(args, format);

	// Create a new format string with the prefix
	char prefixed_format[2046];
	snprintf(prefixed_format, sizeof(prefixed_format), "[gcix] %s", format);

	if (prefixed_format[strlen(prefixed_format) - 1] != '\n')
		strcat_s(prefixed_format, "\n");

	vprintf(prefixed_format, args);

	// Reset the va_list to log the message
	va_end(args);
	va_start(args, format);
	char buffer[2046];
	vsnprintf(buffer, sizeof(buffer), prefixed_format, args);
	va_end(args);

	// Log to file
	custom_log(buffer);

	va_end(args);
}