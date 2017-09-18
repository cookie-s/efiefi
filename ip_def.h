#include "common.h"

typedef struct {
    UINT8 Addr[4];
} EFI_IPv4_ADDRESS;
typedef struct {
    UINT8 Addr[16];
} EFI_IPv6_ADDRESS;

typedef struct {
    UINT8 DefaultProtocol;
    BOOLEAN AcceptAnyProtocol;
    BOOLEAN AcceptIcmpErrors;
    BOOLEAN AcceptBroadcast;
    BOOLEAN AcceptPromiscuous;
    BOOLEAN UseDefaultAddress;
    EFI_IPv4_ADDRESS StationAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    UINT8 TypeOfService;
    UINT8 TimeToLive;
    BOOLEAN DoNotFragment;
    BOOLEAN RawData;
    UINT32 ReceiveTimeout;
    UINT32 TransmitTimeout;
} EFI_IP4_CONFIG_DATA;

typedef struct {
    EFI_IPv4_ADDRESS SubnetAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    EFI_IPv4_ADDRESS GatewayAddress;
} EFI_IP4_ROUTE_TABLE;

typedef struct {
    UINT8 Type;
    UINT8 Code;
} EFI_IP4_ICMP_TYPE;

typedef struct {
    BOOLEAN IsStarted;
    UINT32 MaxPacketSize;
    EFI_IP4_CONFIG_DATA ConfigData;
    BOOLEAN IsConfigured;
    UINT32 GroupCount;
    EFI_IPv4_ADDRESS *GroupTable;
    UINT32 RouteCount;
    EFI_IP4_ROUTE_TABLE *RouteTable;
    UINT32 IcmpTypeCount;
    EFI_IP4_ICMP_TYPE *IcmpTypeList;
} EFI_IP4_MODE_DATA;
