#include "console.h"

#include <Windows.h>
#include <cstdio>
#include <cstdarg>

bool log = TRUE; // This can be set to 0 or 1 to control the logging behavior
FILE* Stream = nullptr;

void console::Setup() noexcept
{
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
	freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
	freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w", stderr);

	char title[256];
	sprintf_s(title, sizeof(title), "gcix - %s %s", __DATE__, __TIME__);
	SetConsoleTitleA(title);
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
	char FileName[260];

	if (log) {
		if (!Stream) {
			generate_filename(FileName, sizeof(FileName));
			Stream = fopen(FileName, "a");
			if (!Stream) {
				perror("Failed to open log file");
				return;
			}
		}
		fputs(message, Stream);
		fflush(Stream);
	}
	else {
		if (Stream) {
			fclose(Stream);
			Stream = nullptr;
		}
	}
}

void console::PrintImportant(const char* format, ...) noexcept
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	// Save current attributes
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;

	// Set text color to green
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

	va_list args;
	va_start(args, format);

	printf_s("[gcix] ");
	vprintf_s(format, args);
	printf_s("\n");

	va_end(args);

	// Restore original attributes
	SetConsoleTextAttribute(hConsole, saved_attributes);
}

void console::AgoraPrint(int a1, int a2, int a3, int a4, char* Format, ...) noexcept
{
	char Buffer[2564]; // Buffer to store the formatted message
	va_list va;

	// Initialize va_list with the variable arguments
	va_start(va, Format);

	// Format the message
	vsprintf_s(Buffer, sizeof(Buffer), Format, va);

	// Print the message to the console
	printf("Log: %s\n", Buffer);
	custom_log(Buffer);

	// Call the original function with the original arguments
	va_end(va);
}

void console::Print(const char* format, ...) noexcept
{
	va_list args;
	va_start(args, format);

	printf_s("[gcix] ");
	vprintf_s(format, args);
	printf_s("\n");

	va_end(args);
}



void console::DebugPrint(const char* format, ...) noexcept
{
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
	//custom_log(buffer);

	va_end(args);
}