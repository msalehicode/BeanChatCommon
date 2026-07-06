#pragma once
#include <QDataStream>
#include <QDateTime>
#include "UserPackets.h"
#include "ChannelPackets.h"

namespace BeanChatCommon
{
    struct ServerInfo
    {
        QString name;
        QString version;
        QString website;
        QDateTime startTime;

        //store server's avatarHash, if user couldn't find that hash in cached acatars would ask for avatar.
        //and would store inside user's servers directory
        QString avatarHash;
        QString oldAvatarHash; //when avatar changed to tell users delete old avatar

        bool operator==(const ServerInfo &other) const
        {
            return name == other.name &&
                   version == other.version &&
                   website == other.website &&
                   startTime == other.startTime &&
                   avatarHash == other.avatarHash &&
                   oldAvatarHash == other.oldAvatarHash;
        }

        bool operator!=(const ServerInfo &other) const
        {
            return !(*this == other);
        }
    };


    inline QDataStream& operator<<(QDataStream& out,
                                   const ServerInfo& p)
    {
        out << p.name
            << p.version
            << p.website
            << p.avatarHash
            << p.oldAvatarHash
            << p.startTime;

        return out;
    }

    inline QDataStream& operator>>(QDataStream& in,
                                   ServerInfo& p)
    {
        in >> p.name
            >> p.version
            >> p.website
            >> p.avatarHash
            >> p.oldAvatarHash
            >> p.startTime;

        return in;
    }


    struct ServerStatePacket
    {
        ServerInfo serverInfo;
        QList<ChannelInfo> channels;
        QList<UserInfo> users;
    };


    inline QDataStream&
    operator<<(QDataStream& out,
               const ServerStatePacket& p)
    {
        out << p.serverInfo
            << p.channels
            << p.users;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               ServerStatePacket& p)
    {
        in  >> p.serverInfo
            >> p.channels
            >> p.users;

        return in;
    }

}
