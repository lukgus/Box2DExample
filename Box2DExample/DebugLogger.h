#ifndef DEBUG_LOGGER_HG
#define DEBUG_LOGGER_HG

#include <string>

class DebugLogger
{
public:
	static void LogMessage(const std::string &message);
	static void LogNotification(const std::string &main, const std::string &sub);
	static void LogSubMessage(const std::string &message);
	static void LogWarning(const std::string &message);

	static void LogError(const std::string &message);
	static void LogError(const std::string &message, const std::string &sub);
	static void LogError(const std::string &source, const std::string &message, const std::string &sub);
private:
	static const int LOG_MESSAGE_COLOUR;
	static const int LOG_SUBMESSAGE_COLOUR;
	static const int LOG_WARNING_COLOUR;
	static const int LOG_ERROR_COLOUR;
};

#endif
