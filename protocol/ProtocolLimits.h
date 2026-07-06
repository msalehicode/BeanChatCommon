#pragma once

namespace BeanChatCommon
{
    namespace ProtocolLimits
    {
        constexpr int MaxUsernameLength = 32;

        constexpr int MaxChannelNameLength = 64;

        constexpr int MaxMessageLength = 4096;

        constexpr int MaxPacketSize = 16 * 1024 * 1024; //16MB
    }
}
