#version 120

uniform sampler2D theTexture;
varying vec2 _textureCoordinates;

void main()
{
    gl_FragColor = texture2D(theTexture, _textureCoordinates);
	//gl_FragColor = vec4(_textureCoordinates, 0.0, 1.0);
}
