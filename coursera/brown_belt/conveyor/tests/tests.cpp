#include "gtest/gtest.h"
#include "pipeline.h"
#include <sstream>
#include <string>

using namespace std;

TEST(Basic, Sanity)
{
    string input = ("erich@example.com\n"
                    "richard@example.com\n"
                    "Hello there\n"

                    "erich@example.com\n"
                    "ralph@example.com\n"
                    "Are you sure you pressed the right button?\n"

                    "ralph@example.com\n"
                    "erich@example.com\n"
                    "I do not make mistakes of that kind\n");
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email &email) {
        return email.from == "erich@example.com";
    });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = ("erich@example.com\n"
                             "richard@example.com\n"
                             "Hello there\n"

                             "erich@example.com\n"
                             "ralph@example.com\n"
                             "Are you sure you pressed the right button?\n"

                             "erich@example.com\n"
                             "richard@example.com\n"
                             "Are you sure you pressed the right button?\n");

    EXPECT_EQ(expectedOutput, outStream.str());
}

TEST(Basic, Reader)
{
    string input = "\n\n\n\n";
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = "\n\n\n";

    EXPECT_EQ(expectedOutput, outStream.str());
}