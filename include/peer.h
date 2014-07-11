/*
 *
 *  Connection Manager
 *
 *  Copyright (C) 2014  Intel Corporation. All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __CONNMAN_PEER_H
#define __CONNMAN_PEER_H

#ifdef __cplusplus
extern "C" {
#endif

struct connman_peer;

struct connman_peer *connman_peer_create(const char *identifier);
void connman_peer_destroy(struct connman_peer *peer);

const char *connman_peer_get_identifier(struct connman_peer *peer);
void connman_peer_set_name(struct connman_peer *peer, const char *name);
void connman_peer_set_device(struct connman_peer *peer,
				struct connman_device *device);
struct connman_device *connman_peer_get_device(struct connman_peer *peer);

int connman_peer_register(struct connman_peer *peer);
void connman_peer_unregister(struct connman_peer *peer);

struct connman_peer *connman_peer_get(struct connman_device *device,
						const char *identifier);

struct connman_peer_driver {
	int (*connect) (struct connman_peer *peer);
	int (*disconnect) (struct connman_peer *peer);
};

int connman_peer_driver_register(struct connman_peer_driver *driver);
void connman_peer_driver_unregister(struct connman_peer_driver *driver);

#ifdef __cplusplus
}
#endif

#endif /* __CONNMAN_PEER_H */
