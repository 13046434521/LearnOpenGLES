precision mediump float;
varying vec2 vTexCoord;
uniform sampler2D uTextureSampler;
uniform float whiteLevel;


void main() {
    //    gl_FragColor = vec4(1.0,0.0,0.0,1.0);
    float factor = 0.1;

    vec4 color = texture2D(uTextureSampler, vTexCoord);

//    color.r += factor * whiteLevel;
//    color.g += factor * whiteLevel;
//    color.b += factor * whiteLevel;

//    float avg = (color.r + color.g + color.b)/3.0;
//    color = vec4(avg, avg, avg, 1.0);

    if(color.r>0.5){
        color.r = 1.0;
    }else{
        color.r = 0.0;
    }
    if(color.b>0.5){
        color.b = 1.0;
    }else{
        color.b = 0.0;
    }
    if(color.g>0.5){
        color.g = 1.0;
    }else{
        color.g = 0.0;
    }
//    gl_FragColor = vec4(color.r,color.g,color.b,color.a);

    gl_FragColor = color;
}