//# version 300 es
precision mediump float;
varying vec4 u_TextureCoord;
uniform sampler2D u_Texture;
//out vec4 fragColor;
void main(){
    gl_FragColor = texture2D(u_Texture,u_TextureCoord.st);
}