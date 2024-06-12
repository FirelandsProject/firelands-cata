/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FC_AUTH_SHA1_H
#define FC_AUTH_SHA1_H

#include "Define.h"
#include <string>
#include <openssl/sha.h>
#include <openssl/evp.h>

class BigNumber;

class FC_COMMON_API SHA1Hash
{
    public:
        SHA1Hash();
        SHA1Hash(SHA1Hash const &other);     // copy
        SHA1Hash(SHA1Hash &&other);          // move
        SHA1Hash &operator=(SHA1Hash other); // assign
        ~SHA1Hash();

        void Swap(SHA1Hash &other) throw();
        friend void Swap(SHA1Hash &left, SHA1Hash &right) { left.Swap(right); }

        void UpdateBigNumbers(BigNumber* bn0, ...);

        void UpdateData(const uint8 *dta, int len);
        void UpdateData(const std::string &str);

        void Initialize();
        void Finalize();

        uint8 *GetDigest(void) { return mDigest; }
        int GetLength(void) const { return SHA_DIGEST_LENGTH; }

    private:
        EVP_MD_CTX *m_ctx;
        uint8 mDigest[SHA_DIGEST_LENGTH];
};

/// Returns the SHA1 hash of the given content as hex string.
FC_COMMON_API std::string CalculateSHA1Hash(std::string const& content);

#endif
