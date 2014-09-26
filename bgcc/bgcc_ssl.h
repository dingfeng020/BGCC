#ifndef BGCC_SSL_H
#define BGCC_SSL_H

#include <openssl/ssl.h>

namespace bgcc {

    extern SSL_CTX* g_ssl_ctx;

    enum ssl_type {
        SSL_SERVER,
        SSL_CLIENT
    };

    enum ssl_version {
        SSLv2,
        SSLv3,
        TLSv1,
        SSLv23
    };

    struct ssl_init {
        enum ssl_type type;
        enum ssl_version version;
        const char* cert_file;
        const char* pkey_file;
    };

    int ssl_init(const struct ssl_init* init);

    int ssl_uninit();

}

#endif
