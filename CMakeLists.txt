cmake_minimum_required(VERSION 3.16)

project(BeanChatCommon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)


if(ANDROID)
    set(OPENSSL_ROOT "${CMAKE_CURRENT_LIST_DIR}/third_party/openssl/arm64-v8a")

    add_library(OpenSSL::Crypto SHARED IMPORTED)
    set_target_properties(OpenSSL::Crypto PROPERTIES
        IMPORTED_LOCATION "${OPENSSL_ROOT}/lib/libcrypto.so"
        INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_ROOT}/include"
    )

    add_library(OpenSSL::SSL SHARED IMPORTED)
    set_target_properties(OpenSSL::SSL PROPERTIES
        IMPORTED_LOCATION "${OPENSSL_ROOT}/lib/libssl.so"
        INTERFACE_LINK_LIBRARIES OpenSSL::Crypto
        INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_ROOT}/include"
    )
else()

    if(WIN32) #install via msys2: pacman -S mingw-w64-x86_64-openssl
            set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
    endif()

    set(OPENSSL_USE_STATIC_LIBS TRUE)
    find_package(OpenSSL REQUIRED)

endif()


add_library(BeanChatCommon STATIC

    protocol/Packet.h
    protocol/PacketHelpers.h
    protocol/PacketType.h
    protocol/Packets.h
    protocol/ProtocolVersion.h
    protocol/ProtocolLimits.h

    #packets
    protocol/packets/ChannelPackets.h
    protocol/packets/LoginPackets.h
    protocol/packets/MessagePackets.h
    protocol/packets/ServerPackets.h
    protocol/packets/UserPackets.h
    protocol/packets/UdpPacekts.h

    crypto/Crypto.h
    crypto/Crypto.cpp
)

target_link_libraries(
    BeanChatCommon
    PUBLIC
        Qt6::Core
        OpenSSL::SSL
        OpenSSL::Crypto
)


if(ANDROID)
target_link_libraries(BeanChatCommon
    PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party/openssl/arm64-v8a/lib/libssl.a
        ${CMAKE_SOURCE_DIR}/third_party/openssl/arm64-v8a/lib/libcrypto.a
)
endif()


target_include_directories(
    BeanChatCommon
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(
    BeanChatCommon
    PRIVATE
        BEANCHATCOMMON_LIBRARY
)
