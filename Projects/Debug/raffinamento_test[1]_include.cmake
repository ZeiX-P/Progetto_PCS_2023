if(EXISTS "C:/Users/LENOVO/Desktop/Progetto_Raffinamento/Projects/Debug/raffinamento_test[1]_tests.cmake")
  include("C:/Users/LENOVO/Desktop/Progetto_Raffinamento/Projects/Debug/raffinamento_test[1]_tests.cmake")
else()
  add_test(raffinamento_test_NOT_BUILT raffinamento_test_NOT_BUILT)
endif()
