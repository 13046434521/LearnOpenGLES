precision mediump float;
varying vec2 vTexCoord;
uniform sampler2D uTextureSampler;
uniform float whiteLevel;


void main() {
//    gl_FragColor = vec4(1.0,0.0,0.0,1.0);
    float factor = 0.1;

    vec4 color = texture2D(uTextureSampler,vTexCoord);

    color.r += factor * whiteLevel;
    color.g += factor * whiteLevel;
    color.b += factor * whiteLevel;

    gl_FragColor = color;
}