#pragma once

#include <QDateTime>
#include <QDataStream>
#include <QString>

namespace BeanChatCommon
{
    struct SendMessagePacket
    {
        enum Type
        {
            Text,
            Image,
            Video,
            File,
            Link,
            Emoji
        };

        QString text;
        Type type;
        QString mediaPath;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const SendMessagePacket& p)
    {
        out << p.text
            << p.type
            << p.mediaPath;


        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               SendMessagePacket& p)
    {
        in  >> p.text
            >> p.type
            >> p.mediaPath;

        return in;
    }





    struct ChatMessagePacket
    {
        enum Type
        {
            Text,
            Image,
            Video,
            File,
            Link,
            Emoji
        };

        //fill by server
        quint64 messageId;
        quint64 senderId;
        QString senderName; //sometimes user has disconnected, we don't access to his id to findout what was his name
        // quint64 channelId;
        QDateTime timestamp=QDateTime::currentDateTime();


        //fill by client
        QString text="";
        Type type = Text;
        QString mediaPath="";
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const ChatMessagePacket& p)
    {
        out << p.messageId
            << p.senderId
            // << p.channelId
            << p.senderName
            << p.text
            << p.type
            << p.mediaPath
            << p.timestamp;


        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               ChatMessagePacket& p)
    {
        in >> p.messageId
            >> p.senderId
            // >> p.channelId
            >> p.senderName
            >> p.text
            >> p.type
            >> p.mediaPath
            >> p.timestamp;

        return in;
    }

}
