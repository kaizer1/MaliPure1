//
// Created by Сергей Лоскутников on 10/07/2017.
//

#include "Matrix.h"

#include <cmath>
#include <cstdio>
#include <android/log.h>

#define LogLL(...) __android_log_print(ANDROID_LOG_VERBOSE, " matrix val ", __VA_ARGS__)

void matrixIdentityFunction(float* matrix)
{
    if(matrix == NULL)
    {
        return;
    }

    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;
    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;
    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

void matrixTranslate(float* matrix, float x, float y, float z)
{
    float temporaryMatrix[16];
    matrixIdentityFunction(temporaryMatrix);
    temporaryMatrix[12] = x;
    temporaryMatrix[13] = y;
    temporaryMatrix[14] = z;
    matrixMultiply(matrix,temporaryMatrix,matrix);
}

void matrixMultiply(float* destination, float* operand1, float* operand2)
{
    float theResult[16];
    int row, column = 0;
    int i,j = 0;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            theResult[4 * i + j] = operand1[j] * operand2[4 * i] + operand1[4 + j] * operand2[4 * i + 1] +
                                   operand1[8 + j] * operand2[4 * i + 2] + operand1[12 + j] * operand2[4 * i + 3];
        }
    }

    for(int i = 0; i < 16; i++)
    {
        destination[i] = theResult[i];
    }
}

void matrixFrustum(float* matrix, float left, float right, float bottom, float top, float zNear, float zFar)
{
    float temp, xDistance, yDistance, zDistance;
    temp = 2.0 *zNear;
    xDistance = right - left;
    yDistance = top - bottom;
    zDistance = zFar - zNear;
    matrixIdentityFunction(matrix);
    matrix[0] = temp / xDistance;
    matrix[5] = temp / yDistance;
    matrix[8] = (right + left) / xDistance;
    matrix[9] = (top + bottom) / yDistance;
    matrix[10] = (-zFar - zNear) / zDistance;
    matrix[11] = -1.0f;
    matrix[14] = (-temp * zFar) / zDistance;
    matrix[15] = 0.0f;
}

void matrixPerspective(float* matrix, float fieldOfView, float aspectRatio, float zNear, float zFar)
{
    float ymax, xmax;
//    ymax = zNear * tanf(fieldOfView * M_PI / 360.0);
    ymax = zNear * ( retSin(fieldOfView * M_PI / 360.0)/retCos(fieldOfView * M_PI / 360.0f));
    xmax = ymax * aspectRatio;
    matrixFrustum(matrix, -xmax, xmax, -ymax, ymax, zNear, zFar);
}



 float mainSin(float x)
{

    if((0 <= x) && (x <= 45.0f))
    {
        float t = x;
        return retSin(matrixDegreesToRadians(t));
    }
    else if((45 < x) && (x <= 90.0f))
    {
        float t = 90.0f - x;
     return retCos(matrixDegreesToRadians(t));
    }
    else if((90.0f < x) && (x <= 135.0f))
    {
        float t = x - 90.0f;
    return retCos(matrixDegreesToRadians(t));
    }
    else if((135.0f < x) && (x <= 180.0f))
    {
        float t = 180 - x;
   return retSin(matrixDegreesToRadians(t));
    }

        // all best
    else if((180.0f < x) && (x <= 225.0f))
    {
        float t = x - 180.0f;
        return -retSin(matrixDegreesToRadians(t));
    }
    else if((225.0f < x) && (x <= 270.0f))
    {
        float t = 270.0f - x;
        return -retCos(matrixDegreesToRadians(t));
    }
    else if((270 < x) && (x <= 315.0f))
    {
        float t = x - 270.0f;
        return -retCos(matrixDegreesToRadians(t));
    }
    else if((315.0f < x) && (x <= 360.0f))
    {
        float t = 360.0f - x;
        return -retSin(matrixDegreesToRadians(t));
    }

}



 float mainCos(float x)
{
     LogLL(" input cos == %f \n", x);
    if( (0 <= x) &&  (x <= 45.0f))
    {
         float t = x;
        LogLL(" this !! \n");
   return  retCos(matrixDegreesToRadians(t));
    }
    else if((45.0f < x) && (x <= 90.0f))
    {
         float t = 90.0f - x;
        LogLL(" HHJJ %f \n", t);
   return retSin(matrixDegreesToRadians(t));
    }
    else if((90.0f < x) && (x <= 135.0f))
    {
        float t = x - 90.0f;
        LogLL(" tTirk == %f \n", t);
   return -retSin(matrixDegreesToRadians(t));
    }
    else if((135.0f < x) && (x <= 180.0f))
    {
        float t = 180 - x;
    return -retCos(matrixDegreesToRadians(t));
    }

        // all best
    else if( (180 < x) && (x <= 225))
    {
        float t =  x - 180;
        return -retCos(matrixDegreesToRadians(t));
    }
    else if( (225.0f < x) && (x <= 270.0f))
    {
        float t =  270.0f - x;
        return -retSin(matrixDegreesToRadians(t));
    }

    else if((270 < x) && (x <= 315.0f))
    {
        float t =  x - 270.0f;
        return retSin(matrixDegreesToRadians(t));
    }
    else if((315.0f < x) && (x <= 360.0f))
    {
        float t =  360.0f - x;
        return retCos(matrixDegreesToRadians(t));
    }
}



