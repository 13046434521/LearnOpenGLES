precision mediump float;
varying vec2 vTexCoord;
uniform sampler2D uTextureSampler;
uniform float whiteLevel;


void main() {
    //    gl_FragColor = vec4(1.0,0.0,0.0,1.0);
    float factor = 0.1;

    vec4 color = texture2D(uTextureSampler, vTexCoord);
    vec4 haha ;
    float offest_position=0.5;
    float offest_x=0.5;
    float offest_y=0.5;
    float blur = 0.005;
    if(vTexCoord.x>offest_position-offest_x&&vTexCoord.x<offest_position+offest_x&&vTexCoord.y>offest_position-offest_y&&vTexCoord.y<offest_position+offest_y){
        vec4 color1 =  texture2D(uTextureSampler, vec2(vTexCoord.x+blur,vTexCoord.y+blur));
        vec4 color2 =  texture2D(uTextureSampler, vec2(vTexCoord.x+blur,vTexCoord.y-blur));
        vec4 color3 =  texture2D(uTextureSampler, vec2(vTexCoord.x-blur,vTexCoord.y+blur));
        vec4 color4 =  texture2D(uTextureSampler, vec2(vTexCoord.x-blur,vTexCoord.y-blur));

        haha = (color1+color2+color3+color4);
        color = vec4(haha.x/4.0,haha.y/4.0,haha.z/4.0,haha.a);
    }
//    color.r += factor * whiteLevel;
//    color.g += factor * whiteLevel;
//    color.b += factor * whiteLevel;

//    float avg = (color.r + color.g + color.b)/3.0;
//    color = vec4(avg, avg, avg, 1.0);

//    if(color.r>0.5){
//        color.r = 1.0;
//    }else{
//        color.r = 0.0;
//    }
//    if(color.b>0.5){
//        color.b = 1.0;
//    }else{
//        color.b = 0.0;
//    }
//    if(color.g>0.5){
//        color.g = 1.0;
//    }else{
//        color.g = 0.0;
//    }
//    gl_FragColor = vec4(color.r,color.g,color.b,color.a);

    gl_FragColor = color;
}