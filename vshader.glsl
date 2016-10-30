attribute vec4 vPosition;

varying vec4 fcolor;

uniform mat4 model_view;
uniform mat4 projection;
uniform vec4 vcolor;

void main() 
{
   gl_Position = projection*model_view*vPosition;

   fcolor = vcolor;
} 
