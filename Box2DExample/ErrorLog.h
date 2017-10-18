/* cErrorLog.h
*
* This class is a singleton that creates a error log file
* for errots to be outputed.  This is really needed because
* we are running this game without a console to output
* information.
*
* Contributors: Lukas Gustafson
* Date: January 27, 2016
*/

#ifndef ERROR_LOG_HG
#define ERROR_LOG_HG

#include <string>

class ErrorLog
{
public:
	~ErrorLog(void);
	static ErrorLog* GetInstance(void);

	void SetBaseFilePath(std::string baseFilePath);
	std::string GetBaseFilePath(void);

	void CreateErrorLogFile(std::string errorLogFileName);
	void UseErrorLogFile(std::string errorLogFileName);
	void WriteErrorMessageToLogFile(std::string message, bool newLine = true);
	void WriteErrorMessageToLogFile(int message, bool newLine = true);

private:
	ErrorLog(void);
	static ErrorLog* m_pInstance;

	std::string m_BaseFilePath;
	std::string m_ErrorLogFileName;
};

#endif
