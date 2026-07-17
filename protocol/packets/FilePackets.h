#ifndef FILEPACKETS_H
#define FILEPACKETS_H

#pragma once

#include <QString>
#include <QByteArray>
#include <QDataStream>

namespace BeanChatCommon
{

    struct UploadFileBeginPacket
    {
        quint64 channelId;
        QString filename;
        QString mimeType;
        quint64 fileSize;
        QByteArray sha256;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const UploadFileBeginPacket& p)
    {
        out  <<  p.channelId
                << p.filename
                << p.mimeType
                << p.fileSize
                << p.sha256;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UploadFileBeginPacket& p)
    {
        in  >> p.channelId
          >>  p.filename
           >> p.mimeType
           >> p.fileSize
           >> p.sha256;

        return in;
    }


    struct UploadFileChunkPacket
    {
        quint64 uploadId;
        QByteArray payload;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const UploadFileChunkPacket& p)
    {
        out  << p.uploadId
                << p.payload;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UploadFileChunkPacket& p)
    {
        in   >> p.uploadId
              >> p.payload;

        return in;
    }



    struct UploadFileFinishPacket
    {
        quint64 uploadId;
    };
    inline QDataStream&
    operator<<(QDataStream& out,
               const UploadFileFinishPacket& p)
    {
        out  << p.uploadId;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UploadFileFinishPacket& p)
    {
        in   >> p.uploadId;

        return in;
    }


    struct UploadFileBeginResponsePacket
    {
        bool success;
        quint64 uploadId;
        QString error;
    };

    inline QDataStream&
    operator<<(QDataStream& out,
               const UploadFileBeginResponsePacket& p)
    {
        out  << p.success
                << p.uploadId
                <<p.error;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UploadFileBeginResponsePacket& p)
    {
        in    >> p.success
                >> p.uploadId
                >> p.error;

        return in;
    }

    struct UploadFileFinishResponsePacket
    {
        bool success;
        quint64 attachmentId;
        QString error;
    };
    inline QDataStream&
    operator<<(QDataStream& out,
               const UploadFileFinishResponsePacket& p)
    {
        out  << p.success
            << p.attachmentId
            <<p.error;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               UploadFileFinishResponsePacket& p)
    {
        in    >> p.success
            >> p.attachmentId
            >> p.error;

        return in;
    }



    struct DownloadAttachmentPacket
    {
        quint64 attachmentId;
    };
    inline QDataStream&
    operator<<(QDataStream& out,
               const DownloadAttachmentPacket& p)
    {
        out  << p.attachmentId;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               DownloadAttachmentPacket& p)
    {
        in   >> p.attachmentId;

        return in;
    }


    struct DownloadAttachmentBeginPacket
    {
        bool success = false;
        QString error;
        quint64 attachmentId;
        QString filename;
        QString mimeType;
        quint64 size;
        QByteArray sha256;
    };
    inline QDataStream&
    operator<<(QDataStream& out,
               const DownloadAttachmentBeginPacket& p)
    {
        out  << p.success
            << p.error
            << p.attachmentId
            << p.filename
            << p.mimeType
            << p.size
            << p.sha256;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               DownloadAttachmentBeginPacket& p)
    {
        in  >> p.success
           >> p.error
           >> p.attachmentId
           >> p.filename
           >> p.mimeType
           >> p.size
           >> p.sha256;

        return in;
    }



    struct DownloadAttachmentChunkPacket
    {
        quint64 attachmentId;

        QByteArray payload;
    };
    inline QDataStream&
    operator<<(QDataStream& out,
               const DownloadAttachmentChunkPacket& p)
    {
        out  << p.attachmentId
            << p.payload;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               DownloadAttachmentChunkPacket& p)
    {
        in   >> p.attachmentId
            >> p.payload;

        return in;
    }



    struct DownloadAttachmentFinishPacket
    {
        quint64 attachmentId;
    };
    inline QDataStream&
    operator<<(QDataStream& out,
               const DownloadAttachmentFinishPacket& p)
    {
        out  << p.attachmentId;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               DownloadAttachmentFinishPacket& p)
    {
        in   >> p.attachmentId;

        return in;
    }





    struct AttachmentChunkPacket
    {
        quint64 attachmentId;
        QByteArray payload;
        bool lastChunk;
    };
    inline QDataStream&
    operator<<(QDataStream& out,
               const AttachmentChunkPacket& p)
    {
        out  << p.attachmentId
            << p.payload
            << p.lastChunk;

        return out;
    }

    inline QDataStream&
    operator>>(QDataStream& in,
               AttachmentChunkPacket& p)
    {
        in  >> p.attachmentId
            >> p.payload
            >> p.lastChunk;

        return in;
    }

}
#endif // FILEPACKETS_H
