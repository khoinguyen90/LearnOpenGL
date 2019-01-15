#version 330 core
precision mediump float;
in vec4 TriangleColor;
out vec4 FragColor;
void main() {
    FragColor = TriangleColor;
}
