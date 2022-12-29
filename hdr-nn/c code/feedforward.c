#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include"image_header_file.h"
#include "weight_biases.h"

float sigmoid_function(float x) {
     float r;
     r = 1 / (1 + exp(-x));
     return r;
}
int main(){
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
        float temp = sigmoid_function(output_l1[i]);
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
        float temp = sigmoid_function(output_l2[i]);
        output_l2[i] = temp;

        if(temp > maxp)
        {
            maxp = temp;
            max = i;
        }
        //printf("number is %d and prediction probability is %f\n",i, output_l2[i]);
        
    }
    // Prediction number
    printf("The prediction is :");
    printf("number is %d and prediction probability is %f\n",max, maxp);
    return 0;
}