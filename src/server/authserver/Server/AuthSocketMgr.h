/*
 * Copyright (C) 2022 Firelands <https://github.com/FirelandsProject/>
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

#ifndef AuthSocketMgr_h__
#define AuthSocketMgr_h__

#include "AuthSession.h"
#include "SocketMgr.h"

class AuthSocketMgr : public SocketMgr<AuthSession> {
  typedef SocketMgr<AuthSession> BaseSocketMgr;

public:
  static AuthSocketMgr &Instance() {
    static AuthSocketMgr instance;
    return instance;
  }

  bool StartNetwork(Firelands::Asio::IoContext &ioContext,
                    std::string const &bindIp, uint16 port,
                    int threadCount = 1) override {
    if (!BaseSocketMgr::StartNetwork(ioContext, bindIp, port, threadCount))
      return false;

    _acceptor->AsyncAcceptWithCallback<&AuthSocketMgr::OnSocketAccept>();
    return true;
  }

protected:
  NetworkThread<AuthSession> *CreateThreads() const override {
    return new NetworkThread<AuthSession>[1];
  }

  static void OnSocketAccept(tcp::socket &&sock, uint32 threadIndex) {
    Instance().OnSocketOpen(std::forward<tcp::socket>(sock), threadIndex);
  }
};

#define sAuthSocketMgr AuthSocketMgr::Instance()

#endif // AuthSocketMgr_h__
