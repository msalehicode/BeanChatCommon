#pragma once
#include <QtGlobal>

namespace BeanChatCommon
{
    enum class PacketType : quint16
    {
        Invalid = 0,

        //login
        LoginRequest,
        LoginChallenge,
        LoginProof,
        LoginResponse,


        //connection
        UserConnected,
        UserDisconnected,
        UserConnectionLost,


        //channel
        CreateChannel,
        UpdateChannel,
        DeleteChannel,

        ChannelCreated,
        ChannelUpdated,
        ChannelDeleted,


        //chat
        ChatMessage,

        //chat file
        UploadFileBegin,
        UploadFileBeginResponse,

        UploadFileChunk,

        UploadFileFinish,
        UploadFileFinishResponse,

        DownloadAttachment,
        DownloadAttachmentBegin,//response
        DownloadAttachmentChunk,
        DownloadAttachmentFinish,



        //join,move
        JoinChannel,
        UserJoinedChannel,

        MoveUser,
        UserMoved,


        //status
        UserMuted ,
        UserUnmuted ,

        UserDeafened ,
        UserUndeafened ,

        UserCameraOpened,
        UserCameraClosed,


        //user info
        RequestAvatars, //user sends those ids has no cached matches for those avatars
        ResponseAvatars, //server send avatar data for those ids

        UpdateUserInfo, //user sends to ask to update username, avatar, ...
        UserInfoChanged, //users receive this when someone changed his info

        //state
        RequestServerState,
        ServerState, //response to RequestServerState


        //udp codes:
        UdpLoginRequest = 100, //when user loginResponse arrived client sends this to server to register udp socket.
        UdpLoginResponse = 101, //response to Udplogin
        UdpPingRequest = 102, //continuesly server sends to registered UDP clients
        UdpPingResponse = 103, //client responses to server's PingRequest
        UdpVoiceData = 104,
        UdpVideoData =105
    };
}
