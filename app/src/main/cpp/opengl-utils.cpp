//
// Created by TianLong on 2021/2/6.
//

#include "opengl-utils.h"


extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_glClearColor(JNIEnv *env, jclass clazz, jfloat red,
                                                           jfloat green, jfloat blue,
                                                           jfloat alpha) {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "glClearColor");
    glClearColor(red, green, blue, alpha);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_glClear(JNIEnv *env, jclass clazz, jint type) {
    glClear(type);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_onSurfaceChanged(JNIEnv *env, jclass clazz, jint x,
                                                               jint y,
                                                               jint width, jint height) {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "glViewPort");
    glViewport(x, y, width, height);
}


GLuint vbo;
GLuint program;
GLuint textureCoord;
GLuint mvpMatrix;
GLuint position;
glm::mat4 mvp;
GLuint textures;

void initBufferData() {
    Vertices vertices[4];
    vertices[0].position[0] = -1.0f;
    vertices[0].position[1] = -1.0f;
    vertices[0].position[2] = -1.0f;
    vertices[0].position[3] = 1.0f;
    vertices[0].texture[0] = 0;
    vertices[0].texture[1] = 1;


    vertices[1].position[0] =  1.0f;
    vertices[1].position[1] = -1.0f;
    vertices[1].position[2] = -1.0f;
    vertices[1].position[3] = 1.0f;
    vertices[1].texture[0] = 1;
    vertices[1].texture[1] = 1;

    vertices[2].position[0] = -1.0f;
    vertices[2].position[1] = 1.0f;
    vertices[2].position[2] = -1.0f;
    vertices[2].position[3] = 1.0f;
    vertices[2].texture[0] = 0;
    vertices[2].texture[1] = 0;

    vertices[3].position[0] = 1.0f;
    vertices[3].position[1] = 1.0f;
    vertices[3].position[2] = -1.0f;
    vertices[3].position[3] = 1.0f;
    vertices[3].texture[0] = 1;
    vertices[3].texture[1] = 0;

    int size = sizeof(vertices) * 4;
    glGenBuffers(1, &vbo);//生成VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);//确定vbo的数据类型为GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);//在该vbo上开辟相应大小的内存
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);//传输数据到该vbo上
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void initTexture(){
    glGenTextures(1,&textures);
    glBindTexture(GL_TEXTURE_2D,textures);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,0,0,0,GL_RGBA,GL_UNSIGNED_BYTE,0);
    glBindTexture(GL_TEXTURE_2D,0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_initGLES(JNIEnv *env, jclass clazz,
                                                       jobject asset_manager) {
    AAssetManager *assetManager = AAssetManager_fromJava(env, asset_manager);
    unsigned char *vertex = loadContentFiles(assetManager, "vertex.glsl");
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, (char *) vertex);

    unsigned char *fragment = loadContentFiles(assetManager, "fragment.glsl");
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, (char *) fragment);

    program = createProgram(vertexShader, fragmentShader);

    position = glGetAttribLocation(program, "a_Position");
    textureCoord = glGetAttribLocation(program,"a_TextureCoord");
    mvpMatrix = glGetUniformLocation(program, "u_mvpMatrix");

    initBufferData();
    initTexture();
}



extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_drawFrame(JNIEnv *env, jclass clazz) {

    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(position, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_drawFrameData(JNIEnv *env, jclass clazz, jint width,
                                                            jint height, jobject data_buffer) {
    void* data = env->GetDirectBufferAddress(data_buffer);
    int w = width;
    int h = height;

    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(position,4,GL_FLOAT,GL_FALSE,sizeof(Vertices),0);
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(textureCoord,4,GL_FLOAT,GL_FALSE,sizeof(Vertices),(void *)(sizeof(float)*4));
    glEnableVertexAttribArray(textureCoord);

    glBindTexture(GL_TEXTURE_2D,textures);
//    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);
}