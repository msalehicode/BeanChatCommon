#pragma once

#include <QByteArray>
#include <QString>

#include <QCryptographicHash>

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <QDebug>

namespace BeanChatCommon
{
    class Crypto
    {
    public:

        //--------------------------------------------------------------------------
        // Key generation
        //--------------------------------------------------------------------------

        // Generates a brand new Ed25519 key pair.
        // Returns true on success.
        static bool generateKeyPair(
            QByteArray& publicKey,
            QByteArray& privateKey);

        //--------------------------------------------------------------------------
        // Digital signatures
        //--------------------------------------------------------------------------

        // Signs arbitrary data using the private key.
        // Returns an empty QByteArray on failure.
        static QByteArray sign(
            const QByteArray& privateKey,
            const QByteArray& data);

        // Verifies a signature using the public key.
        static bool verify(
            const QByteArray& publicKey,
            const QByteArray& data,
            const QByteArray& signature);

        //--------------------------------------------------------------------------
        // Random
        //--------------------------------------------------------------------------

        // Returns cryptographically secure random bytes.
        static QByteArray randomBytes(int size);

        //--------------------------------------------------------------------------
        // Validation
        //--------------------------------------------------------------------------

        // Checks whether the supplied public key is a valid Ed25519 public key.
        static bool isValidPublicKey(const QByteArray& publicKey);

        // Checks whether the supplied private key is a valid Ed25519 private key.
        static bool isValidPrivateKey(const QByteArray& privateKey);

        //--------------------------------------------------------------------------
        // Utilities
        //--------------------------------------------------------------------------

        // Returns a SHA-256 fingerprint of a public key.
        // Example:
        // SHA256:U4gBz7r6+Jv...
        static QString fingerprint(const QByteArray& publicKey);



        //test
        static bool selfTest();
    };

} // namespace BeanChatCommon
