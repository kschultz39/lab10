#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>
#include "pc_uart.h"

//Prototypes
int promptCommInput(void);

int main()
{
    //Configure Interrupt Vectors
    signal(SIGINT, intHandler);
    signal(SIGTERM, intHandler);

    HANDLE hComm;                                       // hComm stream
    DCB dcbSerialParams = {0};                          // Serial parameter
    COMMTIMEOUTS timeouts = {0};                        // Serial timeout
    char readString[RX_BUFFER_SIZE];                    // Read Input String
    int commInt;

    commInt = promptCommInput();                        // Prompt the user for Input
    openComm(&hComm, commInt);                          // Open the COMM Port
    setSerialParams(&hComm, &dcbSerialParams); // Set the serial port params
    setTimeouts(&hComm, &timeouts);                     // Set Timeout params

    //
    while(!UARTexitFlag)
    {
        //Write code here
        writeComm(&hComm, "ON\n");
        Sleep(20);
        readComm(&hComm, readString);
        Sleep(1000);
        writeComm(&hComm, "OFF\n");
        Sleep(20);
        readComm(&hComm, readString);
        Sleep(1000);
    }
    CloseHandle(hComm);                                 // Close the Serial Port
    return 0;
}

int promptCommInput(void)
{
    int commPort = 0;
    // Get the Comm Port from the user
    while(commPort < 1)
    {
        fflush(stdin);
        printf("Enter the comm port as a number: ");
        scanf("%d", &commPort);
    }
    return commPort;
}
