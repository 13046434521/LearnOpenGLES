#include "utils.h"

unsigned char *loadContentFiles(AAssetManager *assetManager, const char *path) {
    unsigned char *content = nullptr;

    int flieSize = 0;
    AAsset *aAsset = AAssetManager_open(assetManager, path, AASSET_MODE_UNKNOWN);
    if (aAsset != nullptr) {
        flieSize = AAsset_getLength(aAsset);
        content = new unsigned char[flieSize];
        AAsset_read(aAsset, content, flieSize);
        AAsset_close(aAsset);
    }

    return content;
}

GLuint compileShader(GLenum shaderType, char *content) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &content, nullptr);
    glCompileShader(shader);
    GLint compile_ret = GL_FALSE;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ret);
    if (compile_ret==GL_FALSE) {
        char result[1024] = {0};
        GLsizei logSize = 0;
        glGetShaderInfoLog(shader, 1024, &logSize, result);
        __android_log_print(ANDROID_LOG_WARN, TAG, "%c", *result);

        glDeleteShader(shader);
    }
    return shader;
}

GLuint createProgram(GLuint vertexShader,GLuint fragmentShader){
    GLuint program = glCreateProgram();
    glUseProgram(program);
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);

    return program;
}