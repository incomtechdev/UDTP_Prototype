#ifndef __IP17__
#define __IP17__

#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

typedef unsigned int uint32;
typedef unsigned long uint64;

#define IPPROTO_IP17 10



typedef struct udtp_Connection UDTP_CONNECTION;
struct udtp_workingtread;

struct NetID{


};


//��������� IP ������� ������ 4 
struct ip_header_v4 {
	/** ������ 4 ���� vhl - ��� ������. ��� IPv4 �������� ���� ������ ���� ����� 4.
	 *	������ 4 ���� vhl - ��� IHL. IHL � (Internet Header Length) ����� ��������� IP-������ � 32-������ ������ (dword). 
	 *	������ ��� ���� ��������� �� ������ ����� ������ � ������. ����������� ���������� �������� ��� ����� ���� ����� 5.
	*/
	unsigned char   vhl;
		#define IP_V  (ip)  (((ip) -> vhl & 0xf0) >> 4)
		#define IP_HL (ip)  ((ip) -> vhl & 0x0f)

	/**��� ������������ (Type of Service, ������� TOS) � ����, ���������� ����� ���������, ������������ ��� ������������ IP-�������.
	*	�������� ����� ������������ ������� :
	*		0 - 2 � ���������(precedence) ������� IP - ��������
	*	3 � ���������� �� ������� ��������(delay) �������� IP - ��������(0 � ����������, 1 � ������ ��������)
	*	4 � ���������� � ���������� �����������(throughput) ��������, �� �������� ������ ������������ IP - �������(0 � ������, 1 � ������� ���������� �����������)
	*	5 � ���������� � ����������(reliability) �������� IP - ��������(0 � ����������, 1 � ������� ����������)
	*	6 - 7 � ECN � ����� ��������� � ��������(���������� IP - �������).
	*/
	unsigned char  type_of_service;

	//.����� ������ - ����� ������ � �������, ������� ��������� � ������. ����������� ���������� �������� ��� ����� ���� ����� 20, ������������ 65535.
	unsigned short total_length;

	/** ������������� � ��������, ����������� ������������ ������ � ���������������
	*	��� ����������� ���������� ������������������ ���������� ��� ������ ������.
	*	��� ������������������ ������ ��� ��������� ����� ���������� �������������.
	*/
	unsigned short id;

	//3 ���� ������. ������ ��� ������ ���� ������ ����� ����, 
	//������ ��� DF (don�t fragment) ���������� ����������� ������������ ������ � 
	//������ ��� MF (more fragments) ����������, �� �������� �� ���� ����� ��������� � ������� �������.
	//���������� 13 ��� �������� ���������.
	//�������� ��������� � ��������, ������������ ������� ��������� � ������ ������.
	//�������� �������� ����������� ������ �������� ������, ������� ��� �������� ������� ��������� �� 8 ��� �������� � �����.
	unsigned short frame_offset;
		#define IP_DF (ip)  ((ip) -> frame_offset & 0x4000)        /* dont fragment flag */
		#define IP_MF (ip)  ((ip) -> frame_offset & 0x2000)        /* more fragments flag */
		#define IP_OFFMASK (ip)  ((ip) -> frame_offset & 0x1fff)   /* mask for fragmenting bits */

	//������������ ����, ����������� ��������� IP-������� ����� ���� ����������� ������ ������� ����� IP-�������� � ����. 
	//RFC 791 ������������� � �������� ���� ������ ������� � �������, ����� ������ ���������� ���� ����, 
	//����� ������� �������� IP-�������, �������� ���������� ����� ���� �� ������� ���� �� 1 
	//(���� ��� �������, ��� ��������� �������� �� ����� ���� ������ ������ ����� �������). 
	//����� �������, �� ��������, ����� ����� (TTL - Time To Live) - ��� ������������ ���������� �����,
	//������� ����� ������ �� ������ ����������� IP-�������.
	//������ IP - ������ �� ����� ���� ���� ������ ���������� IP - ��������, 
	//��� ������� ���� "����� �����" ����� ������ ����.���� ��������������� ��������� � ���� IP - ���������, 
	//"����������" �� ��� ����������� �����.��� ���� ���� - ��������� ������������� IP - �������� ���������� ICMP - �������, ���������� �� ���� �������.
	//� UNIX - �����������, ��� �������, ��� ���� ����������� ���������� IP - �������� ������ �� ��������� 15...30.
	unsigned char  time_to_live;