//

float retSin(float x)
{

    float ret = x - (powf(x,3)/6) + (powf(x,5)/120) - (powf(x, 7)/ 5040) + (powf(x, 9)/326880);

    return ret;
}


float retCos(float x)
{
    float retur = 1 - (powf(x,2)/2) + (powf(x,4)/24) - (powf(x, 6)/ 720) + (powf(x, 8)/40320); // + (powf(x, 8)/40320);
    return retur;
}


void matrixRotateX(float* matrix, float angle)
{
    float tempMatrix[16];
    matrixIdentityFunction(tempMatrix);

//    tempMatrix[5] = cos(matrixDegreesToRadians(angle));
//    tempMatrix[9] = -sin(matrixDegreesToRadians(angle));
//    tempMatrix[6] = sin(matrixDegreesToRadians(angle));
//    tempMatrix[10] = cos(matrixDegreesToRadians(angle));
    tempMatrix[5] = mainCos(angle); // matrixDegreesToRadians
    tempMatrix[9] = -mainSin(angle);
    tempMatrix[6] = mainSin(angle);
    tempMatrix[10] = mainCos(angle);
    LogLL(" angle = %f,  matrix val 5 %f, 9 %f, 6 %f, 10 %f,\n", angle, tempMatrix[5], tempMatrix[9], tempMatrix[6],tempMatrix[10]);

    matrixMultiply(matrix, tempMatrix, matrix);
}

void matrixRotateY(float *matrix, float angle)
{
    float tempMatrix[16];
    matrixIdentityFunction(tempMatrix);

//    tempMatrix[0] = cos(matrixDegreesToRadians(angle));
//    tempMatrix[8] = sin(matrixDegreesToRadians(angle));
//    tempMatrix[2] = -sin(matrixDegreesToRadians(angle));
//    tempMatrix[10] = cos(matrixDegreesToRadians(angle));
    tempMatrix[0] = mainCos(angle);
    tempMatrix[8] = mainSin(angle);
    tempMatrix[2] = -mainSin(angle);
    tempMatrix[10] = mainCos(angle);
    matrixMultiply(matrix, tempMatrix, matrix);
}

void matrixRotateZ(float *matrix, float angle)
{
    float tempMatrix[16];
    matrixIdentityFunction(tempMatrix);

    tempMatrix[0] = cos(matrixDegreesToRadians(angle));
    tempMatrix[4] = -sin(matrixDegreesToRadians(angle));
    tempMatrix[1] = sin(matrixDegreesToRadians(angle));
    tempMatrix[5] = cos(matrixDegreesToRadians(angle));
    matrixMultiply(matrix, tempMatrix, matrix);
}

void matrixScale(float* matrix, float x, float y, float z)
{
    float tempMatrix[16];
    matrixIdentityFunction(tempMatrix);

    tempMatrix[0] = x;
    tempMatrix[5] = y;
    tempMatrix[10] = z;
    matrixMultiply(matrix, tempMatrix, matrix);
}

float matrixDegreesToRadians(float degrees)
{
     float newLff = M_PI * degrees / 180.0f;
     LogLL(" newLff == %f  returnValue == %f\n",degrees, newLff);
    return newLff;
}