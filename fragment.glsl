#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform int t;
void main()
{
    if (t == 1)
        FragColor = texture(texture1, TexCoord);
    else
        FragColor = texture(texture2, TexCoord);
}
