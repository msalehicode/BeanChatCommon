#ifndef COMMONTYPES_H
#define COMMONTYPES_H
#include <QObject>

namespace BeanChatCommon
{
    class Presence
    {
        Q_GADGET

    public:
        enum Status
        {
            Unknown,
            Offline,
            Online, //default
            Idle, //if user become inactive, server set him to idle status (only when user's status is Online or Unknown)
            Away, //user chose to say im away
            Busy,
            DoNotDisturb
        };
        Q_ENUM(Status)
    };

    static bool isValidPresenceStatus(const Presence::Status& status)
    {
        switch (status)
        {
            case Presence::Status::Offline:
            case Presence::Status::Online:
            case Presence::Status::Idle:
            case Presence::Status::Away:
            case Presence::Status::Busy:
            case Presence::Status::DoNotDisturb:
                return true;
        }
        return false;
    }

    class Msg
    {
        Q_GADGET
    public:
        enum Type
        {
            Text,
            Image,
            AnimatedImage,
            Video,
            Audio,
            File,
            Link,
            Code,
            Sticker
        };
        Q_ENUM(Type)
    };

    class ChannelType
    {
        Q_GADGET
    public:
        enum Type
        {
            Unknown=0,
            Voice,
            Text
        };
        Q_ENUM(Type)
    };
}

#endif // COMMONTYPES_H
