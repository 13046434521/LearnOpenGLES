//
// Created by TianLong on 2021/2/6.
//

#include "opengl-utils.h"


extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_glClearColor(JNIEnv *env, jclass clazz, jfloat red,
                                                           jfloat green, jfloat blue, jfloat alpha) {
    __android_log_print(ANDROID_LOG_DEBUG,TAG,"glClearColor");
    glClearColor(red,green,blue,alpha);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_glClear(JNIEnv *env, jclass clazz, jint type) {
    glClear(type);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_onSurfaceChanged(JNIEnv *env, jclass clazz, jint x, jint y,
                                                         jint width, jint height) {
    __android_log_print(ANDROID_LOG_DEBUG,TAG,"glViewPort");
    glViewport(x,y,width,height);
}


GLuint vbo ;
GLuint program;
GLuint mvpMatrix;
GLuint position;

void initGLES(){
    Vertices vertices[3];
    vertices[0].position[0]=0.0f;
    vertices[0].position[1]=0.5f;
    vertices[0].position[2]=-0.1f;
    vertices[0].position[3]=1.0f;

    vertices[1].position[0]=-0.5f;
    vertices[1].position[1]=-0.5f;
    vertices[1].position[2]=-1.0f;
    vertices[1].position[3]=1.0f;

    vertices[2].position[0]=0.5f;
    vertices[2].position[1]=-0.5f;
    vertices[2].position[2]=-1.0f;
    vertices[2].position[3]=1.0f;

    int size = sizeof(vertices)*4;
    glGenBuffers(1,&vbo);//生成VBO
    glBindBuffer(GL_ARRAY_BUFFER,vbo);//确定vbo的数据类型为GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER,size, nullptr,GL_STATIC_DRAW);//在该vbo上开辟相应大小的内存
    glBufferSubData(GL_ARRAY_BUFFER,0,size,vertices);//传输数据到该vbo上
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_initGLES(JNIEnv *env, jclass clazz,
                                                       jobject asset_manager) {
    AAssetManager* assetManager = AAssetManager_fromJava(env,asset_manager);
    unsigned char* vertex = loadContentFiles(assetManager, "vertex.glsl");
    GLuint vertexShader =  compileShader(GL_VERTEX_SHADER,(char *)vertex);
    __android_log_print(ANDROID_LOG_DEBUG,TAG,"%d",vertexShader);

    unsigned char* fragment = loadContentFiles(assetManager,"fragment.glsl");
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER,(char *)fragment);
    __android_log_print(ANDROID_LOG_WARN,TAG,"%d", fragmentShader);

    program = createProgram(vertexShader,fragmentShader);

    position = glGetAttribLocation(program,"a_Position");
    mvpMatrix = glGetUniformLocation(program,"u_mvpMatrix");

    initGLES();
}extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_drawFrame(JNIEnv *env, jclass clazz) {

    glBindBuffer(GL_ARRAY_BUFFER,vbo);

    glEnableVertexAttribArray(position);


    glDrawArrays(GL_TRIANGLES,0,3);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}