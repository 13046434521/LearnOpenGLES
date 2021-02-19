attribute vec4 a_Position;
attribute vec4 a_TextureCoord;
uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform mat4 u_mvpMatrix;
varying vec4 u_TextureCoord;
void main() {
//    gl_Position = u_ProjectionMatrix*u_ViewMatrix*u_ModelMatrix*a_Position;
//    gl_Position = u_mvpMatrix*a_Position;
    u_TextureCoord = a_TextureCoord;
    gl_Position = a_Position;
}
