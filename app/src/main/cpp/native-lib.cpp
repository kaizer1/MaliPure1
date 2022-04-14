//#include <jni.h>
//#include <string>
//
//extern "C"
//JNIEXPORT jstring JNICALL
//Java_com_mailsimpleunderstand_sergeyloscutnikov_malipure_MaliMain_stringFromJNI(
//        JNIEnv *env,
//        jobject /* this */) {
//    std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());
//}


/*
 * Created on Sergey Loskutnikov
 *
 */

#include <jni.h>
#include <android/log.h>

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Matrix.h"
#include "Texture.h"
#include "LosMathematica.h"

#include "NeonGo.h"
#include <cpu-features.h>
//#include <cpufeatures/cpu-features.h>

#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LogWarn(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)



/* [shaders] */
static const char glVertexShader[] =
        "attribute vec4 vertexPosition;\n"
                "attribute vec2 vertexTextureCord;\n"
                "varying vec2 textureCord;\n"
                "uniform mat4 projection;\n"
                "uniform mat4 modelView;\n"
                "void main()\n"
                "{\n"
                "    gl_Position = projection * modelView * vertexPosition;\n"
                "    textureCord = vertexTextureCord;\n"
                "}\n";

static const char glFragmentShader[] =
        "precision mediump float;\n"
                "uniform sampler2D texture;\n"
                "varying vec2 textureCord;\n"
                "void main()\n"
                "{\n"
                "    gl_FragColor = texture2D(texture, textureCord);\n"
                "}\n";
/* [shaders] */

GLuint loadShader(GLenum shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader != 0)
    {
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (compiled != GL_TRUE)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 0)
            {
                char * logBuffer = (char*) malloc(infoLen);

                if (logBuffer != NULL)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, logBuffer);
                    LOGE("Could not Compile Shader %d:\n%s\n", shaderType, logBuffer);
                    free(logBuffer);
                    logBuffer = NULL;
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

