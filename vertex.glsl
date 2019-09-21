#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;

void main(void)
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
