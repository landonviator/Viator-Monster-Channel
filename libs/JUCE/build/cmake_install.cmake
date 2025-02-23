# Install script for directory: /Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/modules/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/extras/Build/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11" TYPE FILE FILES
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/JUCEConfigVersion.cmake"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/JUCEConfig.cmake"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/JUCECheckAtomic.cmake"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/JUCEHelperTargets.cmake"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/JUCEModuleSupport.cmake"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/JUCEUtils.cmake"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/JuceLV2Defines.h.in"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/LaunchScreen.storyboard"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/PIPAudioProcessor.cpp.in"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/PIPAudioProcessorWithARA.cpp.in"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/PIPComponent.cpp.in"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/PIPConsole.cpp.in"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/RecentFilesMenuTemplate.nib"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/UnityPluginGUIScript.cs.in"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/checkBundleSigning.cmake"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/copyDir.cmake"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/juce_runtime_arch_detection.cpp"
    "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/extras/Build/CMake/juce_LinuxSubprocessHelper.cpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.11" TYPE EXECUTABLE FILES "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/juce_lv2_helper")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.11/juce_lv2_helper" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.11/juce_lv2_helper")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.11/juce_lv2_helper")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/CMakeFiles/juce_lv2_helper.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11/LV2_HELPER.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11/LV2_HELPER.cmake"
         "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/CMakeFiles/Export/17b516e11df27681f32be9defbf1dd36/LV2_HELPER.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11/LV2_HELPER-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11/LV2_HELPER.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11" TYPE FILE FILES "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/CMakeFiles/Export/17b516e11df27681f32be9defbf1dd36/LV2_HELPER.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11" TYPE FILE FILES "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/CMakeFiles/Export/17b516e11df27681f32be9defbf1dd36/LV2_HELPER-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.11" TYPE EXECUTABLE FILES "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/juce_vst3_helper")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.11/juce_vst3_helper" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.11/juce_vst3_helper")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.11/juce_vst3_helper")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/CMakeFiles/juce_vst3_helper.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11/VST3_HELPER.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11/VST3_HELPER.cmake"
         "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/CMakeFiles/Export/17b516e11df27681f32be9defbf1dd36/VST3_HELPER.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11/VST3_HELPER-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11/VST3_HELPER.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11" TYPE FILE FILES "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/CMakeFiles/Export/17b516e11df27681f32be9defbf1dd36/VST3_HELPER.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.11" TYPE FILE FILES "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/CMakeFiles/Export/17b516e11df27681f32be9defbf1dd36/VST3_HELPER-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/landonviator/Documents/GitHub/cmake-template-plugin/libs/JUCE/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