	//���������
	//���� �������� � ����, ���������� ������������� ��������� ����� ��������(������, �������������) ������, ��� �������� ������������� ������ IP - ��������.���� ��������� �������������� ��� ���� ����������.
	//		-------- + ------------ - +------------------------------------------
	//		������ - : ����������� : ��� ���������
	//		 ������� : �������� :
	//		-------- + ------------ - +------------------------------------------
	//		  1        ICMP					���������� �������� ����������� ���������
	//		  2        IGMP					���������� �������� ���������� ����������
	//		  3        GGP					�������� "����-����"
	//		  6        TCP					�������� ���������� ���������
	//		  8        EGP					�������� "�������" ������
	//		  17       UDP					�������� ���������� ������������
	//		  27       RDP					�������� �������� ������
	//		  28       IRTP					�������� ���������� �������� ��������
	//		  29       ISO TP4				������������ �������� ISO 4 ������
	//		  80       ISO IP				���������� �������� ISO
	//		  89       OSPF					�������� "���������� ���� ������"
	//		------ - +------------- - +------------------------------------------
	unsigned char  protocol;
			#define ICMP (pr)  ((rp) -> protocol & 0x1)
			#define IGMP (pr)  ((rp) -> protocol & 0x2)
			#define GGP (pr)  ((rp) -> protocol & 0x3)
			#define TCP (pr)  ((rp) -> protocol & 0x6)
			#define EGP (pr)  ((rp) -> protocol & 0x8)
			#define UDP (pr)  ((rp) -> protocol & 0x11)
			#define RDP (pr)  ((rp) -> protocol & 0x1b)
			#define IRTP (pr)  ((rp) -> protocol & 0x1c)
			#define ISO_TP4 (pr)  ((rp) -> protocol & 0x1d)
			#define ISO_IP (pr)  ((rp) -> protocol & 0x50)
			#define OSPF (pr)  ((rp) -> protocol & 0x59)

	//����������� ����� ���������
	//������������ ����, ���������� ����������� ����� ��������� IP - ��������
	//(�������� ��������, ��� ��� ������ IP - �������� ����������� ����� �� ��������������;
	//�������������� ������ - ������ ���������� ������������� ������).
	//��������� ��������� IP - �������� �������� ���� "����� �����", ���������� ���� �������� � ������ ����, 
	//����� ������� ������� IP - �������, �� ��� ���������� ����������� ����� ������ �������������� �����������(�, �������������, ������� ��������).
	//�� ���� ����������, �������� � ����������� TCP / IP, ������������ ��� ���������� Internet - ����������� �����, 
	//������� ������������ ����� ���������� 16 - ������ ����� ���� 16 - ������ ���� �������������� ����������.
	unsigned short checksum;

	struct  in_addr source_address, dest_address;
};

//��������� IP ������� ������ 6 
struct ip_header_v6 {
	// ������ 4 ���� vtf -	��� ������. ��� IPv4 �������� ���� ������ ���� ����� 6.
	// ��������� 8 ��� vtf - Traffic Class ��� ��������� � ������������ ��� ����, ����� ��������� ������ � ������� ������������ � �������� � �������� �������.
	//						��������� ������ (8 ���). ��� ���� ������� �� ���� ��������. 
	//						������� 6 ��� ������������ DSCP ��� ������������� �������. ���������� ��� ���� ������������ ECN ��� �������� ����������.
	// ���������� 20 ��� -	Flow Label ��� ����� ������.����� � ��� ������������������ �������, ���������� ������������ ������������ ��������. 
	//						��� ���� ��������������, ��� ��� ������ ������� ������ ������ ���� ����������� ����������� ���������. 
	//						�������� ������ ��������� ������� ��������������� �����������. ����� ������ ������������� �����-������������ ���� ��������� ���������������� 20-������� �����.
	unsigned int   vtf;
		#define IP_V  (ip)  (((ip) -> vtf & 0xf0 00 00 00) >> 28)
		#define IP_TC (ip)  (((ip) -> vtf & 0xf 00 00 00) >> 20)
		#define IP_TC (ip)  ((ip) -> vtf & 0xfffff)

