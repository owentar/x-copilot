#ifndef X_COPILOT_LOGGER_H
#define X_COPILOT_LOGGER_H

#include <string>

#include <boost/format.hpp>
#include <boost/log/trivial.hpp>

namespace xcopilot {
    class Logger {
    public:
        enum Level {
            DEBUG = boost::log::trivial::severity_level::debug,
            INFO = boost::log::trivial::severity_level::info,
            WARN = boost::log::trivial::severity_level::warning,
            ERROR = boost::log::trivial::severity_level::error,
            FATAL = boost::log::trivial::severity_level::fatal
        };

        static Logger* getInstance();

        static void configureFileLogger(Logger::Level level = Logger::Level::INFO, const std::string& fileName = "xcopilot.log");

        static void configureConsoleLogger(Logger::Level level = Logger::Level::INFO);

        void debug(const std::string &message) { log(message, Logger::Level::DEBUG); };
        void debug(const boost::format &message) { log(message.str(), Logger::Level::DEBUG); };

        void info(const std::string &message) { log(message, Logger::Level::INFO); };
        void info(const boost::format &message) { log(message.str(), Logger::Level::INFO); };

        void warn(const std::string &message) { log(message, Logger::Level::WARN); };
        void warn(const boost::format &message) { log(message.str(), Logger::Level::WARN); };

        void error(const std::string &message) { log(message, Logger::Level::ERROR); };
        void error(const boost::format &message) { log(message.str(), Logger::Level::ERROR); };

        void fatal(const std::string &message) { log(message, Logger::Level::FATAL); };
        void fatal(const boost::format &message) { log(message.str(), Logger::Level::FATAL); };

    private:
        Logger();

        Logger(Logger const &);

        Logger &operator=(Logger const &);

        virtual ~Logger() = default;

        static Logger* instance;

        boost::log::sources::severity_logger<boost::log::trivial::severity_level> logger;

        void log(const std::string &message, Logger::Level level);
    };
}


#endif //X_COPILOT_LOGGER_H
