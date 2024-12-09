uniform float uKa, uKd, uKs; //coefficients of each type of lighting
uniform float uShininess;

varying vec3 vN; // surface normal vector of the current fragment
varying vec3 vL; // vector from current fragment to the light
varying vec3 vE; // vector from current fragment to our eye


void main() {
    vec3 myColor = vec3(0.98, 0.5, 0.45);

    // now do the per-fragment lighting
    vec3 Normal = normalize(vN);
    vec3 Light = normalize(vL);
    vec3 Eye = normalize(vE);

    vec3 ambient = uKa * myColor;

    float d = max(dot(Normal, Light), 0.); //only do diffuse if the light can see the point
    vec3 diffuse = uKd * d * myColor;
    const vec3 SPECULARCOLOR = vec3( 1., 1., 1. );

    float s = 0.;
    if (d > 0.) { // only do specular if the light can see the point
        vec3 ref = normalize(reflect(-Light, Normal)); // perfect reflection vector
        float cosphi = dot(Eye, ref);
        if (cosphi > 0.) {
            s = pow(max(cosphi, 0.), uShininess);
        }
    }

    vec3 specular = uKs * s * SPECULARCOLOR.rgb;
    gl_FragColor = vec4( ambient + diffuse + specular, 1. );
}