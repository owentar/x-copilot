#include "gmock/gmock.h"

#include <algorithm>
#include <functional>
#include <memory>

#include "CommandsProvider.h"

using namespace testing;
using namespace xcopilot;

typedef std::shared_ptr<CommandRecognizer> CommandRecognizerPtr;

auto isCommandEqual(const CommandRecognizerPtr& command) {
    return std::bind(std::equal_to(), std::placeholders::_1, command);
};

auto isCommandPresent(const std::vector<CommandRecognizerPtr>& commands, const CommandRecognizerPtr& command) {
    return std::any_of(commands.begin(), commands.end(), isCommandEqual(command));
}

class CommandsConfigReaderMock : public CommandsConfigReader {
public:
    explicit CommandsConfigReaderMock() : CommandsConfigReader() {}

    MOCK_METHOD1(getAircraftCommandsMatchers, std::vector<AircraftCommandsMatcher>(const std::string&));

    MOCK_METHOD1(getCommandsFromFile, std::vector<CommandRecognizerPtr>(const std::string&));
};

class CommandsProviderTest : public Test {
public:
    CommandsProviderTest() : commandsConfigReaderMock{std::make_unique<NiceMock<CommandsConfigReaderMock>>()} {};
protected:
    std::unique_ptr<NiceMock<CommandsConfigReaderMock>> commandsConfigReaderMock;
    CommandRecognizerPtr defaultCommand1;
    CommandRecognizerPtr defaultCommand2;

    virtual void SetUp() {
        std::vector<AircraftCommandsMatcher> aircraftMatchers = {{"test", "test", "test", "test", "test"}};
        EXPECT_CALL(*commandsConfigReaderMock, getAircraftCommandsMatchers(DEFAULT_INDEX_FILE_PATH)) // TODO: verify how should I import DEFAULT_INDEX_FILE_PATH const
                .WillOnce(Return(aircraftMatchers));

        defaultCommand1 = std::make_shared<CommandRecognizer>(
                CommandMetadata("command-1", CommandType::FLOAT, "command-1", {}));
        defaultCommand2 = std::make_shared<CommandRecognizer>(
                CommandMetadata("command-2", CommandType::FLOAT, "command-2", {}));
        std::vector<CommandRecognizerPtr> defaultCommands = {defaultCommand1, defaultCommand2};
        EXPECT_CALL(*commandsConfigReaderMock, getCommandsFromFile(DEFAULT_COMMANDS_FILE_PATH))
                .WillOnce(Return(defaultCommands));
    }
};

TEST_F(CommandsProviderTest, LoadDefaultCommandsWhenNoMatchIsFoundOnIndex) {
    CommandsProvider commandsProvider(std::move(commandsConfigReaderMock));
    auto commands = commandsProvider.getCommandsForAircraft("not-found", "not-found", "not-found");
    ASSERT_THAT(commands.size(), Eq(2));
}

TEST_F(CommandsProviderTest, MergeCommandsWhenMatchIsFoundOnIndex) {
    auto aircraftCommand1 = std::make_shared<CommandRecognizer>(
            CommandMetadata("command-1", CommandType::INT, "command-1", {}));
    auto aircraftCommand2 = std::make_shared<CommandRecognizer>(
            CommandMetadata("command-3", CommandType::INT, "command-3", {}));
    std::vector<CommandRecognizerPtr> aircraftCommands = {aircraftCommand1, aircraftCommand2};
    EXPECT_CALL(*commandsConfigReaderMock, getCommandsFromFile("test"))
            .WillOnce(Return(aircraftCommands));

    CommandsProvider commandsProvider(std::move(commandsConfigReaderMock));
    auto commands = commandsProvider.getCommandsForAircraft("test", "test", "test");
    ASSERT_THAT(commands.size(), Eq(3));
    ASSERT_THAT(isCommandPresent(commands, aircraftCommand1), Eq(true));
    ASSERT_THAT(isCommandPresent(commands, aircraftCommand2), Eq(true));
    ASSERT_THAT(isCommandPresent(commands, defaultCommand2), Eq(true));
    ASSERT_THAT(isCommandPresent(commands, defaultCommand1), Eq(false));
}
