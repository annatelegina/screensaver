#version 330 core

out vec4 color;
uniform vec3 c;

void main()
{

    color = vec4(c, 1.0f);
}
