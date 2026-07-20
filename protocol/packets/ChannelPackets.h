#pragma once
#include <QDataStream>
#include <QString>

#include "../commonTypes.h"

namespace BeanChatCommon
{
    struct CreateChannelPacket
    {
        QString name;
        QString password;
        ChannelType::Type type = ChannelType::Type::Voice;
        bool saveChats;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const CreateChannelPacket& p)
    {
        out << p.name
            << p.password
            << p.type
            << p.saveChats;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               CreateChannelPacket& p)
    {
        in >> p.name
            >> p.password
            >> p.type
            >> p.saveChats;

        return in;
    }


    struct UpdateChannelPacket
    {
        quint64 channelId;
        QString name;
        QString password;
        bool saveChats;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const UpdateChannelPacket& p)
    {
        out << p.channelId
            << p.name
            << p.password
            << p.saveChats;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UpdateChannelPacket& p)
    {
        in  >> p.channelId
            >> p.name
            >> p.password
            >> p.saveChats;

        return in;
    }




    struct ChannelUpdatedPacket
    {
        quint64 channelId;
        QString name;
        bool isLocked;
        bool saveChats;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const ChannelUpdatedPacket& p)
    {
        out << p.channelId
            << p.name
            << p.isLocked
            << p.saveChats;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               ChannelUpdatedPacket& p)
    {
        in  >> p.channelId
            >> p.name
            >> p.isLocked
            >> p.saveChats;

        return in;
    }

    struct DeleteChannelPacket
    {
        quint64 channelId;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const DeleteChannelPacket& p)
    {
        out << p.channelId;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               DeleteChannelPacket& p)
    {
        in  >> p.channelId;

        return in;
    }





    struct JoinChannelPacket
    {
        quint64 channelId;
        QString password;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const JoinChannelPacket& p)
    {
        out << p.channelId
            << p.password;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               JoinChannelPacket& p)
    {
        in >> p.channelId
            >> p.password;

        return in;
    }

    struct ChannelCreatedPacket
    {
        quint64 id;
        QString name;
        ChannelType::Type type = ChannelType::Type::Voice;
        bool isLocked=false;
        bool saveChats=false;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const ChannelCreatedPacket& p)
    {
        out << p.id
            << p.name
            << p.type
            << p.isLocked
            << p.saveChats;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               ChannelCreatedPacket& p)
    {
        in >> p.id
            >> p.name
            >> p.type
            >> p.isLocked
            >> p.saveChats;

        return in;
    }

    struct UserJoinedChannelPacket
    {
        quint64 userId;
        quint64 channelId=0;
        quint64 oldChannelId;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const UserJoinedChannelPacket& p)
    {
        out << p.userId
            << p.channelId
            << p.oldChannelId;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UserJoinedChannelPacket& p)
    {
        in >> p.userId
            >> p.channelId
            >> p.oldChannelId;

        return in;
    }




    struct ChannelInfo
    {
        quint64 id;
        QString name;
        ChannelType::Type type;
        bool isLocked;
        bool saveChats;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const ChannelInfo& p)
    {
        out << p.id
            << p.name
            << p.type
            << p.saveChats
            << p.isLocked;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               ChannelInfo& p)
    {
        in >> p.id
            >> p.name
            >> p.type
            >> p.saveChats
            >> p.isLocked;

        return in;
    }



}
