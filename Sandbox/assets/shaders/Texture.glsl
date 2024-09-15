#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCoord;
layout(location = 3) in float a_texID;

uniform mat4 u_viewProjection;

out vec2 v_texCoord;
out vec4 v_color;
out float v_texID;

void main() {
    v_color = a_color;
    v_texCoord = a_texCoord;
    v_texID = a_texID;
    gl_Position = u_viewProjection * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
in vec4 v_color;
in float v_texID;

uniform vec4 u_color;
uniform float u_tilingFactor;
uniform sampler2D u_textures[16];

void main() {
    int index = int(v_texID);

    switch (index) {
    case 0:
        color = texture(u_textures[0], v_texCoord) * v_color;
        break;
    case 1:
        color = texture(u_textures[1], v_texCoord) * v_color;
        break;
     case 2:
        color = texture(u_textures[2], v_texCoord) * v_color;
        break;
    case 3:
        color = texture(u_textures[3], v_texCoord) * v_color;
        break;
    case 4:
        color = texture(u_textures[4], v_texCoord) * v_color;
        break;
    case 5:
        color = texture(u_textures[5], v_texCoord) * v_color;
        break;
    case 6:
        color = texture(u_textures[6], v_texCoord) * v_color;
        break;
    case 7:
        color = texture(u_textures[7], v_texCoord) * v_color;
        break;
    case 8:
        color = texture(u_textures[8], v_texCoord) * v_color;
        break;
    case 9:
        color = texture(u_textures[9], v_texCoord) * v_color;
        break;
    case 10:
        color = texture(u_textures[10], v_texCoord) * v_color;
        break;
    case 11:
        color = texture(u_textures[11], v_texCoord) * v_color;
        break;
    case 12:
        color = texture(u_textures[12], v_texCoord) * v_color;
        break;
    case 13:
        color = texture(u_textures[13], v_texCoord) * v_color;
        break;
    case 14:
        color = texture(u_textures[14], v_texCoord) * v_color;
        break;
    case 15:
        color = texture(u_textures[15], v_texCoord) * v_color;
        break;
    default:
        color = vec4(1.0);
        break;
    }
    // float normalizedIndex = float(index) / 15.0;  // Assuming 16 textures max
    // color = vec4(normalizedIndex, 0.0, 0.0, 1.0);  // Red channel visualizes the index


}