add_test( LastTest.Test_Last_Throws_Exception [==[/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/submodules/last/__build/last_tests]==] [==[--gtest_filter=LastTest.Test_Last_Throws_Exception]==] --gtest_also_run_disabled_tests)
set_tests_properties( LastTest.Test_Last_Throws_Exception PROPERTIES WORKING_DIRECTORY [==[/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/submodules/last/__build]==])
add_test( LastTest.Test_Last_Output_Last_Case_In_One_Day [==[/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/submodules/last/__build/last_tests]==] [==[--gtest_filter=LastTest.Test_Last_Output_Last_Case_In_One_Day]==] --gtest_also_run_disabled_tests)
set_tests_properties( LastTest.Test_Last_Output_Last_Case_In_One_Day PROPERTIES WORKING_DIRECTORY [==[/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/submodules/last/__build]==])
add_test( LastTest.Test_Last_Output_Last_Case [==[/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/submodules/last/__build/last_tests]==] [==[--gtest_filter=LastTest.Test_Last_Output_Last_Case]==] --gtest_also_run_disabled_tests)
set_tests_properties( LastTest.Test_Last_Output_Last_Case PROPERTIES WORKING_DIRECTORY [==[/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/submodules/last/__build]==])
set( last_tests_TESTS LastTest.Test_Last_Throws_Exception LastTest.Test_Last_Output_Last_Case_In_One_Day LastTest.Test_Last_Output_Last_Case)