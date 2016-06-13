/* net.h */

#define NETSTK		8192 		/* Stack size for network setup */
#define NETPRIO		500    		/* Network startup priority 	*/
#define NETBOOTFILE	128		/* Size of the netboot filename	*/

/* Constants used in the networking code */

#define	ETH_ARP     0x0806		/* Ethernet type for ARP	*/
#define	ETH_IP      0x0800		/* Ethernet type for IP		*/
#define	ETH_IPv6    0x86DD		/* Ethernet type for IPv6	*/
#define ETH_TYPE_A  0x88b5              /* Ethernet type A */
#define ETH_TYPE_B  0x88b6              /*Ethernet type B */


#define	RAD_BCN		0	/* Radio beacon frame	*/
#define	RAD_DATA	1	/* Radio data frame	*/
#define	RAD_ACK		2	/* Radio ack. frame	*/
#define	RAD_MAC		3	/* Radio MAC cmd frame	*/

#define	LP_DISP_IPHC	3	/* IPHC dispatch	*/
#define	LP_DISP_FRAG1	0x18	/* Frag1 dispatch	*/
#define	LP_DISP_FRAGN	0x1C	/* FragN dispatch	*/
#define	LP_DISP_IP	0x41	/* Uncompr. IP dispatch	*/

#pragma pack(1)
struct	lp_iphc {
	byte	iphc_hl:2;	/* IPHC hop limit	*/
	byte	iphc_nh:1;	/* IPHC next hdr. comp.	*/
	byte	iphc_tf:2;	/* IPHC TC FL		*/
	byte	iphc_disp:3;	/* IPHC dispatch	*/
	byte	iphc_dam:2;	/* IPHC Dst. Addr. Mode	*/
	byte	iphc_dac:1;	/* IPHC Stateful dst.	*/
	byte	iphc_m:1;	/* IPHC multicast dst.	*/
	byte	iphc_sam:2;	/* IPHC Src. Addr. Mode	*/
	byte	iphc_sac:1;	/* IPHC stateful src.	*/
	byte	iphc_cid:1;	/* IPHC Context ID	*/
};
#pragma pack()

#pragma pack(1)
struct	lp_frag1 {
	union {
	 struct {
	  uint32	frag1_dtag:16;	/* Datagram tag		*/
	  uint32	frag1_dsize:11;	/* Datagram size	*/
	  uint32	frag1_disp:5;	/* Frag1 dispatch	*/
	 };
	 uint32	frag1;
	};
};

struct	lp_fragn {
	union {
	 struct {
	  uint32	fragn_dtag:16;	/* Datagram tag		*/
	  uint32	fragn_dsize:11;	/* Datagram size	*/
	  uint32	fragn_disp:5;	/* FragN dispatch	*/
	 };
	 uint32	fragn;
	};
	byte	fragn_doff;	/* Datagram offset	*/
};
#pragma pack()

/* Format of an IEEE 802.15.4 packet carrying IPv6 */

