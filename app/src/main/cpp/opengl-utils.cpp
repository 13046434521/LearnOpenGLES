//
// Created by TianLong on 2021/2/6.
//

#include "opengl-utils.h"

GLuint vbo ;
GLuint program;
GLuint position;
GLuint texture;
GLuint a_texture;
GLuint whiteLevel;
GLuint modelMatrix;
GLuint viewMatrix;
GLuint projectMatrix;
glm::mat4 model,view,project;
Vertices vertices[4];

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
    __android_log_print(ANDROID_LOG_DEBUG,TAG,"glViewPort:width:%d:height:%d",width,height);
    glViewport(x,y,width,height);

    float left = -(width)/2;
    float right = (width)/2;
    float top = (height)/2;
    float bottom = -(height)/2;
    float near = 0.1f;
    float far =100.0f;

    //模型矩阵
//    model =  glm::scale(0.5f,0.5f, 1.0f);
    //视矩阵
//    view = glm::lookAt(glm::vec3 (0,0,4),glm::vec3 (0,0,-1),glm::vec3 (0,1,0));
    //透视投影矩阵
//    project = glm::perspectiveFov(45.0f,(float )width,(float )height,1.0f,1000.0f);
    //正交投影矩阵
//    project = glm::ortho(left,right,bottom,top,near,far);
}

int width =1;
int height=1;

void initBufferData(){
    vertices[0].position[0]=-width;
    vertices[0].position[1]=-height;
    vertices[0].position[2]=-1.0f;
    vertices[0].position[3]=1.0f;

    vertices[1].position[0]=width;
    vertices[1].position[1]=-height;
    vertices[1].position[2]=-1.0f;
    vertices[1].position[3]=1.0f;

    vertices[2].position[0]=-width;
    vertices[2].position[1]=height;
    vertices[2].position[2]=-1.0f;
    vertices[2].position[3]=1.0f;

    vertices[3].position[0]=width;
    vertices[3].position[1]=height;
    vertices[3].position[2]=-1.0f;
    vertices[3].position[3]=1.0f;

    vertices[0].texture[0]=0;
    vertices[0].texture[1]=1;
    vertices[1].texture[0]=1;
    vertices[1].texture[1]=1;
    vertices[2].texture[0]=0;
    vertices[2].texture[1]=0;
    vertices[3].texture[0]=1;
    vertices[3].texture[1]=0;
//    vertices[0].texture[0]=0;
//    vertices[0].texture[1]=0;
//    vertices[1].texture[0]=1;
//    vertices[1].texture[1]=0;
//    vertices[2].texture[0]=0;
//    vertices[2].texture[1]=1;
//    vertices[3].texture[0]=1;
//    vertices[3].texture[1]=1;

    int size = sizeof(vertices)*4;
    glGenBuffers(1,&vbo);//生成VBO
    glBindBuffer(GL_ARRAY_BUFFER,vbo);//确定vbo的数据类型为GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER,size, nullptr,GL_STATIC_DRAW);//在该vbo上开辟相应大小的内存
    glBufferSubData(GL_ARRAY_BUFFER,0,size,vertices);//传输数据到该vbo上
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void initTexture(){
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D,0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_initGLES(JNIEnv *env, jclass clazz,
                                                       jobject asset_manager) {
    AAssetManager* assetManager = AAssetManager_fromJava(env,asset_manager);
    unsigned char* vertex = loadContentFiles(assetManager, "vertex.glsl");
    GLuint vertexShader =  compileShader("Vertex",GL_VERTEX_SHADER,(char *)vertex);
    __android_log_print(ANDROID_LOG_WARN,TAG,"%s",(char *)vertex);

    unsigned char* fragment = loadContentFiles(assetManager,"white_fs.glsl");
    GLuint fragmentShader = compileShader("Fragment",GL_FRAGMENT_SHADER,(char *)fragment);
    __android_log_print(ANDROID_LOG_WARN,TAG,"%s", ( char *)fragment);

    program = createProgram(vertexShader,fragmentShader);
    __android_log_print(ANDROID_LOG_WARN,TAG,"%s""%d","program:",program);

    position = glGetAttribLocation(program,"aPosition");
    __android_log_print(ANDROID_LOG_WARN,TAG,"%s""%d","a_Position:",position);

    a_texture = glGetAttribLocation(program,"aTexCoord");
    __android_log_print(ANDROID_LOG_WARN,TAG,"%s""%d","aTexCoord:",a_texture);

    whiteLevel = glGetUniformLocation(program,"whiteLevel");
    glUniform1f(whiteLevel,0);

    modelMatrix = glGetUniformLocation(program,"modelMatrix");
    viewMatrix = glGetUniformLocation(program,"viewMatrix");
    projectMatrix = glGetUniformLocation(program,"projectMatrix");

    __android_log_print(ANDROID_LOG_WARN,TAG,"%s""%d","modelMatrix:",modelMatrix);
    __android_log_print(ANDROID_LOG_WARN,TAG,"%s""%d","viewMatrix:",viewMatrix);
    __android_log_print(ANDROID_LOG_WARN,TAG,"%s""%d","projectMatrix:",projectMatrix);

    initBufferData();
    initTexture();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_drawFrame(JNIEnv *env, jclass clazz) {

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glEnableVertexAttribArray(position);
//    __android_log_print(ANDROID_LOG_WARN,TAG,"%d", sizeof(Vertices));
//    __android_log_print(ANDROID_LOG_ERROR,TAG,"%d", sizeof(vertices));
    glVertexAttribPointer(position,4,GL_FLOAT, false,sizeof(Vertices),0);

    glUniformMatrix4fv(modelMatrix,1,GL_FALSE,glm::value_ptr(model));
    glUniformMatrix4fv(viewMatrix,1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(projectMatrix,1,GL_FALSE,glm::value_ptr(project));

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_learnopengles_nativeutils_GL30ES_drawFrameData(JNIEnv *env, jclass clazz, jint width,
                                                            jint height, jobject data_buffer) {
        __android_log_print(ANDROID_LOG_ERROR,TAG,"%d,%d", width,height);
    //背面剔除
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);

    void* data = env->GetDirectBufferAddress(data_buffer);
    glUseProgram(program);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(position,4,GL_FLOAT,GL_FALSE,sizeof(Vertices),(void *)(sizeof(float)*2));
    glEnableVertexAttribArray(position);
    //float占4个字节。前面有一个position由4个float点组成。数据在内存中是连续的。一个float点在内存中占4位，4个点为4*4位。
    //所以要获取texture的点要后移4*4的内存地址才能获取texture的内存位置。

    glVertexAttribPointer(a_texture,2,GL_FLOAT,GL_FALSE,sizeof(Vertices),0);
    glEnableVertexAttribArray(a_texture);
    glUniform1f(whiteLevel,0);
    glUniformMatrix4fv(modelMatrix,1,GL_FALSE,glm::value_ptr(model));
    glUniformMatrix4fv(viewMatrix,1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(projectMatrix,1,GL_FALSE,glm::value_ptr(project));

    glBindTexture(GL_TEXTURE_2D,texture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
//    glLineWidth(10);

//    glDrawArrays(GL_LINE_LOOP,0,4);
    glBindTexture(GL_TEXTURE_2D,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glUseProgram(0);
}