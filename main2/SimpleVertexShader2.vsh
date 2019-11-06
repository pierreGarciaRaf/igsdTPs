#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor_modelspace;
layout(location = 2) in mat4 matvertexPosition;
// Sortie
uniform mat2 rsM;

smooth out vec3 colort;

void main(){
  gl_Position = vec4(rsM * vertexPosition_modelspace.xy,1,1) ;
  
  colort    = vertexColor_modelspace;
}