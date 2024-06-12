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

#include <OpenSSLCrypto.h>
#include <openssl/crypto.h>
#include <vector>
#include <thread>
#include <mutex>

#include <openssl/provider.h>
OSSL_PROVIDER* LegacyProvider;
OSSL_PROVIDER* DefaultProvider;

void OpenSSLCrypto::threadsSetup([[maybe_unused]] boost::filesystem::path const &providerModulePath)
{
#if OPENSSL_VERSION_NUMBER >= 0x30000000L
#if FC_PLATFORM == FC_PLATFORM_WINDOWS
    OSSL_PROVIDER_set_default_search_path(nullptr, providerModulePath.string().c_str());
#endif
    LegacyProvider = OSSL_PROVIDER_load(nullptr, "legacy");
    DefaultProvider = OSSL_PROVIDER_load(nullptr, "default");
#endif
}

void OpenSSLCrypto::threadsCleanup()
{
    OSSL_PROVIDER_unload(LegacyProvider);
    OSSL_PROVIDER_unload(DefaultProvider);
    OSSL_PROVIDER_set_default_search_path(nullptr, nullptr);
}
