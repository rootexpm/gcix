#pragma once
#include "ltbasetypes.h"

#define LTNULL 0
#define MAX_SGR_STRINGLEN   100

#define MAX_NETSESSIONNAME_LEN  4096
#define MAX_NETPASSWORD_LEN     64
#define MAX_HOSTIP_LEN          32
#define NO_HOST_PORT            0xFFFF

class NetSession {
public:
    NetSession() { Clear(); }
    virtual ~NetSession() {}

    void Clear() {
        m_dwFlags = 0;
        m_dwMaxConnections = 0;
        m_dwCurConnections = 0;
        m_Ping = 0;
        m_sName[0] = 0;
        m_bHasPassword = false;
        m_HostIP[0] = 0;
        m_HostPort = NO_HOST_PORT;
        m_pNext = LTNULL;
        m_nGameType = 0;
    }

    uint32 m_dwFlags;
    LTGUID m_guidApp;
    LTGUID m_guidInst;
    uint32 m_dwMaxConnections;
    uint32 m_dwCurConnections;
    uint32 m_Ping; //! Ping time in milliseconds.

    /*!
    Host info.  0 length string and NO_HOST_PORT if not on TCP/IP.
    */
    char m_HostIP[MAX_HOSTIP_LEN];
    uint32 m_HostPort;

    char m_sName[MAX_NETSESSIONNAME_LEN];
    char m_bHasPassword;
    uint8 m_nGameType;
    NetSession* m_pNext;
};

enum
{

    //! Start a world and host it (using dialogs).
    STARTGAME_HOST = 0,

    //! Start a world and host on TCP/IP.
    STARTGAME_HOSTTCP = 1,

    //! Connect to a server using dialogs.
    STARTGAME_CLIENT = 2,

    //! Connect to the first TCP/IP game it can find at m_pTCPAddress.
    STARTGAME_CLIENTTCP = 3,

    //! Start a normal game.
    STARTGAME_NORMAL = 4,

    //! (Used for GetGameMode, means we're not running a world or on a server yet).
    GAMEMODE_NONE = 5
};

struct NetHost {
    uint32 m_Port; //! Port if TCP/IP.  If zero, it uses the default.
    uint32 m_dwFlags;
    uint32 m_dwMaxConnections;
    char m_sName[MAX_NETSESSIONNAME_LEN];
    bool m_bHasPassword;
    uint8 m_nGameType;
};

class StartGameRequest
{
public:
    StartGameRequest() {
        m_Type = STARTGAME_NORMAL;
        m_WorldName[0] = 0;
        m_TCPAddress[0] = 0;
        m_RecordFilename[0] = 0;
        m_PlaybackFilename[0] = 0;
        m_flags = 0;
        m_pGameInfo = LTNULL;
        m_GameInfoLen = 0;
        m_pNetSession = LTNULL;
        m_pClientData = LTNULL;
        m_ClientDataLen = 0;
    }

    int m_Type;
    char m_WorldName[MAX_SGR_STRINGLEN];

    //! TCP/IP address, if any.
    char m_TCPAddress[MAX_SGR_STRINGLEN];

    /*!
    Filename to record into, if any (set this to 0 length if you don't want to record).

    \note When this is set, the engine starts the server but doesn't run the level; you must
    send a message to the server telling it to load the world.
    */
    char m_RecordFilename[MAX_SGR_STRINGLEN];

    /*!
    The filename of a recorded demo.  If this is filled in, the engine starts a server
    and fills in m_WorldName with the world that the demo record uses.  You need to
    send a message to the server telling it to load that world.
    */
    char m_PlaybackFilename[MAX_SGR_STRINGLEN];

    //! This must be used with STARTGAME_CLIENT.
    NetSession* m_pNetSession;

    //! This must be used with STARTGAME_HOST.
    NetHost m_HostInfo;

    //! Various flags.
    uint32 m_flags;

    /*!
    This data is copied over and can be accessed by
    the server with ServerDE::GetGameInfo() (if you're
    running a local or hosted game).
    */
    void* m_pGameInfo;
    uint32 m_GameInfoLen;

    /*!
    This data gets sent up and passed into OnClientEnterWorld on the server.
    */
    void* m_pClientData;
    uint32 m_ClientDataLen;
};