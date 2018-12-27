#version 330

precision mediump float;
 uniform sampler2D uTex;
 varying vec4 vTexCoord;

 void main() {
     if (texture2D(uTex, vTexCoord.xy).z < vTexCoord.z)
         gl_FragColor = vec4(0.2, 0.2, 0.2, 1.0);
     else
         gl_FragColor = vec4(0.7, 0.7, 0.7, 1.0);
 }