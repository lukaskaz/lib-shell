#include "mocks/mock_command.hpp"
#include "shellcommand.hpp"

using namespace testing;

class TestCommand : public Test
{
  public:
    std::shared_ptr<CommandsMock> commandMockPtr =
        std::make_shared<NiceMock<CommandsMock>>();
    std::shared_ptr<ShellCommand> handler;

  protected:
    void SetUp() override
    {
        handler = std::make_shared<BashCommand>();
    }

    void TearDown() override
    {
        handler.reset();
    }
};

TEST_F(TestCommand, testValidCommandNoOutputSucceeded)
{
    auto retcode = handler->run("ls > /dev/null");
    EXPECT_EQ(retcode, 0);
}

TEST_F(TestCommand, testInvalidCommandNoOutputFailed)
{
    auto retcode = handler->run("invalid_cmd 2> /dev/null");
    EXPECT_NE(retcode, 0);
}

TEST_F(TestCommand, testValidCommandWithOutputSucceeded)
{
    std::vector<std::string> output;
    auto retcode = handler->run("ls -a", output);
    ASSERT_EQ(retcode, 0);
    EXPECT_FALSE(output.empty());
}

TEST_F(TestCommand, testInvalidCommandWithOutputFailed)
{
    std::vector<std::string> output;
    auto retcode = handler->run("invalid_cmd 2> /dev/null", output);
    ASSERT_NE(retcode, 0);
    EXPECT_TRUE(output.empty());
}

// TEST_F(TestCommand, basicTestSecond)
// {
//     EXPECT_CALL(*commandMockPtr, run(_)).Times(2);
// }
