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
    struct VideoFragment
    {
        quint64 senderId;
        quint32 frameId;
        quint16 fragmentIndex;
        quint16 fragmentCount;
        QByteArray payload;
    };


    inline QDataStream&
    operator<<(QDataStream& out,
               const VideoFragment& p)
    {
        out << p.senderId
            << p.frameId
            << p.fragmentIndex
            << p.fragmentCount
            << p.payload;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               VideoFragment& p)
    {
        in  >> p.senderId
            >> p.frameId
            >> p.fragmentIndex
            >> p.fragmentCount
            >> p.payload;

        return in;
    }


    struct PendingFrame
    {
        quint16 expectedFragments = 0;

        QVector<QByteArray> fragments;

        int received = 0;
    };



    inline QDataStream&
    operator<<(QDataStream& out,
               const PendingFrame& p)
    {
        out << p.expectedFragments
            << p.fragments
            << p.received;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               PendingFrame& p)
    {
        in  >> p.expectedFragments
            >> p.fragments
            >> p.received;

        return in;
    }


}