	//������ 16 ��� pnh - Payload Length, � ������� �� ���� Total Length � ��������� IPv4 ������ ���� �� �������� ������������� ��������� ������ (16 ���).
	//��������� 8 ��� pnh - Next Header,Next Header: ����� ��� ������������ ��������� (����. IPv6 extension), 
	//						������� ��� ���������. � ��������� ����������� ��������� ���� Next Header ����� ��� ������������� ��������� (TCP, UDP � �. �.)
	//���������� 8 ��� pnh - Hop Limit: ������ ���� time to live � IPv4 (8 ���).
	unsigned int   pnh;

	char source_address[128];
	char dest_address[128];

};


typedef struct udtp_header{

	//�������� 2-� ���� �� �����
	//Type[3..0] � ��� ���������;
	//Conn[4..5](Connection) � ��� ���������� :
	//			0 � ��������(������� ������);
	//			1 � ���������������(������� ��������� ������);
	//			2 � �����������(�������� ������ ��������);
	//			3 � ���������(�������� ������ � ���������).
	//�([6]Acknowledgment) � �����, ��������� �������� 0 / 1:
	//			0 � �����;
	//			1 � �������������.
	//D[7](Delay) � ���������� ���������, ��������� �������� 0 / 1:
	//			0 � �����������(�������� �� �������� � ���������);
	//			1 ��  �������� ������� �����(�������� � ��������� �������).
	//Command[8..11] � ����� �������, ������� �� ���� ��������� :
	//			0 - 	�����;
	//			1 - ������� �����;
	//			2 - ������� �����;
	//			3 - ������������ �����;
	//			4 - ��������� �����;
	//			5 - ���������� ����������;
	//			6 - ���������� ����������;
	//			7 - 15 � ���������������;
	//Connection[12..15] � ����� ����������.�������� udtp ������������� ����������� �������� �� 16 ���������� ������������.
	//AuthenticationID[16..31] - ���������������� 2 ����� ��� Authentication ID
	unsigned int control;

	//����������� ���� �Size� 64 ����. 
	//������������ �������� ���� �Size� : 18 446 744 073 709 551 615 ���(2 ^ 64 � 1) ����.
	//���� �Size� ����������:
	//	� ������ �������� �������� - ������ �����
	//	� ������ ��������� �������� - ��������� ������������ ��������.
	//	� ������ �������� �������� - ���������� ������ ������.
	//	� ������ �������� ������ - ������ �������� �������.
	long long size;

	//����������� ���� �Global Label Flow� 64 ����. 
	//������������ �������� ���� �Global Label Flow� : 18 446 744 073 709 551 615 ���(2 ^ 64 � 1).
	//���� �Global Label Flow� ���������� ���������� ����� ������ ��������. ����������� �� �����:
	//	�	Area Address destination(Autonomous System(AS)
	//	�	Area Address source(Autonomous System(AS) | |
	//	�	Destination(Address[7..0] | Name(127..0) | Alias(115..0)
	//	�	Source(Address[7..0] | Name(127..0) | Alias(115..0)
	long long gfl;

	//Protocol [0..15] - ���� �Protocol� ���������� ����� ��������� � ������������ � rfc1700.
	//Bit Rate [16..31] - BitRate � �������, ����������� �������� �������� �������� � ��������� ������������ ���������� ��������� � ��������� ��������. 
	unsigned int pbr;
		#define Protocol(pr) (((pr) -> pbr & 0xff ff 00 00) >> 16)
		#define BitRate(pr) (((pr) -> pbr & 0xff ff ))
	//����������� �����
	//����������� ��� CRC-32 ������������ ����������� �������� ������ ������.
	//32 - ������� ����, ���������� CRC - ����������� �����, ������������ ��� ����� �����.
	//����������� ����� Ethernet - ����� ���������� 64 �����(512 ���).
	//����� ����������� ������� � ���, ��� �������� ������������ ��������� ������ � Ethernet - ����
	//�������� ��������� CSMA / CD ����������� �� ��������� ������� � 47 �����������.
	//�� ��� ����� �������������� �������� 470 ���(��� �������� 10 ������� � �������), ��� ��� 512 - ��� ���������� 470 �� �����, ����������� �������� 2.
	//� ���������, ����� ����� ������, ������������ � ���� �����, ������������ ��� ������������
	//����� ������ �� ����� 64 ������, ������� Ethernet - ����������� ������������ ��������� ���� ������ �� ����������� �����.
	//	����������.���������, ��� �������� ��������� IEEE 802.3 ������������� ���� 16 - ������� ���� ���� �����
	//	�� ����� ���� �������� ����� �����(� ������) ���� Ethernet - �����.
	//	��� ������������� ���� ����������� ���� ����� ������������ ������������ ����������� �������� LLC
	//	(Logic Link Control - �������� ���������� ���������� ������), ���������� ������������� ��������� ����� Ethernet � ������������ �����������.
	//	������ �������� LLC � ����� UNIX(�, ������, � � ����������� ������ ��) ���������� �� ��� : ���������� "de facto" �������� ������������ RFC 894. 
	//	���� ���� ��������, ��� ����� �������� ��������������� ���� �����(0x0800 � ������) 
	//	�� ��������� ����������� ������������� ����� ���� ������������ � ��� ������������� ����, � ��� �������� ����� ���� �����(�������� 1500).
	unsigned int crc;

} UDTP_Header, PUDTP_Header;

