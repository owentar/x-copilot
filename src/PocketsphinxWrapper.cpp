#include "PocketsphinxWrapper.h"

#include <pocketsphinx.h>
#include <string>

void Pocketsphinx::init()
{
    cmd_ln_t* config = cmd_ln_init(NULL, ps_args(), TRUE,       // Load the configuration structure - ps_args() passes the default values
    "-hmm", "/usr/local/share/pocketsphinx/model/en-us/en-us",  // path to the standard english language model
    "-lm", "/home/owentar/Projects/X-Plane/x-copilot/xcopilot/pocketsphinx-data/xp-XP/language-model.lm",
    "-dict", "/home/owentar/Projects/X-Plane/x-copilot/xcopilot/pocketsphinx-data/xp-XP/pronounciation-dictionary.dic",
    "-logfn", "/dev/null",                                      // suppress log info from being sent to screen
     NULL);
    ps = ps_init(config);
}

void Pocketsphinx::start()
{
    ps_start_utt(ps);
}

void Pocketsphinx::end()
{
    ps_end_utt(ps);
}

void Pocketsphinx::process(const short* rawData, unsigned long frameCount)
{
    ps_process_raw(ps, rawData, frameCount, FALSE, FALSE);
}

std::string Pocketsphinx::decode()
{
    this->end();
    std::string result = ps_get_hyp(ps, NULL);
    this->start();
    return result;
}

bool Pocketsphinx::isSpeaking() const
{
    return ps_get_in_speech(ps);
}
