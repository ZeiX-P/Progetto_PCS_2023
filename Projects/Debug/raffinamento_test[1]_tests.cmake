add_test([=[TestAlgo.TestMergeSortAlgorithm]=]  C:/Users/LENOVO/Desktop/Progetto_Raffinamento/Projects/Debug/raffinamento_test.exe [==[--gtest_filter=TestAlgo.TestMergeSortAlgorithm]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestAlgo.TestMergeSortAlgorithm]=]  PROPERTIES WORKING_DIRECTORY C:/Users/LENOVO/Desktop/Progetto_Raffinamento/Projects/Debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestAlgo.TestRaffAlgo]=]  C:/Users/LENOVO/Desktop/Progetto_Raffinamento/Projects/Debug/raffinamento_test.exe [==[--gtest_filter=TestAlgo.TestRaffAlgo]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestAlgo.TestRaffAlgo]=]  PROPERTIES WORKING_DIRECTORY C:/Users/LENOVO/Desktop/Progetto_Raffinamento/Projects/Debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  raffinamento_test_TESTS TestAlgo.TestMergeSortAlgorithm TestAlgo.TestRaffAlgo)
