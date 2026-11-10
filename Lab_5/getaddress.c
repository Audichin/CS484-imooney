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

    struct sockaddr_in v4;
    struct sockaddr_in6 v6;

    struct addrinfo hints, *res, *p;
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC; // allows for both IPv4 and IPv6 addresses

    int stat = getaddrinfo(argv[1], // hostname, this comes from the command line
                       NULL, // service name, this is NULL because we are not specifying a service
                       &hints, // hints, this is a pointer to a struct addrinfo that contains hints about the type of socket we want
                       &res); // result, this is a pointer to a linked list of addrinfo structures that will be filled with the results

    if (stat != 0)
    {
        printf("[ERR] --> getaddrinfo:", gai_strerror(stat));
        return 1;
    }

    printf("Address info requested for %s \n", argv[1]);
    printf("----------------------------------------\n");


    for (p = res; p  != NULL; p -> ai_next) // Need to iterate though both IPV4 and V6 addresses from the linked list obtained
    {                                       // p is a pointer to a struct addrinfo, which contains information about the address
        if(p == AF_INET) // starting with IPv4 addresses 
        {
            printf("IPV4: ");

        }
        else if (p == AF_INET6) // next with IPv6 addresses
        {
            printf("IPV6: ");
        }
    }

}