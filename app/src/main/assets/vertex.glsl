attribute vec4 aPosition;
attribute vec2 aTexCoord;
varying vec2 vTexCoord;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;
void main() {
    vTexCoord = aTexCoord;
    vec4 postion = projectMatrix * viewMatrix * modelMatrix * aPosition;
    gl_Position = vec4(postion.x,postion.y,postion.z,postion.a);
}