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
        quint64 targetTextChannelId = 0; //this uses to send message in text channels, but for voice channel's send text we dont use this read it direcly from user's currentChannel
        Msg::Type type;
        quint64 attachmentId = 0;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const SendMessagePacket& p)
    {
        out << p.text
            << p.targetTextChannelId
            << p.type
            << p.attachmentId;


        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               SendMessagePacket& p)
    {
        in  >> p.text
            >> p.targetTextChannelId
            >> p.type
            >> p.attachmentId;

        return in;
    }





    struct ChatMessagePacket
    {
         //fill by server
        quint64 messageId=0; //for text in voice channels with saveChats OFF always would be 0 otherwise would be saved message id on database
        quint64 senderId;
        QString senderName; //sometimes user has disconnected, we don't access to his id to findout what was his name
        quint64 channelId=0;//only used for text channel types, if channel type is chat would set to 0
        quint64 attachmentId = 0; //by default 0 means no attachment
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
            << p.channelId
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
            >> p.channelId
            >> p.senderName
            >> p.text
            >> p.type
            >> p.attachmentId
            >> p.timestamp;

        return in;
    }


    struct ChatMessageChunkPacket
    {
        quint64 channelId;
        QList<ChatMessagePacket> messages;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const ChatMessageChunkPacket& p)
    {
        out << p.channelId
                << p.messages;
        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               ChatMessageChunkPacket& p)
    {
        in >> p.channelId
             >> p.messages;

        return in;
    }



}
