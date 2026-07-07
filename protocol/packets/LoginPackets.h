#pragma once
#include <QDataStream>
#include <QString>

namespace BeanChatCommon
{
    struct LoginRequestPacket
    {
        QString username;
        QByteArray publicKey; //identity

        // Client information
        QString appVersion;      // "1.2.5"
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
