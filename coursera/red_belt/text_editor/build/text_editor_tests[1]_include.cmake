if(EXISTS "/home/vika/learning/coursera/red_belt/text_editor/build/text_editor_tests[1]_tests.cmake")
  include("/home/vika/learning/coursera/red_belt/text_editor/build/text_editor_tests[1]_tests.cmake")
else()
  add_test(text_editor_tests_NOT_BUILT text_editor_tests_NOT_BUILT)
endif()