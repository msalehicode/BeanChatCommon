#pragma once

#include "PacketType.h"

#include "packets/ChannelPackets.h"
#include "packets/LoginPackets.h"
#include "packets/MessagePackets.h"
#include "packets/ServerPackets.h"
#include "packets/UserPackets.h"
#include "packets/UdpPacekts.h"
#include "packets/FilePackets.h"

#include <limits>



namespace BeanChatCommon
{
    //when user don't find server's avatarHash \
    would send RequestAvatars and if inside that list userId was equal to this \
        server return this code as userId and fill avatarHash, avatarData as response.
    namespace ReservedIds
    {
        constexpr quint64 ServerAvatar =
            std::numeric_limits<quint64>::max() - 1;
    }
}
