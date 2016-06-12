/*
 * udp.h
 *
 *  Created on: 5 cze 2016
 *      Author: maly_windows
 */

#ifndef UDP_H_
#define UDP_H_

#include <errno.h>
#include <unistd.h>

#ifdef __WIN32__

# include <winsock2.h>
# include <ws2tcpip.h>
#else
# include <sys/socket.h>
# include <sys/uio.h>
# include <netdb.h>
# include <netinet/in.h>
#endif

#endif /* UDP_H_ */
