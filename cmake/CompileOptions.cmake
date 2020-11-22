#In .cmake file, we can define functions, marcos 
#We use include(name.cmake) to include these functions and marcos;

# Annoying compiler-specific details
IF(MSVC)
  ADD_DEFINITIONS (/D  _CRT_SECURE_NO_WARNINGS)  ## add macro
  ADD_DEFINITIONS (/D  _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING )
ENDIF()