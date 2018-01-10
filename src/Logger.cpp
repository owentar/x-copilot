#include "Logger.h"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

using namespace xcopilot;
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;

Logger* Logger::instance = nullptr;

Logger* Logger::getInstance() {
    if (instance == nullptr) {
        instance = new Logger("xcopilot.log");
    }

    return instance;
}

Logger::Logger(const std::string& fileName) {
    logging::add_file_log(
            keywords::file_name = fileName,
            keywords::auto_flush = true
    );
    logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
    logging::add_common_attributes();
}

void Logger::log(const std::string &message, boost::log::trivial::severity_level level) {
    BOOST_LOG_SEV(logger, level) << message;
}