typedef struct TreadParams {
	PUDTP_Header	*pheader;
	PUDTP_Header	*pudtp_header;
} structTreadParams, *pstructTreadParams;

enum TreadType{
	data = 0,
	error,
	control,
	status
};

enum MODE{
	file = 0,
	stream,
	message,
	command
};

typedef uint32 BIT;
typedef uint32 FEC;
typedef uint32 SEC;
typedef uint32 BR;
typedef uint32 EVENT;
typedef uint32 ERR;

typedef struct udtp_workingtread{
	HANDLE WINAPI handle;
	unsigned short type;
	SOCKET assinedSck;
} UDTP_WTREAD, *PUDTP_WTREAD;

typedef struct udtp_Channel{
	NetID  netID;
	UDTP_CONNECTION* listConn[16];
	sockaddr_in addr;
	uint32 activeConn;
} UDTP_CHANEL, *PUDTP_CHANEL;

typedef struct udtp_Connection{
	PUDTP_CHANEL parent_Ch;
	UDTP_Header  header;
	PUDTP_WTREAD wt[4];
} UDTP_CONNECTION, *PUDTP_CONNECTION;

//�������� udtp � ������ ���������� ���������� Socket-raw ��� ����������, �������������� �� ��������� �������:
/** ������� ���������� ������� �����������;
*/
/**
������ �������� �������� ��������; */
uint32 udtp_BitRate(PUDTP_CONNECTION *conn);			//������ �������� �������� ��������;
uint32 udtp_Delay(PUDTP_CONNECTION *conn);			//������ ��� �������� �������� ��������;
uint32 udtp_ControlBitRate(PUDTP_CONNECTION *conn);	//�������� �������� ��������;
//���������� ������� ���������������;
	//** ���� �� ������������ � �� ����������
	int udtp_NetID_Init();		//��������� NetID �� ������� ����������;
	int udtp_NetID_Del();		//������� NetID � �������� ����������;
	int udtp_NetID_Authen();	//����������� ������������� NetID;
	int udtp_NetID_Acct();		//������ NetID ����������;
	int udtp_NetID_Contact();	//���������� � NetID ����������;
//���������� ��������� ������;
	uint32 udtp_Chanel(UDTP_CHANEL *ch, sockaddr_in addr);	//������� ����� �����;
	//uint32 udtp_Open(UDTP_CHANEL *ch);	//������� �����;
	//uint32 udtp_Take(UDTP_CHANEL *ch);	//������� �����;
	uint32 udtp_ShutChanel(UDTP_CHANEL *ch);	//������� �����;
	//uint32 udtp_Restore(UDTP_CHANEL *ch);	//������������ �����;
	uint32 udtp_Connect(UDTP_CHANEL *ch);	//���������� ����������;
	uint32 udtp_Accept(UDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//������� ����������;
	uint32 udtp_Close(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//���������� ����������;
	uint32 udtp_Send(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//�������� ������ �� ����������;
	uint32 udtp_Receive(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//������� ������ �� ����������;
	uint32 udtp_Repeat(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//��������� ������ �� ����������;
	uint32 udtp_Crypto(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//�������� / ��������� ���������� ������������ ������;
	uint32 udtp_FecDec(PUDTP_CHANEL *ch, PUDTP_CONNECTION *conn);	//�������� / ��������� �������������� ����������� ������.


#endif
