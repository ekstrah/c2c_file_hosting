AUTHORS:
Dongho Kim

This is a small program that demonstrates basic communication using UDP sockets with Selective Repeat Protocol

PORT NUMBER is fixed in port.h

TO RUN:
    //client
    ./udp-send <file-path> <file-name> <server-IP>

    //server
    ./udp-recv <file-path>

PACKET FORMAT:
----------------------------------------------------------------------------------------------------
| 508 Bytes for the data potion | 4 bytes for an unsigned integer representing the sequence number|
----------------------------------------------------------------------------------------------------
We chose a window size of 16. 

Both server and client must agree to the same packet format.
