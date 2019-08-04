// dh.c Panagiotis (Peter) Goulas Student ID: 886001

/* A simple client program for server.c

   To compile: gcc client.c -o client

   To run: start the server, then the client */





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>


#define G         15
#define P         97

#define SHA        "(dh.c)= "

// function prototypes

int power(int x, unsigned int y, int p);

int main(int argc, char ** argv)
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent * server;

    char buffer[256];

    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);


    /* Translate host name into peer's IP address ;
     * This is name translation service by the operating system
     */
    server = gethostbyname(argv[1]);

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    /* Building data structures for socket */

    bzero((char *)&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy(server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(portno);

    /* Create TCP socket -- active open
    * Preliminary steps: Setup: creation of active open socket
    */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(0);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR connecting");
        exit(0);
    }

    /* Do processing
    */

    // SEND USERNAME

    printf("Enter Username Please: ");



    bzero(buffer, 256);

    strcpy(buffer, "pgoulas\n");

    

    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(0);
    }


    // send gmod value
    bzero(buffer, 256);

    int answer = 0;

    // https://www.tutorialspoint.com/c_standard_library/c_function_fopen.htm
    FILE* fp = popen("openssl sha256 dh.c", "r");

    char string1[32] = {'\0'};
    // char string2[32];

    
    fread(string1, 1, 32, fp);

    printf("\nstring1=%s\n", string1);

    // strcpy(string2, string1);

    char *array1 = malloc(2 * sizeof(char *)); 

    array1 = strstr(string1, SHA) + 8;

    strncpy(buffer, array1, 2);

    printf("\n%s\n", buffer);

    int b = 0; 


    //  https://www.techonthenet.com/c_language/standard_library_functions/stdlib_h/strtoll.php
    b =(int)strtol(buffer, NULL, 16);


    answer = power(G,b,P);

    sprintf(buffer, "%d\n", answer);


    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(0);
    }



    
    // RECEIVE 

    bzero(buffer, 256);

    n = read(sockfd, buffer, 255);

    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(0);
    }

    printf("%s\n", buffer);


    // send value again

    int data_g = 0;

    data_g= strtol(buffer, NULL, 10);

    printf("%d\n", data_g);

    int answer2 = 0;
    answer2 = power(data_g, b, 97);

    sprintf(buffer, "%d\n", answer2);

    // write into socket

    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(0);
    }


    bzero(buffer, 256);

    n = read(sockfd, buffer, 255);

    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(0);
    }

    printf("%s\n", buffer);





    return 0;
}

// https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
/* Iterative Function to calculate (x^y)%p in O(log y) */
int power(int g, unsigned int b, int p) 
{ 
    int res = 1;      // Initialize result 
  
    g = g % p;  // Update x if it is more than or  
                // equal to p 
  
    while (b > 0) 
    { 
        // If y is odd, multiply x with result 
        if (b & 1) 
            res = (res*g) % p; 
  
        // y must be even now 
        b = b>>1; // y = y/2 
        g = (g*g) % p;   
    } 
    return res; 
} 