#pragma once

#include <vector>
#include <string>
#include <functional>
#include <type_traits>
#include <iostream>


#define RED "\033[1;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define DEF "\033[0;0m"

#define INFO_PREFIX YELLOW "[    INFO] " DEF
#define RUN_PREFIX GREEN "[RUN     ] " DEF
#define OK_PREFIX GREEN "[      OK] " DEF
#define FAILED_PREFIX RED "[  FAILED] " DEF


#define ASSERT(cond)       \
    if (!(cond)) {         \
        success = false;   \
        condition = #cond; \
        file = __FILE__;   \
        line = __LINE__;   \
    }

#define ASSERT_TRUE(cond) ASSERT(cond);
#define ASSERT_FALSE(cond) ASSERT(!(cond));

#define ASSERT_NULL(value) ASSERT(value == nullptr);
#define ASSERT_NOTNULL(value) ASSERT(value != nullptr);

#define ASSERT_EQ(a, b)                                                         \
    if (!(a == b)) {                                                            \
        std::cout << INFO_PREFIX "Actual values: " << a << " == " << b << "\n"; \
    }                                                                           \
    ASSERT(a == b);

#define ASSERT_NE(a, b)                                                         \
    if (!(a != b)) {                                                            \
        std::cout << INFO_PREFIX "Actual values: " << a << " != " << b << "\n"; \
    }                                                                           \
    ASSERT(a != b);

#define ASSERT_NEAR(a, b, e) ASSERT(std::fabs(a - b) < e);

#define EXPECT_TRUE(cond) ASSERT(cond);
#define EXPECT_FALSE(cond) ASSERT(!(cond));

#define EXPECT_NULL(value) ASSERT(value == nullptr);
#define EXPECT_NOTNULL(value) ASSERT(value != nullptr);

#define EXPECT_EQ(a, b) ASSERT_EQ(a, b);
#define EXPECT_NE(a, b) ASSERT_NE(a, b);

#define EXPECT_NEAR(a, b, e) ASSERT_NEAR(a, b, e);


#define TEST(suite, name)                               \
    void name(bool&, std::string&, std::string&, int&); \
                                                        \
    namespace {                                         \
    bool __##name = gt2::addTest(name, #name);          \
    }                                                   \
                                                        \
    void name(bool& success, std::string& condition, std::string& file, int& line)


namespace gt2 {

struct Test {
    std::string name;
    std::function<void(bool&, std::string&, std::string&, int&)> fn;
};

static std::vector<Test>& tests() {
    static std::vector<Test> tests_;
    return tests_;
}

inline static bool addTest(std::function<void(bool&, std::string&, std::string&, int&)> fn,
                           const std::string& name) {
    tests().push_back({name, fn});
    return true;
}

inline static size_t runAllTests() {
    size_t numberOfFailedTests = 0;

    for (const auto& test : tests()) {
        std::cout << RUN_PREFIX << test.name << "\n";
        bool success = true;
        std::string condition;
        std::string filename;
        int line = 0;

        test.fn(success, condition, filename, line);

        if (success) {
            std::cout << OK_PREFIX << test.name << "\n";
        } else {
            std::cout << FAILED_PREFIX << test.name << "\n"
                      << "           " RED "Assertion failed: " << condition << DEF "\n"
                      << "           " RED << filename << ":" << line << DEF "\n";
            ++numberOfFailedTests;
        }
    }

    if (numberOfFailedTests == 0) {
        std::cout << GREEN "[ Summary] All tests succeeded!" DEF "\n";
    } else {
        double percentage = 100.0 * numberOfFailedTests / gt2::tests().size();

        std::cout << RED "[ Summary] " << numberOfFailedTests          //
                  << " Tests failed " << percentage << "% " DEF "\n";  //
    }

    return numberOfFailedTests;
}
}  // namespace gt2

#define TEST_MAIN() \
    int main() { return gt2::runAllTests(); }

