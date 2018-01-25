#include "gmock/gmock.h"

#include <memory>
#include <string>
#include <vector>

#include "CommandsConfigReader.h"
#include "XPlaneDataRefSDK.h"

using namespace testing;
using namespace xcopilot;

class XPlaneDataRefSDKMock : public XPlaneDataRefSDK {
public:
//    MOCK_METHOD1(findDataRef, XPLMDataRef(const std::string&));
};

class CommandsIntegrationTest : public Test {
public:
    CommandsIntegrationTest() : xPlaneDatRefSDK{}, configReader{&xPlaneDatRefSDK} {};
protected:
    XPlaneDataRefSDKMock xPlaneDatRefSDK;
    CommandsConfigReader configReader{&xPlaneDatRefSDK};
    std::vector<std::shared_ptr<Command>> commands;

    virtual void SetUp() { commands = configReader.getCommandsForAircraft(); }

    void assertCommandIsNotRecognized(const std::string& name, const std::string& phrase) { assertCommand(name, phrase, false); }

    template<typename T>
    void assertCommandIsRecognized(const std::string& name, const std::string& phrase, T value) { assertCommand(name, phrase, true); }

    void assertCommand(const std::string& name, const std::string& phrase, bool isRecognized) {
        auto command = findCommand(phrase);
        ASSERT_THAT(command, NotNull());
        ASSERT_THAT(command->getName(), name);
    }
private:
    std::shared_ptr<Command> findCommand(const std::string& phrase) {
        auto value = std::find_if(commands.begin(), commands.end(),
                     [phrase] (const std::shared_ptr<Command> command) -> bool { return command->isRecognized(phrase); });
        return value != commands.end() ? *value : nullptr;
    }
};

TEST_F(CommandsIntegrationTest, SetAltimeter) {
    auto commandName = "SET_ALTIMETER";
    assertCommandIsRecognized(commandName, "SET ALTIMETER TWO NINE NINE TWO", 29.92);
}
