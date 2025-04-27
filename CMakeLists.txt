cmake_minimum_required(VERSION 3.16)

project (Incubator)

add_subdirectory(Common/MFBufferLib)
add_subdirectory(Common/MFEndianUtilsLib)
add_subdirectory(Common/MFByteStreamLib)


add_subdirectory(Components/TC2004Lib)
add_subdirectory(Components/DHT11Lib)
add_subdirectory(Components/NTCLib)
add_subdirectory(Components/Eeprom24CLib)
add_subdirectory(Components/SHT3XLib)
add_subdirectory(Components/JoystickLib)
add_subdirectory(IncubatorLib)
add_subdirectory(IncubatorTestSimulator)