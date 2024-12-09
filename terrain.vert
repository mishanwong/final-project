varying vec3 vN; // surface normal vector
varying vec3 vL; // vector from point to light
varying vec3 vE; // vector from point to eye

void main() {
    vec3 vert = gl_Vertex.xyz;
    vN = 

    // Write vN, vL, vE;
    gl_Position = gl_ModelViewProjectionMatrix * vec4( vert, 1. );
}