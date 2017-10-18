#include "DebugLogger.h"

#include <Windows.h>

#include <iostream>

using std::cout;
using std::endl;

const int DebugLogger::LOG_MESSAGE_COLOUR = 7;
const int DebugLogger::LOG_SUBMESSAGE_COLOUR = 8;
const int DebugLogger::LOG_WARNING_COLOUR = 14;
const int DebugLogger::LOG_ERROR_COLOUR = 12;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void DebugLogger::LogMessage(const std::string &message)
{
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << message << " " << endl;
}

void DebugLogger::LogNotification(const std::string &source, const std::string &notification)
{
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << "[" << source << "] ";
	SetConsoleTextAttribute(hConsole, LOG_SUBMESSAGE_COLOUR);
	cout << notification << endl;
}

void DebugLogger::LogSubMessage(const std::string &subMessage)
{
	SetConsoleTextAttribute(hConsole, LOG_SUBMESSAGE_COLOUR);
	cout << "  " << subMessage << endl;
}

void DebugLogger::LogWarning(const std::string &message)
{
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << "[";
	SetConsoleTextAttribute(hConsole, LOG_WARNING_COLOUR);
	cout << "Warning";
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << "] ";
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << message << endl;
}

void DebugLogger::LogError(const std::string &message)
{
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << "[";
	SetConsoleTextAttribute(hConsole, LOG_ERROR_COLOUR);
	cout << "Error";
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << "] ";
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << message << endl;
}

void DebugLogger::LogError(const std::string &message, const std::string &sub)
{
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << "[";
	SetConsoleTextAttribute(hConsole, LOG_ERROR_COLOUR);
	cout << "Error";
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << "] ";
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << message << " ";
	SetConsoleTextAttribute(hConsole, LOG_SUBMESSAGE_COLOUR);
	cout << sub << endl;
}

void DebugLogger::LogError(const std::string &source, const std::string &message, const std::string &sub)
{
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << "[";
	SetConsoleTextAttribute(hConsole, LOG_ERROR_COLOUR);
	cout << "Error";
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << "] ";
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << "[" << source << "] ";
	SetConsoleTextAttribute(hConsole, LOG_MESSAGE_COLOUR);
	cout << message << " ";
	SetConsoleTextAttribute(hConsole, LOG_SUBMESSAGE_COLOUR);
	cout << sub << endl;
}