GLuint createProgram(const char* vertexSource, const char * fragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (vertexShader == 0)
    {
        return 0;
    }

    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (fragmentShader == 0)
    {
        return 0;
    }

    GLuint program = glCreateProgram();

    if (program != 0)
    {
        glAttachShader(program , vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program , GL_LINK_STATUS, &linkStatus);

        if(linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;

            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);

            if (bufLength > 0)
            {
                char* logBuffer = (char*) malloc(bufLength);

                if (logBuffer != NULL)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, logBuffer);
                    LOGE("Could not link program:\n%s\n", logBuffer);
                    free(logBuffer);
                    logBuffer = NULL;
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint glProgram;
GLuint vertexLocation;
GLuint samplerLocation;
GLuint projectionLocation;
GLuint modelViewLocation;
GLuint textureCordLocation;
GLuint textureId;

float projectionMatrix[16];
float modelViewMatrix[16];
float angle = 0;


static void cpuLosInfo(void)
{
#if defined(__arm__)

    LogWarn( " ARM los \n");
#elif defined(__aarch64__)
    LogWarn( " Aa64 los  \n");

#endif
}


/* [setupGraphicsUpdate] */
bool setupGraphics(int width, int height)
{

    cpuLosInfo();
     // see core CPU
   int jio = android_getCpuCount();
    LogWarn( " my cpu core == %d \n", jio);


    glProgram = createProgram(glVertexShader, glFragmentShader);


    //simdLos newLosVecor = createVector2Los(2.0f, -32.023f);
    LosVector2 lvertor(2.0f, -32.023f);// = new LosVector2(2.0f, -32.23f);
    LosVector2 right(5.0f, 0.4f);

    const int ase = 0;
    LosVector2 result = lvertor * right;
    LogWarn(" my result vector multiple x == %f and y == %f \n", getValueSimdVecX(result, ase), getValueSimdVecY(result));

    lvec4f newLve(3, 1, 0.4f, -3);
    lvec4f newWor(-9.0f, 4, 0.934f, 0.0f);
    lvec4f vifk(-30.0f, 0.23421f, 0.004f, -3.234f);
    lvec4f simpleExample (3.4f, 0.0f, 0.0f, 0.0f);
    lvec4f finl = newLve * newWor;

    // float * dst, const float * cst, float * src, uint32_t count

     float tuir = 45;
     const float kol = 0.4f;
    float ryti = -0.2341234f;  // 0.24893f
    uint32_t  cou = 32;

     // uint32_t

     //float df[2]=  {0.24f, -0.4235f};
    int* retuzi;
     int eer = 3;
    retuzi = &eer;

//    typedef struct losLL
//    {
//        float mitu[2];
//    }losStruct;

//    losStruct newStruct;
//    newStruct.mitu[0] = (int32_t)5;
//    newStruct.mitu[1] = (int32_t)17;

    losVectorInt2 newDl;

    const float fe[16] = {2.54f, 0.324f, -0.2888f, 1.283746f,
                          8.1234f, 0.234f, -4.11f, 1.1f,
                          3.23f, 0.03f, 0.1445f, -0.4f,
                          0.4f,  0.14f, 0.099f, -1.0f};


    const float sef[16] = {0.344f, 1.2344f, 0.34288f, -3.44746f,
                          -0.13f, 6.0f, 1.0999f, 2.0f,
                          2.324f, -2.0f, 1.5f, 0.943f,
                          -3.1f,  1.0000f, 2.9f, 0.777f};


    unsigned int co = 3;
    float floatback;
    float serLos = ne10_mulcmatvec_cm2x2f_v2f_neon (&floatback, fe, sef);
   LogWarn(" serLos vector == %f and BACK == %f \n", serLos, floatback);

    lvec4f eq = newLve * simpleExample;

    lmatff newMat(newLve, newWor, vifk, vifk);
    lmatff finalK(newWor, simpleExample, vifk, newLve);
     lmatff rt = newMat * finalK;
   LogWarn(" me result vector == %f , %f , %f, %f \n", getXvectro4(eq.simple4f), getYvectro4(eq.simple4f), getZvectro4(eq.simple4f), getWvectro4(eq.simple4f));

      for(int jio = 0; jio <= 3; jio++)
      {
          for(int kij = 0; kij <= 3; kij++)
              LogWarn("  matrix Float == %f \n",rt.backElememtMatrix(jio, kij));
      }




    if (!glProgram)
    {
        LOGE ("Could not create program");
        return false;
    }

    vertexLocation = glGetAttribLocation(glProgram, "vertexPosition");
    textureCordLocation = glGetAttribLocation(glProgram, "vertexTextureCord");
    projectionLocation = glGetUniformLocation(glProgram, "projection");
    modelViewLocation = glGetUniformLocation(glProgram, "modelView");
    samplerLocation = glGetUniformLocation(glProgram, "texture");

    /* Setup the perspective. */
    matrixPerspective(projectionMatrix, 45, (float)width / (float)height, 0.1f, 100);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, width, height);

    /* Load the Texture. */
    textureId = loadSimpleTexture();
    if(textureId == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}






/* [setupGraphicsUpdate] */
/* [verticesAndTexture] */
GLfloat cubeVertices[] = {-1.0f,  1.0f, -1.0f, /* Back. */
                          1.0f,  1.0f, -1.0f,
                          -1.0f, -1.0f, -1.0f,
                          1.0f, -1.0f, -1.0f,
                          -1.0f,  1.0f,  1.0f, /* Front. */
                          1.0f,  1.0f,  1.0f,
                          -1.0f, -1.0f,  1.0f,
                          1.0f, -1.0f,  1.0f,
                          -1.0f,  1.0f, -1.0f, /* Left. */
                          -1.0f, -1.0f, -1.0f,
                          -1.0f, -1.0f,  1.0f,
                          -1.0f,  1.0f,  1.0f,
                          1.0f,  1.0f, -1.0f, /* Right. */
                          1.0f, -1.0f, -1.0f,
                          1.0f, -1.0f,  1.0f,
                          1.0f,  1.0f,  1.0f,
                          -1.0f, 1.0f, -1.0f, /* Top. */
                          -1.0f, 1.0f,  1.0f,
                          1.0f, 1.0f,  1.0f,
                          1.0f, 1.0f, -1.0f,
                          -1.0f, - 1.0f, -1.0f, /* Bottom. */
                          -1.0f,  -1.0f,  1.0f,
                          1.0f, - 1.0f,  1.0f,
                          1.0f,  -1.0f, -1.0f
};

GLfloat textureCords[] = { 1.0f, 1.0f, /* Back. */
                           0.0f, 1.0f,
                           1.0f, 0.0f,
                           0.0f, 0.0f,
                           0.0f, 1.0f, /* Front. */
                           1.0f, 1.0f,
                           0.0f, 0.0f,
                           1.0f, 0.0f,
                           0.0f, 1.0f, /* Left. */
                           0.0f, 0.0f,
                           1.0f, 0.0f,
                           1.0f, 1.0f,
                           1.0f, 1.0f, /* Right. */
                           1.0f, 0.0f,
                           0.0f, 0.0f,
                           0.0f, 1.0f,
                           0.0f, 1.0f, /* Top. */
                           0.0f, 0.0f,
                           1.0f, 0.0f,
                           1.0f, 1.0f,
                           0.0f, 0.0f, /* Bottom. */
                           0.0f, 1.0f,
                           1.0f, 1.0f,
                           1.0f, 0.0f
};
/* [verticesAndTexture] */

GLushort indicies[] = {0, 3, 2, 0, 1, 3, 4, 6, 7, 4, 7, 5,  8, 9, 10, 8, 11, 10, 12, 13, 14, 15, 12, 14, 16, 17, 18, 16, 19, 18, 20, 21, 22, 20, 23, 22};


//int flOit(int x)
//{
//
//#pragma arm
//
//    asm volatile
//
//    STMFD sp!, {r0}
//    ADD r0, x, 1
//    EOR x, r0, x
//   LDMFD sp!, {r0}
//}
// return x;
//}

void renderFrame()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    matrixIdentityFunction(modelViewMatrix);
    LogWarn(" my sin == %f \n", angle);
    matrixRotateX(modelViewMatrix, angle);
    matrixRotateY(modelViewMatrix, angle);

    matrixTranslate(modelViewMatrix, 0.0f, 0.0f, -10.0f);

    glUseProgram(glProgram);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, cubeVertices);
    glEnableVertexAttribArray(vertexLocation);

    /* [enableAttributes] */
    glVertexAttribPointer(textureCordLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCords);
    glEnableVertexAttribArray(textureCordLocation);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE,projectionMatrix);
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelViewMatrix);

    /* Set the sampler texture unit to 0. */
    glUniform1i(samplerLocation, 0);
    /* [enableAttributes] */
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indicies);


    angle += 1;
    if (angle >= 360)
    {

        angle = 0;
    }
}

