/* net.c - net_init, netin */

#include <xinu.h>

bpid32	netbufpool;
int32	beserver;

/*------------------------------------------------------------------------
 * net_init  -  Initialize the network
 *------------------------------------------------------------------------
 */
void	net_init (void)
{
	char	procname[50];	/* Netin process name	*/
	int32	iface;		/* Interface number	*/
	char	buf[10] = {0};

	/* Initialize the interfaces */

	netiface_init();

	/* Create the network buffer pool */

	netbufpool = mkbufpool(PACKLEN, 20);
	if((int32)netbufpool == SYSERR) {
		panic("Cannot create network buffer pool\n");
	}

	while(TRUE) {
		kprintf("Enter the backend number of the server: ");
		memset(buf, 0, 10);
		read(CONSOLE, buf, 10);
		beserver = atoi(buf);
		if((beserver < 101) || (beserver > 196)) {
			kprintf("Invalid backend number, must be in range [101,196]\n");
			continue;
		}
		beserver -= 101;
		break;
	}

	/* Create a netin process for each interface */

	for(iface = 0; iface < NIFACES; iface++) {

		if(if_tab[iface].if_state == IF_DOWN) {
			continue;
		}

		sprintf(procname, "netin_%d", iface);
		resume(create(netin, NETSTK, NETPRIO, procname, 1, iface));

		nd_init(iface);
	}
}

/*------------------------------------------------------------------------
 * netin  -  Network input process
 *------------------------------------------------------------------------
 */
process	netin (
	int32	iface
	)
{
	struct	ifentry *ifptr;	/* Pointer to interface	*/
	struct	netpacket *pkt;	/* Pointer to packet	*/

	if((iface < 0) || (iface > NIFACES)) {
		return SYSERR;
	}

	ifptr = &if_tab[iface];

	while(TRUE) {

		pkt = (struct netpacket *)getbuf(netbufpool);
		if((int32)pkt == SYSERR) {
			panic("netin cannot get buffer for packet\n");
		}

		read(RADIO, (char *)pkt, PACKLEN);

		if((pkt->net_ipvtch&0xf0) == 0x60) {
			kprintf("netin: incoming ipv6 packet\n");
			pkt->net_iface = iface;
			ip_in(pkt);
			//freebuf((char *)pkt);
		}
		else {
			freebuf((char *)pkt);
		}
	}

	return OK;
}
