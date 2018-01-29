#include "PocketsphinxWrapper.h"

#include <string>
#include <boost/filesystem.hpp>

#include "pocketsphinx/pocketsphinx.h"
#include "Logger.h"

#ifdef IBM
#define POCKETSPHINX_LOGFN "nul"
#else
#define POCKETSPHINX_LOGFN "/dev/null"
#endif

using namespace xcopilot;

boost::filesystem::path getPocketsphinxDataPathForResource(const std::string& resource)
{
    return boost::filesystem::absolute("pocketsphinx-data/xp-XP/" + resource);
}

void Pocketsphinx::start()
{
    Logger::getInstance()->debug("Starting pocketsphinx");
    auto hmm = getPocketsphinxDataPathForResource("acoustic-model").generic_string();
    auto lm = getPocketsphinxDataPathForResource("language-model.lm").generic_string();
    auto jsgf = getPocketsphinxDataPathForResource("grammar.jsgf").generic_string();
    auto dict = getPocketsphinxDataPathForResource("pronounciation-dictionary.dic").generic_string();
    cmd_ln_t* config = cmd_ln_init(NULL, ps_args(), TRUE,       // Load the configuration structure - ps_args() passes the default values
    "-hmm", hmm.c_str(),  // path to the standard english language model
//    "-lm", lm.c_str(),
    "-jsgf", lm.c_str(),
    "-dict", dict.c_str(),
    "-logfn", POCKETSPHINX_LOGFN,                                      // suppress log info from being sent to screen
    NULL);
    ps = ps_init(config);

    ps_start_utt(ps);
    Logger::getInstance()->debug("Pocketsphinx successfuly");
}

void Pocketsphinx::stop() { ps_end_utt(ps); }

void Pocketsphinx::process(const short* rawData, unsigned long frameCount)
{
    ps_process_raw(ps, rawData, frameCount, FALSE, FALSE);
}

std::string Pocketsphinx::decode()
{
    ps_end_utt(ps);
    std::string result = ps_get_hyp(ps, NULL);
    ps_start_utt(ps);
    return result;
}

bool Pocketsphinx::isSpeaking() const { return ps_get_in_speech(ps); }
