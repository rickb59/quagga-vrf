/*
 * Interface looking up by netlink.
 * Copyright (C) 1998 Kunihiro Ishiguro
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.  
 */

#include <zebra.h>

#include "zebra/zserv.h"
#include "ioctl.h"



extern int interface_lookup_netlink (void);


/* Interface information read by netlink. */
void
interface_list (void)
{
  interface_lookup_netlink ();  
}

int if_set_vlan(struct interface *ifp, int id)
{
	return kernel_vlan_set (ifp, id);
}


int if_set_vrf(struct interface *ifp, int id)
{
	return kernel_vrf_set (ifp, id);
}


/* set interface MTU */
void
if_set_mtu (struct interface *ifp, unsigned int mtu)
{
	mtu = kernel_set_link_mtu(ifp, mtu);
}


/* Set interface flags */
int
if_set_flags (struct interface *ifp, uint64_t flags)
{
  int ret;
  struct ifreq ifreq;

  kernel_link_set_flags(ifp,flags);

}
/* Unset interface's flag. */
int
if_unset_flags (struct interface *ifp, uint64_t flags)
{

	 kernel_link_unset_flags(ifp, flags);
}

#if 0
int
if_set_prefix (struct interface *ifp, struct connected *ifc)
{
  return kernel_address_add_ipv4 (ifp, ifc);
}

/* Interface address is removed using netlink interface. */
int
if_unset_prefix (struct interface *ifp, struct connected *ifc)
{
  return kernel_address_delete_ipv4 (ifp, ifc);
}

#ifdef HAVE_IPV6
/* Interface's address add/delete functions. */
int
if_prefix_add_ipv6 (struct interface *ifp, struct connected *ifc)
{

}

if_prefix_delete_ipv6 (struct interface *ifp, struct connected *ifc)
{

}
#endif /* HAVE_IPV6 */




int
if_get_index (struct interface *ifp)
{

	int ifindex;

	ifindex = 0;
    /* Linux 2.0.X does not have interface index. */
    ifp->ifindex = ifindex;
    return ifp->ifindex;
}

int
if_get_hwaddr (struct interface *ifp)
{
	int ret;
	int i;

	ret = netlink_get_hwaddr(ifp);
	  if (ret < 0)
	    ifp->hw_addr_len = 0;
	  else
	    {
//	      memcpy (ifp->hw_addr, ifreq.ifr_hwaddr.sa_data, 6);

	      for (i = 0; i < 6; i++)
		if (ifp->hw_addr[i] != 0)
		  break;

	      if (i == 6)
		ifp->hw_addr_len = 0;
	      else
		ifp->hw_addr_len = 6;
	    }
	  return 0;
}


static int
if_getaddrs (void)
{
	return 0;
}

interface_info_netlink ()
{

}

int
if_get_addr (struct interface *ifp)
{
  int ret;

}
#endif
