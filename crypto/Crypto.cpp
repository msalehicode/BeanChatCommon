#include "Crypto.h"

namespace BeanChatCommon
{
    bool Crypto::generateKeyPair(
        QByteArray& publicKey,
        QByteArray& privateKey)
    {
        publicKey.clear();
        privateKey.clear();

        EVP_PKEY_CTX* ctx =
            EVP_PKEY_CTX_new_id(
                EVP_PKEY_ED25519,
                nullptr);

        if(!ctx)
            return false;

        if(EVP_PKEY_keygen_init(ctx) <= 0)
        {
            EVP_PKEY_CTX_free(ctx);
            return false;
        }

        EVP_PKEY* key = nullptr;

        if(EVP_PKEY_keygen(ctx, &key) <= 0)
        {
            EVP_PKEY_CTX_free(ctx);
            return false;
        }

        EVP_PKEY_CTX_free(ctx);

        size_t publicLength = 32;
        unsigned char publicBuffer[32];

        if(EVP_PKEY_get_raw_public_key(
                key,
                publicBuffer,
                &publicLength) <= 0)
        {
            EVP_PKEY_free(key);
            return false;
        }

        size_t privateLength = 32;
        unsigned char privateBuffer[32];

        if(EVP_PKEY_get_raw_private_key(
                key,
                privateBuffer,
                &privateLength) <= 0)
        {
            EVP_PKEY_free(key);
            return false;
        }

        EVP_PKEY_free(key);

        publicKey =
            QByteArray(
                reinterpret_cast<char*>(publicBuffer),
                publicLength);

        privateKey =
            QByteArray(
                reinterpret_cast<char*>(privateBuffer),
                privateLength);

        return true;
    }

    QByteArray Crypto::randomBytes(
        int size)
    {
        QByteArray bytes(size, Qt::Uninitialized);

        if(RAND_bytes(
                reinterpret_cast<unsigned char*>(bytes.data()),
                size) != 1)
        {
            return {};
        }

        return bytes;
    }

    QString Crypto::fingerprint(
        const QByteArray& publicKey)
    {
        QByteArray hash =
            QCryptographicHash::hash(
                publicKey,
                QCryptographicHash::Sha256);

        return QStringLiteral("SHA256:%1")
            .arg(QString::fromLatin1(hash.toBase64()));
    }

    bool Crypto::isValidPublicKey(
        const QByteArray& publicKey)
    {
        EVP_PKEY* key =
            EVP_PKEY_new_raw_public_key(
                EVP_PKEY_ED25519,
                nullptr,
                reinterpret_cast<const unsigned char*>(publicKey.constData()),
                publicKey.size());

        if(!key)
            return false;

        EVP_PKEY_free(key);

        return true;
    }

    bool Crypto::isValidPrivateKey(
        const QByteArray& privateKey)
    {
        EVP_PKEY* key =
            EVP_PKEY_new_raw_private_key(
                EVP_PKEY_ED25519,
                nullptr,
                reinterpret_cast<const unsigned char*>(privateKey.constData()),
                privateKey.size());

        if(!key)
            return false;

        EVP_PKEY_free(key);

        return true;
    }


    QByteArray Crypto::sign(
        const QByteArray& privateKey,
        const QByteArray& data)
    {
        EVP_PKEY* key =
            EVP_PKEY_new_raw_private_key(
                EVP_PKEY_ED25519,
                nullptr,
                reinterpret_cast<const unsigned char*>(privateKey.constData()),
                privateKey.size());

        if(!key)
            return {};

        EVP_MD_CTX* ctx =
            EVP_MD_CTX_new();

        if(!ctx)
        {
            EVP_PKEY_free(key);
            return {};
        }

        if(EVP_DigestSignInit(
                ctx,
                nullptr,
                nullptr,
                nullptr,
                key) <= 0)
        {
            EVP_MD_CTX_free(ctx);
            EVP_PKEY_free(key);
            return {};
        }

        size_t signatureLength = 0;

        if(EVP_DigestSign(
                ctx,
                nullptr,
                &signatureLength,
                reinterpret_cast<const unsigned char*>(data.constData()),
                data.size()) <= 0)
        {
            EVP_MD_CTX_free(ctx);
            EVP_PKEY_free(key);
            return {};
        }

        QByteArray signature(
            signatureLength,
            Qt::Uninitialized);

        if(EVP_DigestSign(
                ctx,
                reinterpret_cast<unsigned char*>(signature.data()),
                &signatureLength,
                reinterpret_cast<const unsigned char*>(data.constData()),
                data.size()) <= 0)
        {
            EVP_MD_CTX_free(ctx);
            EVP_PKEY_free(key);
            return {};
        }

        signature.resize(signatureLength);

        EVP_MD_CTX_free(ctx);
        EVP_PKEY_free(key);

        return signature;
    }


    bool Crypto::verify(
        const QByteArray& publicKey,
        const QByteArray& data,
        const QByteArray& signature)
    {
        EVP_PKEY* key =
            EVP_PKEY_new_raw_public_key(
                EVP_PKEY_ED25519,
                nullptr,
                reinterpret_cast<const unsigned char*>(publicKey.constData()),
                publicKey.size());

        if(!key)
            return false;

        EVP_MD_CTX* ctx =
            EVP_MD_CTX_new();

        if(!ctx)
        {
            EVP_PKEY_free(key);
            return false;
        }

        if(EVP_DigestVerifyInit(
                ctx,
                nullptr,
                nullptr,
                nullptr,
                key) <= 0)
        {
            EVP_MD_CTX_free(ctx);
            EVP_PKEY_free(key);
            return false;
        }

        bool ok =
            EVP_DigestVerify(
                ctx,
                reinterpret_cast<const unsigned char*>(signature.constData()),
                signature.size(),
                reinterpret_cast<const unsigned char*>(data.constData()),
                data.size()) == 1;

        EVP_MD_CTX_free(ctx);
        EVP_PKEY_free(key);

        return ok;
    }



    bool Crypto::selfTest()
    {
        qDebug() << "========== BeanChat Crypto Self Test ==========";

        QByteArray publicKey;
        QByteArray privateKey;

        if(!generateKeyPair(publicKey, privateKey))
        {
            qDebug() << "FAILED: generateKeyPair()";
            return false;
        }

        qDebug() << "Public Key Size :" << publicKey.size();
        qDebug() << "Private Key Size:" << privateKey.size();

        QByteArray challenge = randomBytes(32);

        QByteArray signature = sign(privateKey, challenge);

        qDebug() << "Signature Size :" << signature.size();

        if(!verify(publicKey, challenge, signature))
        {
            qDebug() << "FAILED: verify()";
            return false;
        }

        // Modify challenge
        QByteArray modifiedChallenge = challenge;
        modifiedChallenge[0] ^= 1;

        if(verify(publicKey, modifiedChallenge, signature))
        {
            qDebug() << "FAILED: Modified challenge accepted.";
            return false;
        }

        // Modify signature
        QByteArray modifiedSignature = signature;
        modifiedSignature[0] ^= 1;

        if(verify(publicKey, challenge, modifiedSignature))
        {
            qDebug() << "FAILED: Modified signature accepted.";
            return false;
        }

        // Wrong key
        QByteArray otherPublic;
        QByteArray otherPrivate;

        generateKeyPair(
            otherPublic,
            otherPrivate);

        if(verify(otherPublic, challenge, signature))
        {
            qDebug() << "FAILED: Wrong public key accepted.";
            return false;
        }

        qDebug() << "All crypto tests passed.";
        qDebug() << "===============================================";

        return true;
    }
}