extern "C"
{
 //                    Java_com_mailsimpleunderstand_sergeyloscutnikov_malipure_MaliMain_stringFromJNI
 //                    Java_com_mailsimpleunderstand_sergeyloscutnikov_malipure_NativeLibrary_init
JNIEXPORT void JNICALL Java_com_mailsimpleunderstand_sergeyloscutnikov_malipure_NativeLibrary_init (JNIEnv * env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_mailsimpleunderstand_sergeyloscutnikov_malipure_NativeLibrary_step(
        JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_com_mailsimpleunderstand_sergeyloscutnikov_malipure_NativeLibrary_init(
        JNIEnv * env, jobject obj, jint width, jint height)
{
    setupGraphics(width, height);
}

//  JAVA_com_mail_simple_understand_sergeyloscutnikov.example_mali

JNIEXPORT void JNICALL Java_com_mailsimpleunderstand_sergeyloscutnikov_malipure_NativeLibrary_step(
        JNIEnv * env, jobject obj)
{
    renderFrame();
}



// TODO: from armNeon
//#include <chrono>
//#include <arm_neon.h>
//
//
//
//short* generateRamp(short startValue, short len){
//    short* ramp = new short[len];
//    for( short i = 0; i < len; i++){
//        ramp[i] = startValue + i;
//    }
//    return ramp;
//}
//
//
//
//std::chrono::system_clock::time_point  now();
//double msElapsedTime(std::chrono::system_clock::time_point start );
//int dot_product_neon(short* vector1, short* vector2, short len);
//int dot_product(short* vector1, short* vector2, short len);
//
//extern "C" JNIEXPORT jstring JNICALL
//Java_com_sergey_los_lokutnikovgames_armsimd_MainActivity_stringFromJNI(
//        JNIEnv* env,
//        jobject /* this */) {
//    std::string hello = "Hello from C++";
//
//
//    const int rampLenght = 1024;
//    const int trials = 10000;
//
//    auto ramp1 = generateRamp(0, rampLenght);
//    auto ramp2 = generateRamp(0, rampLenght);
//
//    int lastResult = 0;
//    auto start = now();
//    for (int i = 0; i < trials; i++) {
//        lastResult = dot_product(ramp1, ramp2, rampLenght);
//    }
//    auto elapserTime = msElapsedTime(start);
//
//
//    // with Neon
//    int lastResultNeon = 0;
//    start = now();
//
//    for (int i = 0; i < trials; i++) {
//        lastResultNeon = dot_product_neon(ramp1, ramp2, rampLenght);
//    }
//    auto elapsedTimeNeon = msElapsedTime(start);
//
//    delete ramp1, ramp2;
//
//    std::string resultString = "----------------- NO NEON ---------------------\n Result " +
//                               std::to_string(lastResult) + "\n ELapsed time: " +
//                               std::to_string((int) elapserTime) + " ms"
//                               + "\n\n-------=========== NEON ============----------\n"
//                               + "Result: " + std::to_string(lastResultNeon)
//                               + "\n Elapdes Time: " + std::to_string((int)elapsedTimeNeon) + " ms";
//
//   // return env->NewStringUTF(hello.c_str());
//   return  env->NewStringUTF( resultString.c_str() );
//
//}
//
//
//
//
//int dot_product(short* vector1, short* vector2, short len){
//       int result = 0;
//       for(short i = 0; i < len; i++){
//            result += vector1[i] + vector2[i];
//       }return result;
//}
//
//int dot_product_neon(short* vector1, short* vector2, short len){
//       const short transferSize = 4;
//       short segments = len/transferSize;
//
//       int32x4_t partialSumsNen = vdupq_n_s32(0);
//       for(short  i =0; i < segments; i++){
//            short offset = i * transferSize;
//            int16x4_t vector1Neon = vld1_s16(vector1 + offset);
//            int16x4_t vector2Neon = vld1_s16(vector2 + offset);
//
//            partialSumsNen = vmlal_s16(partialSumsNen, vector1Neon, vector2Neon);
//       }
//
//       //Store partial sums
//        int partialSums[transferSize];
//       vst1q_s32(partialSums, partialSumsNen);
//
//       int result = 0;
//       for( short i = 0; i < transferSize; i++){
//           result += partialSums[i];
//       }
//
//       return result;
//}
//
//double msElapsedTime(std::chrono::system_clock::time_point start ){
//    auto end = std::chrono::system_clock::now();
//   return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//}
//
//std::chrono::system_clock::time_point  now(){
//    return std::chrono::system_clock::now();
//}