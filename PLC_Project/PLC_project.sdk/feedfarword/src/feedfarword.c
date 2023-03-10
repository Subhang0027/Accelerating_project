/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "platform.h"
#include "xil_printf.h"
#include "weights_and_biases.h"
#include "Image.h"


int main()
{
    init_platform();
    float sigmoid(float x) {
         float result;
         result = 1 / (1 + exp(-x));
         return result;
    }
{
        int max = 0;

        float maxp = 0;

        int rows_l1= 30;

        int coloumns_l1= 784;

        int rows_l2 = 10;

        int coloumns_l2 = 30;

        float result_l1[30] = {0};

        float result_l2[10] = {0};

        float output_l1[30] = {0};

        float output_l2[10] = {0};

        int i,j,k;


                          /////////First layer Matrix multiplication//////////

        for(i = 0; i < rows_l1; i++)
        {
            for(j = 0; j < coloumns_l1; j++)
            {
                result_l1[i] = 0;
                for(k=0;k<coloumns_l1;k++)
                {
                    result_l1[i] += weight_for_layer_1[i][k] * image[k];
                }
            }
        }
        for(int i=0;i<rows_l1;i++)
        {
            float temp = result_l1[i] + biases_l1[i];
            output_l1[i] = temp;
        }
        for(int i=0;i<rows_l1;i++)
        {
            float temp = sigmoid(output_l1[i]);
            output_l1[i] = temp;
        }


                          ///////// Second layer Matrix Multiplication /////////


        for(i = 0; i < rows_l2; i++)
        {
            for(j = 0; j < coloumns_l2; j++)
            {
                result_l2[i] = 0;
                for(k=0;k<coloumns_l2;k++)
                {
                    result_l2[i] += weight_for_layer_2[i][k] * image[k];
                }
            }
        }
          for(int i=0;i<rows_l2;i++)
        {
            float temp = result_l2[i] + biases_l2[i];
            output_l2[i] = temp;
        }
        for(int i=0;i<rows_l2;i++)
        {
            float temp = sigmoid(output_l2[i]);
            output_l2[i] = temp;

            if(temp > maxp)
            {
                maxp = temp;
                max = i;
            }
//             printf("%d - %f\n",i, output_l2[i]);

        }
        printf("The prediction is :");
        printf("%d - %f\n",max, maxp);
    }

    cleanup_platform();
    return 0;
}
