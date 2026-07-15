#pragma once
#include <QDataStream>
#include <QString>
#include "../commonTypes.h"

namespace BeanChatCommon
{
    struct LoginRequestPacket
    {
        QString username;
        QByteArray publicKey; //identity
        Presence::Status status=Presence::Status::Online;

        // Client information
        QString appVersion;      // "1.2.5"
        quint32 appProtocolVersion=0; //that BeanChatCommon version using, e.g 1 or 3 , 10 ...
        QString buildType;       // "Release", "Debug"

        // Operating system
        QString osName;          // "Windows", "Linux", "macOS"
        QString osVersion;       // "11", "Ubuntu 24.04"

        // Hardware / machine
        QString machineName;     // Computer hostname
        QString machineId;       // Stable generated ID
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const LoginRequestPacket& p)
    {
        out << p.username
            << p.publicKey
            << p.appVersion
            << p.status
            << p.appProtocolVersion
            << p.buildType
            << p.osName
            << p.osVersion
            << p.machineName
            << p.machineId;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               LoginRequestPacket& p)
    {
        in >> p.username
            >> p.publicKey
            >> p.appVersion
            >> p.status
            >> p.appProtocolVersion
            >> p.buildType
            >> p.osName
            >> p.osVersion
            >> p.machineName
            >> p.machineId;

        return in;
    }



    struct LoginPacket
    {
        //used to send challange to client \
            or signature to server
        QByteArray payload;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const LoginPacket& p)
    {
        out << p.payload;
        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               LoginPacket& p)
    {
        in >> p.payload;
        return in;
    }




    struct LoginResponsePacket
    {
        int id;
        bool accepted;
        QString message;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const LoginResponsePacket& p)
    {
        out << p.id
            << p.accepted
            << p.message;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               LoginResponsePacket& p)
    {
        in >> p.id
            >> p.accepted
            >> p.message;

        return in;
    }


}
