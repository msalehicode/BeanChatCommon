#ifndef COMMONTYPES_H
#define COMMONTYPES_H

namespace BeanChatCommon
{
    enum class PresenceStatus
    {
        Unknown=0,
        Offline,
        Online, //default
        Idle, //if user become inactive, server set him to idle status (only when user's status is Online or Unknown)
        Away, //user chose to say im away
        Busy,
        DoNotDisturb
    };

    static bool isValidPresenceStatus(const PresenceStatus& status)
    {
        switch (status)
        {
            case PresenceStatus::Offline:
            case PresenceStatus::Online:
            case PresenceStatus::Idle:
            case PresenceStatus::Away:
            case PresenceStatus::Busy:
            case PresenceStatus::DoNotDisturb:
                return true;
        }
        return false;
    }
}

#endif // COMMONTYPES_H
