/*  Sirikata
 *  TimeSyncServer.hpp
 *
 *  Copyright (c) 2010, Ewen Cheslack-Postava
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of Sirikata nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sirikata/core/util/Standard.hh>
#include <sirikata/core/sync/TimeSyncServer.hpp>

#include <Protocol_TimeSync.pbj.hpp>
#include <sirikata/core/network/Message.hpp> //serializePBJMessage
#include <sirikata/core/network/ObjectMessage.hpp> // OBJECT_PORT_TIMESYNC

namespace Sirikata {

TimeSyncServer::TimeSyncServer(Context* ctx, OHDP::Service* ohdp)
 : mContext(ctx)
{
    mPort = ohdp->bindOHDPPort(OBJECT_PORT_TIMESYNC);
    if (mPort == NULL) {
        SILOG(timesync,fatal,"Couldn't bind port " << OBJECT_PORT_TIMESYNC << " for TimeSyncServer, must already be in use...");
    }
    else {
        SILOG(timesync, detailed, "Listening for time sync messages...");
        mPort->receive(
            std::tr1::bind(&TimeSyncServer::handleMessage, this, _1, _2, _3)
        );
    }
}

TimeSyncServer::~TimeSyncServer() {
    delete mPort;
}

void TimeSyncServer::handleMessage(const OHDP::Endpoint& src, const OHDP::Endpoint& dst, MemoryReference payload) {
    SILOG(timesync, detailed, "Received time sync message from remote node " << src.node());

    Sirikata::Protocol::TimeSync sync_msg;
    bool parse_success = sync_msg.ParseFromArray(payload.data(), payload.size());
    if (!parse_success) {
        LOG_INVALID_MESSAGE_BUFFER(sync, error, ((char*)payload.data()), payload.size());
        return;
    }

    // Our only job is to take the existing message, fill in a timestamp, and
    // send it back.
    sync_msg.set_t(mContext->simTime());
    String resp = serializePBJMessage(sync_msg);
    mPort->send(src, MemoryReference(resp));
    SILOG(timesync, detailed, "Sent time sync message reply to remote node " << src.node());
}

} // namespace Sirikata
