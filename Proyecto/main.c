//------------Electrónica Digital II--------------------
//-----------------Proyecto #4--------------------------
//-------------Marco Juárez - 18516---------------------

//*********************************************************************************************
// Librerias
//*********************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

//**********************************************************************************************
// Variable
//**********************************************************************************************
uint8_t bandera = 0;
uint8_t bandera2 = 1;

//**********************************************************************************************
// Declaracion funcion
//**********************************************************************************************
void display(uint8_t data);

//**********************************************************************************************
//Codigo Principal
//**********************************************************************************************
int main(void)
{
    //Configuraciones reloj
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //Configuracion de puerto b para el display
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);//Habilitamos puerto B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);//Habilitamos puerto E
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4|GPIO_PIN_5);

    //Puerto c para los push
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7); //pines a utilizar
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

    //Puerto D para los leds rojos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);//Habilitamos puerto D
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    //Puerto E para leds verdes
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    //Configuracion UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1); //Habilitamos UART1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); //Habilitamos puerto B
    GPIOPinConfigure(GPIO_PB0_U1RX);//Habilitamos RX
    GPIOPinConfigure(GPIO_PB1_U1TX);//Habilitamos TX
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); // config uart
    UARTIntClear(UART1_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX | UART_INT_FE | UART_INT_PE | UART_INT_BE | UART_INT_OE | UART_INT_RI | UART_INT_CTS | UART_INT_DCD | UART_INT_DSR); // clear isr
    UARTEnable (UART1_BASE);



    while (1)
    {
        //Corrimiento de Bits
        bandera = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7) >> 4;
        if (bandera != bandera2)//Si es diferente a
        {
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, bandera);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ~bandera);
            display( 4 - (((bandera >> 3) & 0x01) + ((bandera >> 2) & 0x01) + ((bandera >> 1) & 0x01) + (bandera & 0x01)));
            bandera2 = bandera;
            UARTCharPut(UART1_BASE, bandera);//
        }
    }
}

void display(uint8_t bandera)
{
    switch (bandera & 0x0F)
    {
    //Display inicio en 0
        case 0:
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0xFF);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0x00);
            break;
        //Display en 1
        case 1:
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x00);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0x00);
            break;
        //Display en 2
        case 2:
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0xFF);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0xFF);
            break;
        //Display en 3
        case 3:
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0xFF);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x00);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0xFF);
            break;
        //Display en 4
        case 4:
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x00);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0xFF);
            break;
        default:
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0xFF);
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0x00);

    }
}
