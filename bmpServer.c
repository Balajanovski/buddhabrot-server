/*
 *  bmpServer.c
 *  1917 serve that 3x3 bmp from lab3 Image activity
 *
 *  Created by Tim Lambert on 02/04/12.
 *  Containing code created by Richard Buckland on 28/01/11.
 *  Copyright 2012 Licensed under Creative Commons SA-BY-NC 3.0.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include "xanadu.h"

#include "mandelbrot.h"

int waitForConnection (int serverSocket);
int makeServerSocket (int portno);
void serveBMP (int socket);
void serveViewer(int socket);

#define SIMPLE_SERVER_VERSION 1.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 1917
#define NUMBER_OF_PAGES_TO_SERVE 10
// after serving this many pages the server will halt

int main (int argc, char *argv[]) {
    printf ("************************************\n");
    printf ("Starting simple server %f\n", SIMPLE_SERVER_VERSION);
    printf ("Serving bmps since 2012\n");

    int serverSocket = makeServerSocket (DEFAULT_PORT);
    printf ("Access this server at http://localhost:%d/\n", DEFAULT_PORT);
    printf ("************************************\n");

    char request[REQUEST_BUFFER_SIZE];

    int numberServed = 0;
    while (numberServed < NUMBER_OF_PAGES_TO_SERVE) {

        printf ("*** So far served %d pages ***\n", numberServed);

        int connectionSocket = waitForConnection (serverSocket);
        // wait for a request to be sent from a web browser, open a new
        // connection for this conversation

        // read the first line of the request sent by the browser
        int bytesRead;
        bytesRead = read (connectionSocket, request, (sizeof request)-1);
        assert (bytesRead >= 0);
        // were we able to read any data from the connection?

        //TODO: Find content of GET (between second and third blankspaces)------------
        /*
        if result is "/", run serveViewer()
        else if result is "/x1_y1_z8" or something, using the extract function from tutlab:parsing, get the x,y and z values and pass them into serveBMP to display the mandelbrot
        serveViewer() should work. everything else you'll need to implement unfortunately.
        */
        //-----------------------------------------------------------------------------

        // print entire request to the console
        printf (" *** Received http request ***\n %s\n", request);

        //send the browser a simple html page using http
        printf (" *** Sending http response ***\n");
        serveBMP(connectionSocket);

        // close the connection after sending the page- keep aust beautiful
        close(connectionSocket);

        numberServed++;
    }

    // close the server connection after we are done- keep aust beautiful
    printf ("** shutting down the server **\n");
    close (serverSocket);

    return EXIT_SUCCESS;
}

void serveViewer(int socket) {
    char* message;
    message = "HTTP/1.0 200 OK\r\n"
                "Content-Type: image/bmp\r\n"
                "\r\n"
        "<!DOCTYPE html>\n"
        "<script src=\"http://almondbread.cse.unsw.edu.au/tiles.js\"></script>";
    printf("No image, sending => %s\n", message);
    send (socket, message, strlen(message), 0);
}

void serveBMP (int socket) {
    char* message;

    // first send the http response header

    // (if you write stings one after another like this on separate
    // lines the c compiler kindly joins them togther for you into
    // one long string)
    message = "HTTP/1.0 200 OK\r\n"
                "Content-Type: image/bmp\r\n"
                "\r\n";
    printf ("about to send=> %s\n", message);
    write (socket, message, strlen (message));

    uint8_t* bmp = generateBuddhabrot(generateComplex(CENTER_X, CENTER_Y), ZOOM);

    write (socket, bmp, 512 * 512 * 3);
    freeBuddhabrot();
}


// start the server listening on the specified port number
int makeServerSocket (int portNumber) {

    // create socket
    int serverSocket = socket (AF_INET, SOCK_STREAM, 0);
    assert (serverSocket >= 0);
    // error opening socket

    // bind socket to listening port
    struct sockaddr_in serverAddress;
    memset ((char *) &serverAddress, 0,sizeof (serverAddress));

    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port        = htons (portNumber);

    // let the server start immediately after a previous shutdown
    int optionValue = 1;
    setsockopt (
      serverSocket,
      SOL_SOCKET,
      SO_REUSEADDR,
      &optionValue,
      sizeof(int)
    );

    int bindSuccess =
      bind (
         serverSocket,
         (struct sockaddr *) &serverAddress,
         sizeof (serverAddress)
      );

    assert (bindSuccess >= 0);
    // if this assert fails wait a short while to let the operating
    // system clear the port before trying again

    return serverSocket;
}

// wait for a browser to request a connection,
// returns the socket on which the conversation will take place
int waitForConnection (int serverSocket) {
   // listen for a connection
   const int serverMaxBacklog = 10;
   listen (serverSocket, serverMaxBacklog);

   // accept the connection
   struct sockaddr_in clientAddress;
   socklen_t clientLen = sizeof (clientAddress);
   int connectionSocket =
      accept (
         serverSocket,
         (struct sockaddr *) &clientAddress,
         &clientLen
      );

   assert (connectionSocket >= 0);
   // error on accept

   return (connectionSocket);
}

