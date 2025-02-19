#include "mocks/mock_shell.hpp"
#include "shell/interfaces/linux/bash/shell.hpp"

using namespace testing;

class TestShell : public Test
{
  public:
    std::shared_ptr<ShellMock> commandMockPtr =
        std::make_shared<NiceMock<ShellMock>>();
    std::shared_ptr<shell::ShellIf> shellif;

  protected:
    void SetUp() override
    {
        shellif = shell::Factory::create<shell::lnx::bash::Shell>();
    }

    void TearDown() override
    {
        shellif.reset();
    }
};

TEST_F(TestShell, testValidCommandNoOutputSucceeded)
{
    auto retcode = shellif->run("ls > /dev/null");
    EXPECT_EQ(retcode, 0);
}

TEST_F(TestShell, testInvalidCommandNoOutputFailed)
{
    auto retcode = shellif->run("invalid_cmd 2> /dev/null");
    EXPECT_NE(retcode, 0);
}

TEST_F(TestShell, testValidCommandWithOutputSucceeded)
{
    std::vector<std::string> output;
    auto retcode = shellif->run("ls -a", output);
    ASSERT_EQ(retcode, 0);
    EXPECT_FALSE(output.empty());
}

TEST_F(TestShell, testInvalidCommandWithOutputFailed)
{
    std::vector<std::string> output;
    auto retcode = shellif->run("invalid_cmd 2> /dev/null", output);
    ASSERT_NE(retcode, 0);
    EXPECT_TRUE(output.empty());
}
