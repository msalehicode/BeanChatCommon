#pragma once
#include <QDataStream>
#include <QDateTime>
#include "UserPackets.h"
#include "ChannelPackets.h"

namespace BeanChatCommon
{
    struct ServerInfo
    {
        //overview/appearance
        QString name;
        QString avatarHash; //store server's avatarHash, if user couldn't find that hash in cached acatars would ask for avatar. and would store inside user's servers directory
        // QString oldAvatarHash; //when avatar changed to tell users delete old avatar
        QString bannerHash;
        // QString oldBannerHash;
        QString themeColor;


        //general
        QString website;
        QString version;
        bool reportToServerListStatus=false;
        int maxUsers=32;
        int reservedSlots=1; //for admin when server is full!
        bool showOfflineUsers=true; //if it's true would read all users in server and send them to connected client as offline users. if amount of offline users exceeded than a value would just return couple chunk..

        //voice
        int voiceQualityIndex=0;


        //upload and storage
        int maxUploadSizePerFile=1024;//MB
        int totalStorageSpace =1024;//MB


        //message and logs (TEXT CHANNEL)
        int sendWelcomeMessagesToChannel=-1;
        int sendEventLogsToChannel=-1;


        //addons
        bool musicBotStatus=true;
        QString musicBotProxyURL="";
        QString musicBotProxyUser="";
        QString musicBotProxyPass="";


        //security and privacy
        bool serverPasswordStatus =false;
        QString serverPassword="";


        //etc
        QDateTime startTime;

        static ServerInfo convertDataForNormalUser(const ServerInfo& data)
        {
            ServerInfo converted = data;
            converted.reservedSlots=0;
            converted.reportToServerListStatus=false;
            converted.musicBotStatus=false;
            converted.totalStorageSpace=0;
            converted.musicBotProxyURL="";
            converted.musicBotProxyUser="";
            converted.musicBotProxyPass="";
            converted.serverPassword="";
            return converted;
        }

        bool operator==(const ServerInfo &other) const
        {
            return name == other.name &&
                   avatarHash == other.avatarHash &&
                   // oldAvatarHash == other.oldAvatarHash;
                   bannerHash == other.bannerHash &&
                   // oldBannerHash == other.oldBannerHash
                   themeColor == other.themeColor &&

                   website == other.website &&
                   version == other.version &&
                   reportToServerListStatus == other.reportToServerListStatus &&
                   maxUsers == other.maxUsers &&
                   reservedSlots == other.reservedSlots &&
                   showOfflineUsers == other.showOfflineUsers &&

                   voiceQualityIndex == other.voiceQualityIndex &&

                   maxUploadSizePerFile == other.maxUploadSizePerFile &&
                   totalStorageSpace == other.totalStorageSpace &&


                   sendWelcomeMessagesToChannel == other.sendWelcomeMessagesToChannel &&
                   sendEventLogsToChannel == other.sendEventLogsToChannel &&


                   musicBotStatus == other.musicBotStatus &&
                   musicBotProxyURL == other.musicBotProxyURL &&
                   musicBotProxyUser == other.musicBotProxyUser &&
                   musicBotProxyPass == other.musicBotProxyPass &&

                   serverPasswordStatus == other.serverPasswordStatus &&
                   serverPassword == other.serverPassword &&

                       startTime == other.startTime;
        }

        bool operator!=(const ServerInfo &other) const
        {
            return !(*this == other);
        }
    };


    inline QDataStream& operator<<(QDataStream& out,
                                   const ServerInfo& p)
    {
        out << p.name
            << p.avatarHash
            // << p.oldAvatarHash
            << p.bannerHash
            // << p.oldBannerHash
            << p.themeColor

            << p.website
            << p.version
            << p.reportToServerListStatus
            << p.maxUsers
            << p.reservedSlots
            << p.showOfflineUsers

            << p.voiceQualityIndex

            << p.maxUploadSizePerFile
            << p.totalStorageSpace

            << p.musicBotStatus
            << p.musicBotProxyURL
            << p.musicBotProxyUser
            << p.musicBotProxyPass

            << p.serverPasswordStatus
            << p.serverPassword

            << p.startTime;

        return out;
    }
    inline QDataStream& operator>>(QDataStream& in,
                                   ServerInfo& p)
    {
        in >> p.name
            >> p.avatarHash
            // >> p.oldAvatarHash
            >> p.bannerHash
            // >> p.oldBannerHash
            >> p.themeColor

            >> p.website
            >> p.version
            >> p.reportToServerListStatus
            >> p.maxUsers
            >> p.reservedSlots
            >> p.showOfflineUsers

            >> p.voiceQualityIndex

            >> p.maxUploadSizePerFile
            >> p.totalStorageSpace

            >> p.musicBotStatus
            >> p.musicBotProxyURL
            >> p.musicBotProxyUser
            >> p.musicBotProxyPass

            >> p.serverPasswordStatus
            >> p.serverPassword

            >> p.startTime;
        return in;
    }


    struct ServerStatePacket
    {
        ServerInfo serverInfo;
        QList<ChannelInfo> channels;
        QList<UserInfo> users;
    };
    inline QDataStream&
    operator<<(QDataStream& out,
               const ServerStatePacket& p)
    {
        out << p.serverInfo
            << p.channels
            << p.users;

        return out;
    }
    inline QDataStream&
    operator>>(QDataStream& in,
               ServerStatePacket& p)
    {
        in  >> p.serverInfo
            >> p.channels
            >> p.users;

        return in;
    }




    struct UpdateServerSettingsPacket
    {
        ServerInfo serverInfo;
    };
    inline QDataStream&
    operator<<(QDataStream& out,
               const UpdateServerSettingsPacket& p)
    {
        out << p.serverInfo;
        return out;
    }
    inline QDataStream&
    operator>>(QDataStream& in,
               UpdateServerSettingsPacket& p)
    {
        in  >> p.serverInfo;
        return in;
    }


    struct ServerSettingsUpdatedPacket
    {
        ServerInfo serverInfo;
    };
    inline QDataStream&
    operator<<(QDataStream& out,
               const ServerSettingsUpdatedPacket& p)
    {
        out << p.serverInfo;
        return out;
    }
    inline QDataStream&
    operator>>(QDataStream& in,
               ServerSettingsUpdatedPacket& p)
    {
        in  >> p.serverInfo;
        return in;
    }



    struct RedeemPrivilegeTokenPacket
    {
        QString token;
        qint64 userId;
        bool result;
        QString resultMessage;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const RedeemPrivilegeTokenPacket& p)
    {
        out << p.token
                << p.userId
                << p.result
                << p.resultMessage;
        return out;
    }
    inline QDataStream&
    operator>>(QDataStream& in,
               RedeemPrivilegeTokenPacket& p)
    {
        in >> p.token
            >> p.userId
            >> p.result
            >> p.resultMessage;
        return in;
    }
}
