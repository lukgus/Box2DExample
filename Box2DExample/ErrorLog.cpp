/* cErrorLog.cpp
*
* This class writes messages to a logfile that you specify.
* Each call to WriteErrorMessageToLogFile is on it's seperateline
* unless false is specified to continue where you left off.
*
* Contributors: Lukas Gustafson
* Date: January 27, 2016
*/

// Example of usage:
//cErrorLog* theLogger = cErrorLog::GetInstance();
//theLogger->CreateErrorLogFile("MyError.log");
//theLogger->WriteErrorMessageToLogFile("This is my error!");
//theLogger->WriteErrorMessageToLogFile("This is my other error!");
//theLogger->WriteErrorMessageToLogFile("The position of the ship is: ", false);
//theLogger->WriteErrorMessageToLogFile(ship->position.ToString());

#include "ErrorLog.h"

#include <fstream>
#include <sstream>

// Static instance of the class must be declared in the .cpp file.
ErrorLog* ErrorLog::m_pInstance;

/*
* cErrorLog - Default Constructor
* Just sets the default base file path to logs/
*/
ErrorLog::ErrorLog(void)
{
	m_BaseFilePath = "logs/";
	m_ErrorLogFileName = "ErrorList.log";

	return;
}

/*
* cErrorLog - Default Destructor
*
*/
ErrorLog::~ErrorLog(void)
{
	return;
}

/*
* SetBaseFilePath
* Sets the base file path for all of the error logs
* Default is in the Project Directory in the folder "logs/"
* @param baseFilePath - The new base file path for all of the log files
*/
void ErrorLog::SetBaseFilePath(std::string baseFilePath)
{
	m_BaseFilePath = baseFilePath;

	return;
}

/*
* GetBaseFilePath
* Retrieves the current base file path for the error logs
* @return the base file path
*/
std::string ErrorLog::GetBaseFilePath(void)
{
	return m_BaseFilePath;
}


/*
* GetInstance
* Singleton caller.  Creates an instance of the class if it
* does not already exist.  Returns the instance of the class.
*
* @return - the single instance of the class
*/
ErrorLog* ErrorLog::GetInstance(void)
{
	if (m_pInstance == 0)
	{
		m_pInstance = new ErrorLog();
	}
	return m_pInstance;
}

/*
* CreateErrorLogFile
* Creates a log file to output errors to.  The date, time, and other
* required information will be printed at the top of the created log
* file.  The name of the file gets saved in one of the class's parameters.
* @param - the name of the log file to create
*/
void ErrorLog::CreateErrorLogFile(std::string errorLogFileName)
{
	// Save the file name
	m_ErrorLogFileName = errorLogFileName;

	// Create the file
	std::ofstream errorLog(m_BaseFilePath + m_ErrorLogFileName);

	// Check if the file created/opened
	if (!errorLog.is_open())
	{
		// Welp we can't write this in a log..
		return;
	}

	// Close the file
	errorLog.close();

	return;
}

/*
* UseErrorLogFile
* Changes the current log file to another one.  This does not
* Clear or add a new header to the error file.  It just switches
* it so log files can be written in seperately if needed.
* @param - the name of the log file to create
*/
void ErrorLog::UseErrorLogFile(std::string errorLogFileName)
{
	// Save the file name
	m_ErrorLogFileName = errorLogFileName;

	return;
}

/*
* WriteErrorMessageToLogFile
* Writes an error message in the log file
* @param message - the message to write to the file
*/
void ErrorLog::WriteErrorMessageToLogFile(std::string message, bool newLine)
{
	// Open the file 
	std::ofstream errorLog;
	errorLog.open(m_BaseFilePath + m_ErrorLogFileName, std::ios::app);

	// Check if the file opened
	if (!errorLog.is_open())
	{
		// Welp we can't write this in the log..
		return;
	}

	// Move cursor to the end of the file
	errorLog.seekp(0, errorLog.end);

	// Write the message
	errorLog.write(message.c_str(), message.length());

	if (newLine)
	{
		errorLog.write("\n", 1);
	}

	// Close the file
	errorLog.close();

	return;
}

/*
* WriteErrorMessageToLogFile
* Writes an error message in the log file
* @param message - the message to write to the file
*/
void ErrorLog::WriteErrorMessageToLogFile(int message, bool newLine)
{
	std::stringstream ss;
	ss << message;
	WriteErrorMessageToLogFile(ss.str().c_str(), newLine);

	return;
}

