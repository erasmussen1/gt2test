# gt2test

## Description:
gt2test is a small c++ header only test framework

This is a very basic test framework (without exceptions) and can be used on embedded devices

The test macros are similar to the googletest. gt2test supports test fixtures

If more advanced test features are needed used gtest or catch2


### Project requires following
c++ version 13.0 or newer

### How to build and run the demo project:

```
 g++ -o test_fib demo/test_fib.cpp -Iinclude

 ./test_fib

```


### Output from demo:
```
[RUN     ] Fib0of15
[      OK] Fib0of15
[RUN     ] Fib1of15
[      OK] Fib1of15
[RUN     ] Fib2of15
[      OK] Fib2of15
[RUN     ] CompareTwoStringsEQ
[    INFO] Actual values: Hello == Hello1
[  FAILED] CompareTwoStringsEQ
           Assertion failed: aa == bb
           demo/test_fib.cpp:93
[RUN     ] CompareTwoStringsNE
[    INFO] Actual values: Hello != Hello
[  FAILED] CompareTwoStringsNE
           Assertion failed: aa != bb
           demo/test_fib.cpp:100
[RUN     ] TwoIntEQ
[    INFO] Actual values: 7 == 8
[  FAILED] TwoIntEQ
           Assertion failed: x == y
           demo/test_fib.cpp:107
[RUN     ] TwoIntNE
[    INFO] Actual values: 7 != 7
[  FAILED] TwoIntNE
           Assertion failed: x != y
           demo/test_fib.cpp:114
[RUN     ] Fib0of15f
[      OK] Fib0of15f
[RUN     ] Fib0of5f
[      OK] Fib0of5f
[ Summary] 4 Tests failed 44.4444%

```

### Example of the demo code:
```

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
    void SetUp() override {
        ;
    }

    void TearDown() override {
        n = 0;
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

```
