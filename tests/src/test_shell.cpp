#include "mocks/mock_shell.hpp"
#include "shell/interfaces/bash/shell.hpp"

using namespace testing;

class TestShell : public Test
{
  public:
    std::shared_ptr<ShellMock> commandMockPtr =
        std::make_shared<NiceMock<ShellMock>>();
    std::shared_ptr<shell::ShellIf> handler;

  protected:
    void SetUp() override
    {
        handler =
            shell::Factory::create<shell::bash::Bash, shell::bash::config_t>(
                {});
    }

    void TearDown() override
    {
        handler.reset();
    }
};

TEST_F(TestShell, testValidCommandNoOutputSucceeded)
{
    auto retcode = handler->run("ls > /dev/null");
    EXPECT_EQ(retcode, 0);
}

TEST_F(TestShell, testInvalidCommandNoOutputFailed)
{
    auto retcode = handler->run("invalid_cmd 2> /dev/null");
    EXPECT_NE(retcode, 0);
}

TEST_F(TestShell, testValidCommandWithOutputSucceeded)
{
    std::vector<std::string> output;
    auto retcode = handler->run("ls -a", output);
    ASSERT_EQ(retcode, 0);
    EXPECT_FALSE(output.empty());
}

TEST_F(TestShell, testInvalidCommandWithOutputFailed)
{
    std::vector<std::string> output;
    auto retcode = handler->run("invalid_cmd 2> /dev/null", output);
    ASSERT_NE(retcode, 0);
    EXPECT_TRUE(output.empty());
}
