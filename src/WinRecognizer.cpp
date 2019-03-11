#include <algorithm>

#include <boost/format.hpp>

#include "WinRecognizer.h"
#include "Logger.h"

#ifdef RELEASE
#define GRAMMAR_FILE_PATH L"Resources/plugins/x-copilot/config/Default-Grammar.xml"
#else
#define GRAMMAR_FILE_PATH L"config/Default-Grammar.xml"
#endif

const int GRAM_ID = 409;

using namespace xcopilot;
using boost::format;

void checkResult(const HRESULT& result)
{
	if (result == S_OK) {
		return;
	}

	std::string message;

	switch (result) {

	case E_INVALIDARG:
		message = "One or more arguments are invalids.";

	case E_ACCESSDENIED:
		message = "Acces Denied.";

	case E_NOINTERFACE:
		message = "Interface does not exist.";

	case E_NOTIMPL:
		message = "Not implemented method.";

	case E_OUTOFMEMORY:
		message = "Out of memory.";

	case E_POINTER:
		message = "Invalid pointer.";

	case E_UNEXPECTED:
		message = "Unexpecter error.";

	case E_FAIL:
		message = "Failure";

	default:
		message = "Unknown : " + std::to_string(result);
	}

	Logger::getInstance()->fatal(message);
}

void WinRecognizer::start()
{
	// Initialize COM
	if (!FAILED(::CoInitialize(NULL)))
	{
		HRESULT hr = SpFindBestToken(SPCAT_RECOGNIZERS, L"language=409", NULL, &recognizerToken.p);

		if (SUCCEEDED(hr)) {
			// Create the recognizer for this process
			hr = recognizer.CoCreateInstance(CLSID_SpInprocRecognizer);

			if (SUCCEEDED(hr)) {
				// Set the token (lang) to the recognizer
				hr = recognizer->SetRecognizer(recognizerToken);

				if (SUCCEEDED(hr)) {
					// Create a recognition context for recognition
					hr = recognizer->SetRecoState(SPRST_INACTIVE);
					checkResult(hr);

					hr = recognizer->CreateRecoContext(&context.p);
					checkResult(hr);

					// Set Audio input
					hr = SpGetDefaultTokenFromCategoryId(SPCAT_AUDIOIN, &audioToken.p);
					checkResult(hr);
					hr = recognizer->SetInput(audioToken, TRUE);
					checkResult(hr);
					hr = SpCreateDefaultObjectFromCategoryId(SPCAT_AUDIOIN, &audio.p);
					checkResult(hr);
					hr = recognizer->SetInput(audio, TRUE);
					checkResult(hr);

					//hr = m_cpRecoContext.CoCreateInstance(CLSID_SpSharedRecoContext);


					if (SUCCEEDED(hr)) {
						// Tell it that we only care about speech recognition events
						ULONGLONG events = SPFEI(SPEI_RECOGNITION);
						hr = context->SetInterest(events, events);
						checkResult(hr);

						// Create a SR grammar
						hr = context->CreateGrammar(0, &grammar.p);
						checkResult(hr);

						if (SUCCEEDED(hr)) {
							context->Pause(NULL);

							//// Command & control mode from a file
							hr = grammar->LoadCmdFromFile(GRAMMAR_FILE_PATH, SPLO_STATIC);
							checkResult(hr);
							
							if (FAILED(hr)) checkResult(hr);

							hr = grammar->SetGrammarState(SPGS_ENABLED);
							if (FAILED(hr)) checkResult(hr);

							hr = grammar->SetRuleState(NULL, NULL, SPRS_ACTIVE);
							if (FAILED(hr)) checkResult(hr);

							hr = context->Resume(NULL);
							if (FAILED(hr)) checkResult(hr);
						}
					}

					/*
					SPRECOCONTEXTSTATUS ctxStatus;
					context->GetStatus(&ctxStatus);
					SPCONTEXTSTATE ctxState;
					context->GetContextState(&ctxState);

					SPRECOSTATE recoState;
					recognizer->GetRecoState(&recoState);
					SPRECOGNIZERSTATUS recoStatus;
					recognizer->GetStatus(&recoStatus);
					*/

					hr = recognizer->SetRecoState(SPRST_ACTIVE_ALWAYS);
				}
			}
		}
	}
}

std::vector<CommandExecutor> WinRecognizer::getRecognizedCommands()
{
	std::vector<CommandExecutor> commandsToExecute;
	// Get all events - note that GetFrom returns S_FALSE when it
	// has no events to get, which passes the SUCCEEDED macro test.
	// We therefore specifically check for S_OK.
	CSpEvent evt;
	while (S_OK == evt.GetFrom(context))
	{
		if (evt.eEventId == SPEI_RECOGNITION &&
			evt.RecoResult())
		{
			HRESULT hr = S_OK;
			WCHAR*	pwszText = NULL;
			ISpRecoResult* pResult = evt.RecoResult();
			SPPHRASE* pPhrase;

			hr = pResult->GetPhrase(&pPhrase);
			if (FAILED(hr)) checkResult(hr);

			int ruleId = pPhrase->Rule.ulId;
			std::vector<int> values;
			auto property = pPhrase->pProperties;
			while (property != NULL) {
				values.push_back(property->vValue.iVal);
				property = property->pNextSibling;
			}

			CoTaskMemFree(pPhrase);

			auto command = std::find_if(commands.begin(), commands.end(),
				[ruleId](const std::shared_ptr<Command> command) -> bool { return command->getId() == ruleId; });

			if (command == commands.end()) {
				Logger::getInstance()->warn(format("The phrase (%1%) was recognized but there's no registered command for it.") % ruleId);
			} else {
				commandsToExecute.push_back(command->get()->getExecutor(values));
			}
		}
	}

	return commandsToExecute;
}

void WinRecognizer::stop()
{
	audioToken.Release();
	audio.Release();
	grammar.Release();
	context.Release();
	recognizerToken.Release();
	recognizer.Release();
}
