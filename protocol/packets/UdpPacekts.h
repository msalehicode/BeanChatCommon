#pragma once

#include <QByteArray>
#include <QDataStream>

namespace BeanChatCommon
{
    struct UdpRegisterPacket
    {
        quint64 userId;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const UdpRegisterPacket& p)
    {
        out << p.userId;
        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UdpRegisterPacket& p)
    {
        in >> p.userId;
        return in;
    }


    struct PingPacket
    {
        quint32 sequence;
        int lastPing=-1;
        float voicePacketLoss=0.0f;
        float videoPacketLoss=0.0f;
    };

    inline QDataStream& operator<<(QDataStream& out,
                                   const PingPacket& p)
    {
        out << p.sequence
            << p.lastPing
            << p.voicePacketLoss
            << p.videoPacketLoss;

        return out;
    }

    inline QDataStream& operator>>(QDataStream& in,
                                   PingPacket& p)
    {
        in >> p.sequence
            >> p.lastPing
            >> p.voicePacketLoss
            >> p.videoPacketLoss;

        return in;
    }

    //voice
    struct VoicePacket
    {
        quint64 senderId=0;

        quint32 sequence=0;

        QByteArray audioData;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const VoicePacket& p)
    {
        out << p.senderId
            << p.sequence
            << p.audioData;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               VoicePacket& p)
    {
        in >> p.senderId
            >> p.sequence
            >> p.audioData;

        return in;
    }


    //video
    struct VideoPacket
    {
        quint64 senderId=0;

        quint32 sequence=0;

        QByteArray videoData;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const VideoPacket& p)
    {
        out << p.senderId
            << p.sequence
            << p.videoData;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               VideoPacket& p)
    {
        in >> p.senderId
            >> p.sequence
            >> p.videoData;

        return in;
    }

}
