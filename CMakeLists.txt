cmake_minimum_required(VERSION 3.16)

project(BeanChatCommon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

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
    crypto/Identity.h
)

target_link_libraries(
    BeanChatCommon
    PUBLIC
        Qt6::Core
)

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
