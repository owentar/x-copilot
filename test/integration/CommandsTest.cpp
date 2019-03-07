#include "gmock/gmock.h"

#include <memory>
#include <string>
#include <vector>

#include "CommandsProvider.h"
#include "../util/XPlaneDataRefSDKMock.h"

using namespace testing;
using namespace xcopilot;

class CommandsIntegrationTest : public Test {
public:
    CommandsIntegrationTest() : xPlaneDatRefSDK{}, commandsProvider{&xPlaneDatRefSDK} {};
protected:
    XPlaneDataRefSDKMock xPlaneDatRefSDK;
    CommandsProvider commandsProvider{&xPlaneDatRefSDK};
    std::vector<std::shared_ptr<CommandRecognizer>> commands;

    virtual void SetUp() { commands = commandsProvider.getCommandsForAircraft("test", "test", "test"); }

    void assertCommandIsNotRecognized(const std::string& name, const std::string& phrase) { assertCommand(name, phrase, false); }

    template<typename T>
    void assertCommandIsRecognized(const std::string& name, const std::string& phrase, T value) { assertCommand(name, phrase, true); }

    void assertCommand(const std::string& name, const std::string& phrase, bool isRecognized) {
        auto command = findCommand(phrase);
        ASSERT_THAT(command, NotNull());
        ASSERT_THAT(command->getName(), name);
    }
private:
    std::shared_ptr<CommandRecognizer> findCommand(const std::string& phrase) {
        auto value = std::find_if(commands.begin(), commands.end(),
                     [phrase] (const std::shared_ptr<CommandRecognizer> command) -> bool { return command->commandRecognized(phrase); });
        return value != commands.end() ? *value : nullptr;
    }
};

TEST_F(CommandsIntegrationTest, SetAltimeter) {
    auto commandName = "SET_ALTIMETER";
    assertCommandIsRecognized(commandName, "SET ALTIMETER TWO NINE NINE TWO", 29.92);
}
