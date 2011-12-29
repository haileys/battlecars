#ifndef PACKET_TYPES_HH
#define PACKET_TYPES_HH

#include <stdint.h>

namespace PacketTypes
{    
    // Client -> Server;
    // Server -> Client;
    const uint32_t PACKET_PING              = 0;
    
    // Client -> Server; std::string name
    // Server -> Client; uint32_t a, uint32_t b
    const uint32_t PACKET_HANDSHAKE         = 1;

    // Client -> Server; uint32_t sum, uint32_t xor // the client adds a and b from the server and xors a and b
    // Server -> Client; uint32_t client_id         // welcome to the server
    const uint32_t PACKET_HANDSHAKE_NONCE   = 2;
        
    // Client -> Server; uint32_t id (of the player the client is interested in)
    // Server -> Client; uint32_t id, std::string name
    const uint32_t PACKET_PLAYER_INFO       = 3;
    
    // Client -> Server; float x, float y, float velocity, float heading
    // Server -> Client; uint32_t id, float x, float y, float velocity, float heading
    const uint32_t PACKET_PLAYER_POSITION   = 4;
    
    // *** The join packet may be sent multiple times
    // Server -> Client; uint32_t id, std::string name, float x, float y, float velocity, float heading
    const uint32_t PACKET_JOIN              = 5;
    
    // Client -> Server;
    // *** The part packet may be sent multiple times
    // Server -> Client; uint32_t id
    const uint32_t PACKET_PART              = 6;
        
    // *** The kick packet may be sent multiple times
    // Server -> Client; std::string reason
    const uint32_t PACKET_KICK              = 7;
}

#endif