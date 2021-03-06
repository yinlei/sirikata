// Copyright (c) 2011 Sirikata Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#ifndef _SIRIKATA_LIBCORE_XDP_PORT_HPP_
#define _SIRIKATA_LIBCORE_XDP_PORT_HPP_

#include <sirikata/core/xdp/Defs.hpp>

namespace Sirikata {
namespace XDP {

/** ODP::Port is the interface for bound ports that allows sending and receiving
 *  ODP messages.  By default no listeners are bound and messages will bypass
 *  the Port and be received by any more generic listeners registered with the
 *  parent ODP::Service.  To receive messages via this port, register a listener
 *  with receive() or receiveFrom().  Messages can only be sent via this port
 *  to endpoints in the same Space as this Port.
 *
 *  It is possible for multiple registered receive callbacks to be able to
 *  handle a message since the components of an endpoint support wildcards.  For
 *  example, if handlers were registered for SpaceID X, ObjectReference Y, and
 *  one with PortID 1 and one with PortID::any(), both would be capable of
 *  handling a message to (X, Y, 1). Resolution of handlers is always from
 *  more-detailed to less-detailed, *with PortID being highest priority,
 *  followed by SpaceID, with ObjectReference being lowest priority*.  This
 *  order is used because generally PortID's will be associated with a
 *  particular service or protocol, which is likely to function across multiple
 *  spaces and be indifferent to the object it is communicating with (for
 *  instance, a protocol which simply responds to requests for meshes).
 *  Therefore, handler resolution proceeds as follows for a message from
 *  endpoint (S, O, P):
 *   -# Check for handler for (S, O, P)
 *   -# Check for handler for (S, any, P)
 *   -# Check for handler for (any, any, P)
 *   -# Check for handler for (S, O, any)
 *   -# Check for handler for (S, any, any)
 *   -# Check for handler for (any, any, any)
 *  Note that combinations which have an object specified but not match any space
 *  are not checked.  This combination generally doesn't make sense since an
 *  object reference won't be valid across spaces.
 *
 *  Once allocated, a Port is owned by the allocator: if the Service it was
 *  allocated from is destroyed, the user is responsible for not using the Port
 *  any more, and is always responsible for deleting the Port.
 */
template<typename EndpointType>
class Port {
public:
    typedef EndpointType Endpoint;
    typedef typename Endpoint::MessageHandler MessageHandler;

    virtual ~Port() {}

    /** Get the endpoint associated with this port. Note that this will always
     *  be a full and unique endpoint, i.e. none of its components will be
     *  their corresponding ANY sentinal values.
     */
    virtual const Endpoint& endpoint() const = 0;

    /** Send an ODP message from this port. The destination endpoint *must* be
     *  unique and have the same SpaceID as this Port's endpoint.
     *  \param to the endpoint to send the message to
     *  \param payload the message payload
     *  \returns true if the message was accepted, false if the underlying
     *           networking layer couldn't immediately accept the message
     */
    virtual bool send(const Endpoint& to, MemoryReference payload) = 0;

    /** Register a default handler for messages received on this port. This is
     *  a utility method that is a shorthand for receiveFrom(Endpoint::any(),
     *  cb).
     *  \param cb handler to invoke when messages are receive
     */
    void receive(const MessageHandler& cb) {
        receiveFrom(Endpoint::any(), cb);
    }

    /** Register a handler for messages from the specified endpoint.
     *  \param from endpoint to dispatch messages from
     *  \param cb handler to invoke when messages are received
     */
    virtual void receiveFrom(const Endpoint& from, const MessageHandler& cb) = 0;

}; // class Port

} // namespace XDP
} // namespace Sirikata

#endif //_SIRIKATA_LIBCORE_XDP_PORT_HPP_
