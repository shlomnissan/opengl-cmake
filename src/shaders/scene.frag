#version 410 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D u_TextureMap;

void main() {
    FragColor = texture(u_TextureMap, v_TexCoord);
}