#version 100

attribute vec4 a_Position;
uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform mat4 u_mvpMatrix;
void main() {
//    gl_Position = u_ProjectionMatrix*u_ViewMatrix*u_ModelMatrix*a_Position;
    gl_Position = u_mvpMatrix*a_Position;
}
