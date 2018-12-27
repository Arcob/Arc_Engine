#version 330

precision mediump float;
attribute vec4 aPosition;
uniform mat4 uMvp;
uniform mat4 uShadowMvp;
varying vec4 vTexCoord;

void main() {
    gl_Position = uMvp*aPosition;
    vTexCoord = uShadowMvp * aPosition;
}