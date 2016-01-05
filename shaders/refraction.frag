#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D refraction;
uniform sampler2D background;
uniform vec2 position;
uniform int radius;

varying vec2 v_texcoord;

void main()
{
    if(texture2D(refraction, v_texcoord).a == 0.f) discard;

    vec2 rv = v_texcoord - vec2(0.5);
    float R = float(radius);
    rv *= 2.f * R;

    float n = 1.8;

    float k = texture2D(refraction, v_texcoord).r;
    //transform k from {0, 1} to {1/n, 1}
    k = ((n - 1.f) * k + 1.f) / n;

    vec2 r_refr = k * rv;

    vec2 bg_texcoord = position + r_refr;
    vec2 window = vec2(1300.f, 650.f);
    bg_texcoord += window / 2.f;
    bg_texcoord /= window;

    gl_FragColor = texture2D(background, bg_texcoord);
}
