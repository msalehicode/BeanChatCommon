#pragma once
#include <QDataStream>

namespace BeanChatCommon
{
    struct UserStatusChangedPacket
    {
        quint64 userId;
        quint64 userChannelId;
        bool status; //status type would set by PacketType::UserMuted or ..
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const UserStatusChangedPacket& p)
    {
        out << p.userId
            << p.userChannelId
            << p.status;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UserStatusChangedPacket& p)
    {
        in >> p.userId
            >> p.userChannelId
            >> p.status;

        return in;
    }





    struct MoveUserPacket
    {
        quint64 userId;
        quint64 channelId;
        QString channelPassword="";
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const MoveUserPacket& p)
    {
        out << p.userId
            << p.channelId
            << p.channelPassword;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               MoveUserPacket& p)
    {
        in >> p.userId
            >> p.channelId
            >> p.channelPassword;

        return in;
    }




    struct UserConnectedPacket
    {
        quint64 id;
        QString username;
        QString identity;
        QString avatarHash;
        bool muted=false;
        bool deafened=false;
        bool camera=false;

        // Client information
        QString appVersion;      // "1.2.5"
        QString buildType;       // "Release", "Debug"

        // Operating system
        QString osName;          // "Windows", "Linux", "macOS"
        QString osVersion;       // "11", "Ubuntu 24.04"

    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const UserConnectedPacket& p)
    {
        out << p.id
            << p.username
            << p.identity
            << p.avatarHash
            << p.muted
            << p.deafened
            << p.camera
            << p.appVersion
            << p.buildType
            << p.osName
            << p.osVersion;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UserConnectedPacket& p)
    {
        in >> p.id
            >> p.username
            >> p.identity
            >> p.avatarHash
            >> p.muted
            >> p.deafened
            >> p.camera
            >> p.appVersion
            >> p.buildType
            >> p.osName
            >> p.osVersion;

        return in;
    }

    struct UserDisconnectedPacket
    {
        quint64 id;
        bool wasConnectionLost=false;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const UserDisconnectedPacket& p)
    {
        out << p.id
            << p.wasConnectionLost;
        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UserDisconnectedPacket& p)
    {
        in >> p.id
            >> p.wasConnectionLost;
        return in;
    }




    struct UserInfo
    {
        quint64 id;

        QString username;
        QString identity;
        QString avatarHash;

        quint64 channelId;

        bool muted=false;
        bool deafened=false;
        bool camera=false;


        // Client information
        QString appVersion;      // "1.2.5"
        QString buildType;       // "Release", "Debug"

        // Operating system
        QString osName;          // "Windows", "Linux", "macOS"
        QString osVersion;       // "11", "Ubuntu 24.04"
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const UserInfo& p)
    {
        out << p.id
            << p.username
            << p.identity
            << p.avatarHash
            << p.channelId
            << p.muted
            << p.deafened
            << p.camera
            << p.appVersion
            << p.buildType
            << p.osName
            << p.osVersion;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UserInfo& p)
    {
        in >> p.id
            >> p.username
            >> p.identity
            >> p.avatarHash
            >> p.channelId
            >> p.muted
            >> p.deafened
            >> p.camera
            >> p.appVersion
            >> p.buildType
            >> p.osName
            >> p.osVersion;


        return in;
    }





    struct RequestAvatarsPacket
    {
        QList<quint64> notFoundIds; //list of userId
    };

    inline QDataStream& operator<<(QDataStream& out,
                                   const RequestAvatarsPacket& p)
    {
        out << p.notFoundIds;
        return out;
    }

    inline QDataStream& operator>>(QDataStream& in,
                                   RequestAvatarsPacket& p)
    {
        in >> p.notFoundIds;
        return in;
    }


    struct UserAvatar
    {
        quint64 userId;
        QString avatarHash;
        QString oldHash; //if isn't empty -> to delete old pic in cache user directory
        QByteArray imageData;

        void clear()
        {
            userId=-1;
            avatarHash.clear();
            oldHash.clear();
            imageData.clear();
        }
    };
    inline QDataStream& operator<<(QDataStream& out,
                                   const UserAvatar& p)
    {
        out << p.userId
            << p.avatarHash
            << p.oldHash
            << p.imageData;

        return out;
    }

    inline QDataStream& operator>>(QDataStream& in,
                                   UserAvatar& p)
    {
        in >> p.userId
            >> p.avatarHash
            >> p.oldHash
            >> p.imageData;

        return in;
    }


    struct ResponseAvatarsPacket
    {
        QList<UserAvatar> avatars; //userId, oldHash, avatarHash, image data
    };

    inline QDataStream& operator<<(QDataStream& out,
                                   const ResponseAvatarsPacket& p)
    {
        out << p.avatars;

        return out;
    }

    inline QDataStream& operator>>(QDataStream& in,
                                   ResponseAvatarsPacket& p)
    {
        in >> p.avatars;

        return in;
    }



    enum class UpdateUserInfoType
    {
        Username,
        Description,
        Identity,
        Avatar,
        ActivityStatus
    };

    struct UpdateUserInfoPacket
    {
        UpdateUserInfoType updateType;
        QString payloadValue;
        QByteArray paylaodData; //for avatar image.
    };

    inline QDataStream& operator<<(QDataStream& out,
                                   const UpdateUserInfoPacket& p)
    {
        out << p.updateType
            << p.payloadValue
            << p.paylaodData;

        return out;
    }

    inline QDataStream& operator>>(QDataStream& in,
                                   UpdateUserInfoPacket& p)
    {
        in >> p.updateType
            >> p.payloadValue
            >> p.paylaodData;

        return in;
    }



    struct UserInfoChangedPacket
    {
        quint64 userId;
        UpdateUserInfoType updateType;
        QString payloadValue; //e.g to pass avatar Hash
        QString payloadSecondValue; //for e.g old hash to tell others delete old avatarHash file
        QByteArray payloadData; //e.g: for avatar image data.
    };

    inline QDataStream& operator<<(QDataStream& out,
                                   const UserInfoChangedPacket& p)
    {
        out << p.userId
            << p.updateType
            << p.payloadValue
            << p.payloadSecondValue
            << p.payloadData;

        return out;
    }

    inline QDataStream& operator>>(QDataStream& in,
                                   UserInfoChangedPacket& p)
    {
        in  >> p.userId
            >> p.updateType
            >> p.payloadValue
            >> p.payloadSecondValue
            >> p.payloadData;

        return in;
    }

}
