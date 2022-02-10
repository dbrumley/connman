#include <assert.h>
#include <stdio.h>

#include "gdhcp/gdhcp.h"

void debug_func(const char *str, gpointer data) {
    fprintf(stderr, "DEBUG: %s\n", str);
}

int main(int argc, char **arv) {
    GDHCPServerError err;
    GMainLoop *main_loop = NULL;
    memset(&err, 0x0, sizeof(err));

    GDHCPServer *server = g_dhcp_server_new(G_DHCP_IPV6, 1, &err);
    assert(server);
    assert(G_DHCP_SERVER_ERROR_NONE == err);

    g_dhcp_server_set_debug(server, &debug_func, NULL);

    int res = g_dhcp_server_set_ip_range(server, "192.168.1.100", "192.168.1.254");
    assert(0 == res);

    res = g_dhcp_server_start(server);
    assert(0 == res);

    main_loop = g_main_loop_new(NULL, FALSE);

    g_main_loop_run(main_loop);

    return 0;
}