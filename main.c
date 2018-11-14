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
        fflush(stdin);
        result= getchar();
        char buffer[50];
        
        blue=50;
        red=50;
        green=50;
        
        sprintf(buffer, "B%d", blue);
        writeComm(&hComm, "buffer\n");
        sprintf(buffer, "R%d", red);
        writeComm(&hComm, "buffer\n")
        sprintf(buffer, "G%d", green);
        writeComm(&hComm, "buffer\n");
        
       
        
        
        switch(result)
        {
            case('0'):
                closeHandle(hComm);
                break;
            case('1'):
                if(red==0)
                {
                    printf("Red cannot be decremented any more, resetting value to 50");
                    red=50;
                   
                }
                else if(red>= 5 && red<= 100)
                {
                    red= red- 5;
                    printf("Decrementing Red");
                 
                }
                
                sprintf(buffer, "R%d", red);
                writeComm(&hComm, "buffer\n");
                
                break;
            case('2'):
               if(green==0)
                {
                    printf("Green cannot be decremented any more, resetting value to 50");
                    red=50;
                   
                }
                else if(green>= 5 && green<= 95)
                {
                    green=green- 5;
                    printf("Decrementing Green");
                 
                }
                
                sprintf(buffer, "G%d", green);
                writeComm(&hComm, "buffer\n");
                
                break;
            case('3'):
                if(blue==0)
                {
                    printf("Blue cannot be decremented any more, resetting value to 50");
                    blue=50;
                   
                }
                else if(blue>= 5 && blue<= 95)
                {
                    blue= blue- 5;
                    printf("Decrementing blue");
                 
                }
                
                sprintf(buffer, "B%d", blue);
                writeComm(&hComm, "buffer\n");
                
                break;
            case ('5'):
                printf("Reset all LED values to 50");
                blue= 50;
                green= 50;
                red=50;
                sprintf(buffer, "R%d", red);
                sprintf(buffer, "G%d", green);
                sprintf(buffer, "B%d", blue);
                break;
            case('7'):
                
                if(red>= 5 && red<= 95)
                {
                    red= red+ 5;
                    printf("Decrementing Red");
                 
                }
                else if(red==100)
                {
                    printf("Red cannot be incremented any more, resetting value to 50");
                    red=50;
                }
                sprintf(buffer, "R%d", red);
                writeComm(&hComm, "buffer\n");
                
                break;
           case('8'):
                if(green>= 5 && green<= 95)
                {
                    green= green+ 5;
                    printf("Decrementing Green");
                 
                }
                else if(green==100)
                {
                    printf("Green cannot be incremented any more, resetting value to 50");
                    green=50;
                }
                sprintf(buffer, "G%d", green);
                writeComm(&hComm, "buffer\n");
                
                break;
          case('9'):
                if(blue>= 5 && blue<= 95)
                {
                    blue= blue + 5;
                    printf("Decrementing Blue");
                 
                }
                else if(blue==100)
                {
                    printf("Blue cannot be incremented any more, resetting value to 50");
                    blue=50;
                }
                sprintf(buffer, "B%d", blue);
                writeComm(&hComm, "buffer\n");
                
                break;
        }
        
        
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
