#pragma once

namespace BeanChatCommon
{
    namespace ProtocolLimits
    {
        constexpr int MaxUsernameLength = 32;

        constexpr int MaxChannelNameLength = 64;

        constexpr int MaxAttachmentSize = 80 * 1024 * 1024; //80 MB

        constexpr int MaxMessageLength = 4096;

        constexpr int MaxPacketSize = 30 * 1024 * 1024; //30MB
    }
}
