#version 120

attribute vec3 position;
attribute vec2 textureCoordinates;
varying vec2 _textureCoordinates;

void main()
{
    _textureCoordinates = textureCoordinates;
    gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 1.0);
}

