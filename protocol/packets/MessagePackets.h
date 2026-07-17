#pragma once

#include <QDateTime>
#include <QDataStream>
#include <QString>

#include "../commonTypes.h"

namespace BeanChatCommon
{
    struct SendMessagePacket
    {
        QString text;
        Msg::Type type;
        quint64 attachmentId = 0;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const SendMessagePacket& p)
    {
        out << p.text
            << p.type
            << p.attachmentId;


        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               SendMessagePacket& p)
    {
        in  >> p.text
            >> p.type
            >> p.attachmentId;

        return in;
    }





    struct ChatMessagePacket
    {
         //fill by server
        quint64 messageId;
        quint64 senderId;
        QString senderName; //sometimes user has disconnected, we don't access to his id to findout what was his name
        // quint64 channelId;
        quint64 attachmentId = 0;
        QDateTime timestamp=QDateTime::currentDateTime();


        //fill by client
        QString text="";
        Msg::Type type = Msg::Type::Text;
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
            << p.attachmentId
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
            >> p.attachmentId
            >> p.timestamp;

        return in;
    }

}
