
#include "gt2test.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>


namespace fib0 {

unsigned int fib(unsigned int n) {
    return n == 0 ? 0 : n == 1 ? 1 : fib(n - 1) + fib(n - 2);
}

}  // namespace fib0

namespace fib1 {

std::vector<unsigned int> cache{0, 1};

unsigned int fib(unsigned int n) {
    if (cache.size() > n) {
        return cache[n];
    }

    const auto result = fib(n - 1) + fib(n - 2);
    cache.push_back(result);
    return result;
}
}  // namespace fib1

namespace fib2 {
class fib_cache {
public:
    fib_cache() : m_previous{0}, m_last{1}, m_size{2} {}

    size_t size() const {
        return m_size;
    }

    unsigned int operator[](unsigned int n) const {
        return n == m_size - 1 ? m_last
            : n == m_size - 2  ? m_previous
                               : throw std::out_of_range("The value is no longer in the cache");
    }

    void push_back(unsigned int value) {
        m_size++;
        m_previous = m_last;
        m_last = value;
    }

private:
    unsigned int m_previous;
    unsigned int m_last;
    size_t m_size;
} cache_fib;

unsigned int fib(unsigned int n) {
    if (cache_fib.size() > n) {
        return cache_fib[n];
    } else {
        const auto result = fib(n - 1) + fib(n - 2);
        cache_fib.push_back(result);
        return result;
    }
}
}  // namespace fib2


TEST(TestSuite, Fib0of15) {
    unsigned int res = fib0::fib(15);

    EXPECT_TRUE(res == 610);
}

TEST(TestSuite, Fib1of15) {
    unsigned int res = fib1::fib(15);

    EXPECT_TRUE(res == 610);
}

TEST(TestSuite, Fib2of15) {
    unsigned int res = fib2::fib(15);

    EXPECT_FALSE(res != 610);
}

TEST(TestSuite, CompareTwoStringsEQ) {
    const std::string aa{"Hello"};
    std::string bb{"Hello1"};

    ASSERT_EQ(aa, bb);
}

TEST(TestSuite, CompareTwoStringsNE) {
    std::string aa{"Hello"};
    std::string bb{"Hello"};

    ASSERT_NE(aa, bb);
}

TEST(TestSuite, TwoIntEQ) {
    unsigned int x = 7;
    unsigned int y = 8;

    ASSERT_EQ(x, y);
}

TEST(TestSuite, TwoIntNE) {
    unsigned int x = 7;
    unsigned int y = 7;

    ASSERT_NE(x, y);
}

struct FibFixture : public gt2::Test {
    void setUp() {
        ;
    }

    void tearDown() {
        ;
    }

    int n{15};
};

TEST_F(FibFixture, Fib0of15f) {
    unsigned int res = fib0::fib(n);

    EXPECT_TRUE(res == 610);
}

TEST_F(FibFixture, Fib0of5f) {
    n = 5;

    unsigned int res = fib0::fib(n);

    EXPECT_TRUE(res == 5);
}


TEST_MAIN();
