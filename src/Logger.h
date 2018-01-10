#ifndef X_COPILOT_LOGGER_H
#define X_COPILOT_LOGGER_H

#include <string>

#include <boost/log/trivial.hpp>

namespace xcopilot {
    class Logger {
    public:
        static Logger* getInstance();

        void debug(const std::string &message) { log(message, boost::log::trivial::severity_level::debug); };

        void info(const std::string &message) { log(message, boost::log::trivial::severity_level::info); };

        void warn(const std::string &message) { log(message, boost::log::trivial::severity_level::warning); };

        void error(const std::string &message) { log(message, boost::log::trivial::severity_level::error); };

        void fatal(const std::string &message) { log(message, boost::log::trivial::severity_level::fatal); };

    private:
        Logger(const std::string& fileName);

        Logger(Logger const &);

        Logger &operator=(Logger const &);

        virtual ~Logger() = default;

        static Logger* instance;

        boost::log::sources::severity_logger<boost::log::trivial::severity_level> logger;

        void log(const std::string &message, boost::log::trivial::severity_level level);
    };
}


#endif //X_COPILOT_LOGGER_H
