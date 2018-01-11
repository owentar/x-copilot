#include "Logger.h"

#include <iostream>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/support/date_time.hpp>

using namespace xcopilot;
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

Logger* Logger::instance = nullptr;

auto getLogFormatter() {
    auto fmtTimeStamp = expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f");
    auto fmtSeverity = expr::attr<boost::log::trivial::severity_level>("Severity");
    return expr::format("[%1%] (%2%) %3%") % fmtTimeStamp % fmtSeverity % expr::message;
}

Logger* Logger::getInstance() {
    if (instance == nullptr) {
        instance = new Logger();
    }

    return instance;
}

void Logger::configureConsoleLogger() {
    auto consoleSink = logging::add_console_log(std::cout, keywords::format = getLogFormatter());
}

void Logger::configureFileLogger(const std::string& fileName) {
    logging::add_file_log(
            keywords::file_name = fileName,
            keywords::format = getLogFormatter(),
            keywords::auto_flush = true
    );
}

Logger::Logger() {
    logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
    logging::add_common_attributes();
}

void Logger::log(const std::string &message, boost::log::trivial::severity_level level) {
    BOOST_LOG_SEV(logger, level) << message;
}