#pragma pack(1)
struct	netpacket_r {
	uint16	net_radftype:3;	/* Radio frame type	*/
	uint16	net_radsec:1;	/* Secutiry enabled	*/
	uint16	net_radfp:1;	/* Frame pending	*/
	uint16	net_radar:1;	/* Acknowledgement req	*/
	uint16	net_radpidc:1;	/* PAN ID compression	*/
	uint16	net_radres:1;	/* Reserved		*/
	uint16	net_radseqsup:1;/* Seq. num. suppression*/
	uint16	net_radie:1;	/* IE list present	*/
	uint16	net_raddam:2;	/* Dst. Addres Mode	*/
	uint16	net_radfver:2;	/* Radio frame version	*/
	uint16	net_radsam:2;	/* Src. Address Mode	*/
	byte	net_radseq;	/* Sequence number	*/
	byte	net_raddstpan[2];/* Dst PAN ID		*/
	byte	net_raddst[8];	/* Radio dst. address	*/
	byte	net_radsrcpan[2];/* Src. PAN ID		*/
	byte	net_radsrc[8];	/* Radio src. address	*/
	union {
	 byte	net_raddata[1280-23];	/* Radio data		*/
	 struct { /* Uncompressed IPv6 header */
	  byte		net_lpdisp;	/* IP dispatch		*/
	  byte		net_ipvtch;	/* IP ver, TC high	*/
	  byte		net_iptclflh;	/* IP TC low, FL high	*/
	  uint16	net_ipfll;	/* IP FL flow		*/
	  uint16	net_iplen;	/* IP payload length	*/
	  byte		net_ipnh;	/* IP next header	*/
	  byte		net_iphl;	/* IP hop limit		*/
	  byte		net_ipsrc[16];	/* IP src. address	*/
	  byte		net_ipdst[16];	/* IP dst. address	*/
	  byte		net_ipdata[];	/* IP data		*/
	 };
	 struct {
	  struct lp_frag1	net_lpfrag1;
	  struct lp_iphc	net_f1iphc;
	  byte	 f1data[];
	 };
	 struct {
	  struct lp_fragn	net_lpfragn;
	  struct lp_iphc	net_f2iphc;
	  byte	 fndata[];
	 };
	 struct {
	  struct lp_iphc	net_iphc;
	  byte	 iphcdata[];
	 };
	};
};
#pragma pack()

/* Format of an Ethernet packet carrying IPv4 and UDP */

#pragma pack(2)
struct	netpacket	{
	byte	net_ethdst[ETH_ADDR_LEN];/* Ethernet dest. MAC address	*/
	byte	net_ethsrc[ETH_ADDR_LEN];/* Ethernet source MAC address	*/
	uint16	net_ethtype;		/* Ethernet type field		*/
	byte	net_ipvh;		/* IP version and hdr length	*/
	byte	net_iptos;		/* IP type of service		*/
	uint16	net_iplen;		/* IP total packet length	*/
	uint16	net_ipid;		/* IP datagram ID		*/
	uint16	net_ipfrag;		/* IP flags & fragment offset	*/
	byte	net_ipttl;		/* IP time-to-live		*/
	byte	net_ipproto;		/* IP protocol (actually type)	*/
	uint16	net_ipcksum;		/* IP checksum			*/
	uint32	net_ipsrc;		/* IP source address		*/
	uint32	net_ipdst;		/* IP destination address	*/
	union {
	 struct {
	  uint16 	net_udpsport;	/* UDP source protocol port	*/
	  uint16	net_udpdport;	/* UDP destination protocol port*/
	  uint16	net_udplen;	/* UDP total length		*/
	  uint16	net_udpcksum;	/* UDP checksum			*/
	  byte		net_udpdata[1500-28];/* UDP payload (1500-above)*/
	 };
	 struct {
	  byte		net_ictype;	/* ICMP message type		*/
	  byte		net_iccode;	/* ICMP code field (0 for ping)	*/
	  uint16	net_iccksum;	/* ICMP message checksum	*/
	  uint16	net_icident; 	/* ICMP identifier		*/
	  uint16	net_icseq;	/* ICMP sequence number		*/
	  byte		net_icdata[1500-28];/* ICMP payload (1500-above)*/
	 };
	};
};
#pragma pack()

#define	PACKLEN	sizeof(struct netpacket)

extern	bpid32	netbufpool;		/* ID of net packet buffer pool	*/

struct	network	{
	uint32	ipucast;
	uint32	ipbcast;
	uint32	ipmask;
	uint32	ipprefix;
	uint32	iprouter;
	uint32	bootserver;
	bool8	ipvalid;
	byte	ethucast[ETH_ADDR_LEN];
	byte	ethbcast[ETH_ADDR_LEN];
	char	bootfile[NETBOOTFILE];
};

extern	struct	network NetData;	/* Local Network Interface	*/
