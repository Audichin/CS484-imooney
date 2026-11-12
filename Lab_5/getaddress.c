#define _POSIX_C_SOURCE 200112L
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 2) 
    {
        printf("[ERR] --> argc: must have a hostname as an argument\n");
        return 1;
    }

    struct sockaddr_in *v4; // needs to be a pointer because it will be used to point to the address of the struct sockaddr_in
    struct sockaddr_in6 *v6; // same as v4 but for IPv6
    struct addrinfo hints, *res, *i, *addr;
    char ip_str[INET6_ADDRSTRLEN]; // Large enough for IPv6

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC; // allows for both IPv4 and IPv6 addresses

    int stat = getaddrinfo(argv[1], // hostname, this comes from the command line
                       NULL, // service name, this is NULL because we are not specifying a service
                       &hints, // hints, this is a pointer to a struct addrinfo that contains hints about the type of socket we want
                       &res); // result, this is a pointer to a linked list of addrinfo structures that will be filled with the results
    
    /* Example of the addrinfo data:
    struct addrinfo 
    {
        int ai_flags;              Options:
        int ai_family;             AF_INET, AF_INET6, etc.
        int ai_socktype;           SOCK_STREAM, SOCK_DGRAM, etc.
        int ai_protocol;           Protocol number
        socklen_t ai_addrlen;      Length of ai_addr
        struct sockaddr *ai_addr;  IP address <-- WE NEED THIS DATA
        char *ai_canonname;        Canonical hostname
        struct addrinfo *ai_next;  Next in list
    };
    */

    /*Example of the sockaddr_in data, sockaddr_in6 looks the same:
    struct sockaddr_in 
    {
        sa_family_t sin_family;
        in_port_t sin_port;
        struct in_addr sin_addr; <-- WE NEED THIS DATA
    };
    */

    if (stat != 0)
    {
        printf("[ERR] --> getaddrinfo: %s\n", gai_strerror(stat)); // gives associated error if getaddrinfo fails for any reason
        return 1;
    }

    printf("Address info for %s \n", argv[1]);
    printf("----------------------------------------\n");


    for (i = res; i != NULL; i = i -> ai_next) // Need to iterate though both IPV4 and V6 addresses from the linked list obtained
    {                                           // p is a pointer to a struct addrinfo, which contains information about the address
        if(i->ai_family == AF_INET) // starting with IPv4 addresses 
        {
            v4 = (struct sockaddr_in *)i->ai_addr; // Becuse i is a pointer, we need to dereference it and access the ai_addr
            addr = &v4->sin_addr; // get the address from the struct sockaddr_in
            printf("[IPV4] --> %s\n", inet_ntop(AF_INET, addr, ip_str, sizeof(ip_str))); // convert the address to a string and print it
        }
        else if (i->ai_family == AF_INET6) // next with IPv6 addresses
        {
            v6 = (struct sockaddr_in6 *)i->ai_addr; // same as v4 but for IPv6
            addr = &v6->sin6_addr; // get the address from the struct sockaddr_in6
            printf("{IPV6} --> %s\n", inet_ntop(AF_INET6, addr, ip_str, sizeof(ip_str))); // convert the address to a string and print it
        }
    }
    freeaddrinfo(res); // make sure to free at the end!
    return 0;
}