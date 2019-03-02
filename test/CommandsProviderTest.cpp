#include "gmock/gmock.h"

#include <memory>

#include "CommandsProvider.h"

using namespace testing;
using namespace xcopilot;

class CommandsConfigReaderMock : public CommandsConfigReader {
public:
    explicit CommandsConfigReaderMock() : CommandsConfigReader() {}

    MOCK_METHOD1(getAircraftCommandsMatchers, std::vector<AircraftCommandsMatcher>(const std::string&));

    MOCK_METHOD1(getCommandsFromFile, std::vector<std::shared_ptr<CommandRecognizer>>(const std::string&));
};

class CommandsProviderTest : public Test {
public:
    CommandsProviderTest() : commandsConfigReaderMock{std::make_unique<NiceMock<CommandsConfigReaderMock>>()} {};
protected:
    std::unique_ptr<NiceMock<CommandsConfigReaderMock>> commandsConfigReaderMock;

    virtual void SetUp() {
        std::vector<AircraftCommandsMatcher> aircraftMatchers = {{"test", "test", "test", "test", "test"}};
        EXPECT_CALL(*commandsConfigReaderMock, getAircraftCommandsMatchers(DEFAULT_INDEX_FILE_PATH)) // TODO: verify how should I import DEFAULT_INDEX_FILE_PATH const
                .WillOnce(Return(aircraftMatchers));

        auto defaultCommand1 = std::make_shared<CommandRecognizer>(
                CommandMetadata("command-1", CommandType::FLOAT, "command-1", {}));
        auto defaultCommand2 = std::make_shared<CommandRecognizer>(
                CommandMetadata("command-2", CommandType::FLOAT, "command-2", {}));
        std::vector<std::shared_ptr<CommandRecognizer>> defaultCommands = {defaultCommand1, defaultCommand2};
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
    std::vector<std::shared_ptr<CommandRecognizer>> aircraftCommands = {aircraftCommand1, aircraftCommand2};
    EXPECT_CALL(*commandsConfigReaderMock, getCommandsFromFile("test"))
            .WillOnce(Return(aircraftCommands));

    CommandsProvider commandsProvider(std::move(commandsConfigReaderMock));
    auto commands = commandsProvider.getCommandsForAircraft("test", "test", "test");
    ASSERT_THAT(commands.size(), Eq(3));
}
