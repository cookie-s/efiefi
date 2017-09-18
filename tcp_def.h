#include "common.h"
#include "ip_def.h"
#include "simple_network_def.h"

typedef struct {
    BOOLEAN UseDefaultAddress;
    EFI_IPv4_ADDRESS StationAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    UINT16 StationPort;
    EFI_IPv4_ADDRESS RemoteAddress;
    UINT16 RemotePort;
    BOOLEAN ActiveFlag;
} EFI_TCP4_ACCESS_POINT;
typedef struct {
    UINT32 ReceiveBufferSize;
    UINT32 SendBufferSize;
    UINT32 MaxSynBackLog;
    UINT32 ConnectionTimeout;
    UINT32 DataRetries;
    UINT32 FinTimeout;
    UINT32 TimeWaitTimeout;
    UINT32 KeepAliveProbes;
    UINT32 KeepAliveTime;
    UINT32 KeepAliveInterval;
    BOOLEAN EnableNagle;
    BOOLEAN EnableTimeStamp;
    BOOLEAN EnableWindowScaling;
    BOOLEAN EnableSelectiveAck;
    BOOLEAN EnablePathMtuDiscovery;
} EFI_TCP4_OPTION;
typedef struct {
    // Receiving Filters
    // I/O parameters
    UINT8 TypeOfService;
    UINT8 TimeToLive;
    // Access Point
    EFI_TCP4_ACCESS_POINT AccessPoint;
    // TCP Control Options
    EFI_TCP4_OPTION * ControlOption;
} EFI_TCP4_CONFIG_DATA;
typedef enum {
    Tcp4StateClosed = 0,
    Tcp4StateListen = 1,
    Tcp4StateSynSent = 2,
    Tcp4StateSynReceived = 3,
    Tcp4StateEstablished = 4,
    Tcp4StateFinWait1 = 5,
    Tcp4StateFinWait2 = 6,
    Tcp4StateClosing = 7,
    Tcp4StateTimeWait = 8,
    Tcp4StateCloseWait = 9,
    Tcp4StateLastAck = 10
} EFI_TCP4_CONNECTION_STATE;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
} EFI_TCP4_COMPLETION_TOKEN;
typedef struct {
    EFI_TCP4_COMPLETION_TOKEN CompletionToken;
} EFI_TCP4_CONNECTION_TOKEN;

typedef struct {
    EFI_TCP4_COMPLETION_TOKEN CompletionToken;
    EFI_HANDLE NewChildHandle;
} EFI_TCP4_LISTEN_TOKEN;

typedef struct {
    UINT32 FragmentLength;
    VOID *FragmentBuffer;
} EFI_TCP4_FRAGMENT_DATA;

typedef struct {
    BOOLEAN UrgentFlag;
    UINT32 DataLength;
    UINT32 FragmentCount;
    EFI_TCP4_FRAGMENT_DATA FragmentTable[1];
} EFI_TCP4_RECEIVE_DATA;

typedef struct {
    BOOLEAN Push;
    BOOLEAN Urgent;
    UINT32 DataLength;
    UINT32 FragmentCount;
    EFI_TCP4_FRAGMENT_DATA FragmentTable[1];
} EFI_TCP4_TRANSMIT_DATA;

typedef struct {
    EFI_TCP4_COMPLETION_TOKEN CompletionToken;
    union {
        EFI_TCP4_RECEIVE_DATA *RxData;
        EFI_TCP4_TRANSMIT_DATA *TxData;
    } Packet;
} EFI_TCP4_IO_TOKEN;

typedef struct {
    EFI_TCP4_COMPLETION_TOKEN CompletionToken;
    BOOLEAN AbortOnClose;
} EFI_TCP4_CLOSE_TOKEN;






struct _EFI_TCP4_PROTOCOL;
typedef EFI_STATUS (EFIAPI *EFI_TCP4_GET_MODE_DATA) (
        IN struct _EFI_TCP4_PROTOCOL *This,
        OUT EFI_TCP4_CONNECTION_STATE *Tcp4State OPTIONAL,
        OUT EFI_TCP4_CONFIG_DATA *Tcp4ConfigData OPTIONAL,
        OUT EFI_IP4_MODE_DATA *Ip4ModeData OPTIONAL,
        OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData OPTIONAL,
        OUT EFI_SIMPLE_NETWORK_MODE *SnpModeData OPTIONAL
        );
typedef EFI_STATUS (EFIAPI *EFI_TCP4_CONFIGURE) (
        IN struct _EFI_TCP4_PROTOCOL *This,
        IN EFI_TCP4_CONFIG_DATA *TcpConfigData OPTIONAL
        );
typedef EFI_STATUS (EFIAPI *EFI_TCP4_ROUTES) (
        IN struct _EFI_TCP4_PROTOCOL *This,
        IN BOOLEAN DeleteRoute,
        IN EFI_IPv4_ADDRESS *SubnetAddress,
        IN EFI_IPv4_ADDRESS *SubnetMask,
        IN EFI_IPv4_ADDRESS *GatewayAddress
        );
typedef EFI_STATUS (EFIAPI *EFI_TCP4_CONNECT) (
        IN struct _EFI_TCP4_PROTOCOL *This,
        IN EFI_TCP4_CONNECTION_TOKEN *ConnectionToken
        );
typedef EFI_STATUS (EFIAPI *EFI_TCP4_ACCEPT) (
        IN struct _EFI_TCP4_PROTOCOL *This,
        IN EFI_TCP4_LISTEN_TOKEN *ListenToken
        );
typedef EFI_STATUS (EFIAPI *EFI_TCP4_TRANSMIT) (
        IN struct _EFI_TCP4_PROTOCOL *This,
        IN EFI_TCP4_IO_TOKEN *Token
        );
typedef EFI_STATUS (EFIAPI *EFI_TCP4_RECEIVE) (
        IN struct _EFI_TCP4_PROTOCOL *This,
        IN EFI_TCP4_IO_TOKEN *Token
        );
typedef EFI_STATUS (EFIAPI *EFI_TCP4_CLOSE)(
        IN struct _EFI_TCP4_PROTOCOL *This,
        IN EFI_TCP4_CLOSE_TOKEN *CloseToken
        );
typedef EFI_STATUS (EFIAPI *EFI_TCP4_CANCEL)(
        IN struct _EFI_TCP4_PROTOCOL *This,
        IN EFI_TCP4_COMPLETION_TOKEN *Token OPTIONAL
        );
typedef EFI_STATUS (EFIAPI *EFI_TCP4_POLL) (
        IN struct _EFI_TCP4_PROTOCOL *This
        );

typedef struct _EFI_TCP4_PROTOCOL {
    EFI_TCP4_GET_MODE_DATA GetModeData;
    EFI_TCP4_CONFIGURE Configure;
    EFI_TCP4_ROUTES Routes;
    EFI_TCP4_CONNECT Connect;
    EFI_TCP4_ACCEPT Accept;
    EFI_TCP4_TRANSMIT Transmit;
    EFI_TCP4_RECEIVE Receive;
    EFI_TCP4_CLOSE Close;
    EFI_TCP4_CANCEL Cancel;
    EFI_TCP4_POLL Poll;
} EFI_TCP4_PROTOCOL;
