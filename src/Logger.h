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
            INFO = boost::log::trivial::severity_level::info
        };

        static Logger* getInstance();

        static void configureFileLogger(Logger::Level level = Logger::Level::INFO, const std::string& fileName = "xcopilot.log");

        static void configureConsoleLogger(Logger::Level level = Logger::Level::INFO);

        void trace(const std::string &message) { log(message, boost::log::trivial::severity_level::trace); };
        void trace(const boost::format &message) { log(message.str(), boost::log::trivial::severity_level::trace); };

        void debug(const std::string &message) { log(message, boost::log::trivial::severity_level::debug); };
        void debug(const boost::format &message) { log(message.str(), boost::log::trivial::severity_level::debug); };

        void info(const std::string &message) { log(message, boost::log::trivial::severity_level::info); };
        void info(const boost::format &message) { log(message.str(), boost::log::trivial::severity_level::info); };

        void warn(const std::string &message) { log(message, boost::log::trivial::severity_level::warning); };
        void warn(const boost::format &message) { log(message.str(), boost::log::trivial::severity_level::warning); };

        void error(const std::string &message) { log(message, boost::log::trivial::severity_level::error); };
        void error(const boost::format &message) { log(message.str(), boost::log::trivial::severity_level::error); };

        void fatal(const std::string &message) { log(message, boost::log::trivial::severity_level::fatal); };
        void fatal(const boost::format &message) { log(message.str(), boost::log::trivial::severity_level::fatal); };

    private:
        Logger();

        Logger(Logger const &);

        Logger &operator=(Logger const &);

        virtual ~Logger() = default;

        static Logger* instance;

        boost::log::sources::severity_logger<boost::log::trivial::severity_level> logger;

        void log(const std::string &message, boost::log::trivial::severity_level level);
    };
}


#endif //X_COPILOT_LOGGER_H
