uniform float uTime;
uniform float uXmin, uXmax;
uniform float uYmin, uYmax;
uniform float uPeriodx, uPeriody;
uniform int uNumx, uNumy;

const float TWOPI = 2 * 3.14159265;

void main()
{
    int ix = gl_InstanceID % uNumx;
    int iy = gl_InstanceID / uNumx;

    float x = uXmin + float(ix) * (uXmax - uXmin) / float(uNumx - 1);
    float y = uYmin + float(iy) * (uYmax - uYmin) / float(uNumy - 1);

    vec4 vert = vec4(x, y, glVertex.zw);

    gl_Position = gl_ModelViewProjectionMatrix * vert;
}