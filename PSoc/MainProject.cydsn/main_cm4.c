/******************************************************************************
* File Name: main_cm4.c
*
* Version: 1.10
*
* Description: This file main application code for the CE223726 EmWin Graphics
*				library TFT Display.
*
* Hardware Dependency: CY8CKIT-028-TFT TFT Display Shield
*					   CY8CKIT-062-BLE PSoC6 BLE Pioneer Kit
*
*******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/
/******************************************************************************
* This file contains the main application code for CE223726 that demonstrates
* controlling a TFT display based on Solomon SSD1355 display controller.
* The project displays a start up screen with Cypress logo and text "CYPRESS EMWIN
* GRAPHICS DEMO TFT DISPLAY".  The project then displays the following screens
* in a loop
*
*	1. A screen demonstrating various text alignements, styles and modes
*	2. A screen demonstratinv various text colors
*	3. A screen showing color bars with gradient
*	4. A screen that displays a bitmap image with an overlaid text
*
 *******************************************************************************/
#include "project.h"
#include "GUI.h"
#include "stdlib.h"
#include "bitmaps.h"
#include <stdio.h>

uint32 CONS = 1800;

void ShowStartupScreen(void){
    GUI_SetFont(GUI_FONT_24_1);
    GUI_SetBkColor(GUI_BLACK);
    GUI_SetColor(GUI_WHITE);	
    GUI_SetTextMode(GUI_TM_NORMAL);

    /* Clear the display */
    GUI_Clear();

    /* Display instructions text */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("To start scanning", 160, 90);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("Press BTN0", 160, 110);
}

void scanningscreen(){
    GUI_SetFont(GUI_FONT_24_1);
    GUI_SetBkColor(GUI_BLACK);
    GUI_SetColor(GUI_WHITE);	
    GUI_SetTextMode(GUI_TM_NORMAL);

    /* Clear the display */
    GUI_Clear();

    /* Display instructions text */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("Scanning", 160, 90);
}

void truescreen(void)
{
    
    GUI_SetFont(GUI_FONT_32_1);
    GUI_SetBkColor(GUI_BLACK);
    GUI_SetColor(GUI_WHITE);	
    GUI_SetTextMode(GUI_TM_NORMAL);

    /* Clear the display */
    GUI_Clear();

    /* Display instructions text */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("YOUR BANCNOTE", 160, 90);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("IS GOOD", 160, 130);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_SetFont(GUI_FONT_16_1);
    GUI_DispStringAt("To restart press BTN1", 160, 200);
}

void falsescreen(void)
{
    
    GUI_SetFont(GUI_FONT_32_1);
    GUI_SetBkColor(GUI_BLACK);
    GUI_SetColor(GUI_WHITE);	
    GUI_SetTextMode(GUI_TM_NORMAL);

    /* Clear the display */
    GUI_Clear();

    /* Display instructions text */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("YOUR BANCNOTE", 160, 90);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("IS FAKE", 160, 130);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_SetFont(GUI_FONT_16_1);
    GUI_DispStringAt("To restart press BTN1", 160, 200);
}




bool checkmagn(){
    
    uint32 sum = 0;
    
    int i = 0;
    for (;;){
        uint32 n = ADC_GetResult32(0);
        sum += n;
        i++;
        if(i == 10000){
            sum = sum / (i/1);
            break;
        }
    }
    
    printf("%d\n\r", sum);
    printf("%d\n\r", abs(sum - CONS));
    
    if (abs(sum - CONS) > 18){
        if (abs(sum - CONS) < 40){ 
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
    
}

bool checkimg(){
    bool ret1;
    bool ret2;
    
    Cy_GPIO_Write(WHITE_LED_PORT, WHITE_LED_NUM, 0);
    CyDelay(500);
    printf("5\n\r");
    for(;;){
        char ind = getchar();
        printf("%c\n\r", ind);
        if (ind == '1'){
            ind = getchar();
            printf("%c\n\r", ind);
            if (ind == '2'){
                ret1 = true;
                break;
            } else{
                ret1 = false;
                break;
            }
        }

    }
    
    
    CyDelay(200);
    
    //Cy_GPIO_Write(UF_LED_PORT, UF_LED_NUM, 1);
    printf("6\n\r");
    for (;;){
        char ind = getchar();
        printf("%c\n\r", ind);        
        if (ind == '1'){
            ind = getchar();
            printf("%c\n\r", ind);
            if (ind == '2'){
                ret2 = true;
                break;
            } else{
                ret2 = false;
                break;
            }
        }
    }

    
    //Cy_GPIO_Write(UF_LED_PORT, UF_LED_NUM, 0);
    
    if (ret1 & ret2){
        return true;
    } else {
        return false;
    }
}

bool checkfunc(){
    
    bool ret1 = checkimg();
    bool ret2 = checkmagn();
    
    if (ret2){
        if (ret1){
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
int main(void)
{

    __enable_irq(); /* Enable global interrupts. */

    /* Initialize EmWin Graphics */
    GUI_Init();
    CapSense_Start();
    CapSense_ScanAllWidgets();
    UART_Start();
    ADC_Start();
    ADC_StartConvert();
    
    Cy_GPIO_Write(WHITE_LED_PORT, WHITE_LED_NUM, 1);
    //Cy_GPIO_Write(UF_LED_PORT, UF_LED_NUM, 1);
    ShowStartupScreen();

    uint16 i = 0;
    for(;;)
    {
       if (!CapSense_IsBusy()){
            CapSense_ProcessAllWidgets();
            if(CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID)){
               CyDelay(100);
                scanningscreen();
                if (checkfunc()){
                    truescreen();
                } else{
                    falsescreen();
                }
                Cy_GPIO_Write(WHITE_LED_PORT, WHITE_LED_NUM, 1);
            }
            if(CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID)){
               CyDelay(100);
                if (i == 1){
                    Cy_GPIO_Write(BLUE_PORT, BLUE_NUM, 0);
                    i = 0;
                    
                } else {
                    Cy_GPIO_Write(BLUE_PORT, BLUE_NUM, 1);
                    i = 1;
                }
                ShowStartupScreen();
            }

            CapSense_UpdateAllBaselines();
            CapSense_ScanAllWidgets();
        }
    }
}

/* [] END OF FILE */
