#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D container;
uniform sampler2D awesomeface;
uniform float textureRatio;

void main() {
	FragColor = mix(texture(container, texCoord), texture(awesomeface, texCoord ), textureRatio);
}
