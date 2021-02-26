attribute vec4 aPosition;
attribute vec2 aTexCoord;
varying vec2 vTexCoord;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;
void main() {
    vTexCoord = aTexCoord;
    gl_Position = projectMatrix * viewMatrix * modelMatrix * aPosition;
}