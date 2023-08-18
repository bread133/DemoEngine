#version 330 core
// Интерполированные значения из вершинного шейдера
in vec3 fragment_color;
// Выходные данные
out vec3 color;

void main(){
    color = fragment_color;
}