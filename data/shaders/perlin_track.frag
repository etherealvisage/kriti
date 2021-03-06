#version 140

const float pi = 3.14159265;

uniform int g_time;

in vec4 v_position;
in vec4 v_normal;
in vec2 v_tex;
out vec4 fragColour;

vec4 mod289(vec4 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0; }

float mod289(float x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0; }

vec4 permute(vec4 x) {
     return mod289(((x*34.0)+1.0)*x);
}

float permute(float x) {
     return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
  return 1.79284291400159 - 0.85373472095314 * r;
}

float taylorInvSqrt(float r)
{
  return 1.79284291400159 - 0.85373472095314 * r;
}

vec4 grad4(float j, vec4 ip)
  {
  const vec4 ones = vec4(1.0, 1.0, 1.0, -1.0);
  vec4 p,s;

  p.xyz = floor( fract (vec3(j) * ip.xyz) * 7.0) * ip.z - 1.0;
  p.w = 1.5 - dot(abs(p.xyz), ones.xyz);
  s = vec4(lessThan(p, vec4(0.0)));
  p.xyz = p.xyz + (s.xyz*2.0 - 1.0) * s.www; 

  return p;
  }
						

#define F4 0.309016994374947451

float snoise(vec4 v)
  {
  const vec4  C = vec4( 0.138196601125011,
                        0.276393202250021,
                        0.414589803375032,
                       -0.447213595499958);


  vec4 i  = floor(v + dot(v, vec4(F4)) );
  vec4 x0 = v -   i + dot(i, C.xxxx);




  vec4 i0;
  vec3 isX = step( x0.yzw, x0.xxx );
  vec3 isYZ = step( x0.zww, x0.yyz );

  i0.x = isX.x + isX.y + isX.z;
  i0.yzw = 1.0 - isX;

  i0.y += isYZ.x + isYZ.y;
  i0.zw += 1.0 - isYZ.xy;
  i0.z += isYZ.z;
  i0.w += 1.0 - isYZ.z;


  vec4 i3 = clamp( i0, 0.0, 1.0 );
  vec4 i2 = clamp( i0-1.0, 0.0, 1.0 );
  vec4 i1 = clamp( i0-2.0, 0.0, 1.0 );

  vec4 x1 = x0 - i1 + C.xxxx;
  vec4 x2 = x0 - i2 + C.yyyy;
  vec4 x3 = x0 - i3 + C.zzzz;
  vec4 x4 = x0 + C.wwww;


  i = mod289(i); 
  float j0 = permute( permute( permute( permute(i.w) + i.z) + i.y) + i.x);
  vec4 j1 = permute( permute( permute( permute (
             i.w + vec4(i1.w, i2.w, i3.w, 1.0 ))
           + i.z + vec4(i1.z, i2.z, i3.z, 1.0 ))
           + i.y + vec4(i1.y, i2.y, i3.y, 1.0 ))
           + i.x + vec4(i1.x, i2.x, i3.x, 1.0 ));



  vec4 ip = vec4(1.0/294.0, 1.0/49.0, 1.0/7.0, 0.0) ;

  vec4 p0 = grad4(j0,   ip);
  vec4 p1 = grad4(j1.x, ip);
  vec4 p2 = grad4(j1.y, ip);
  vec4 p3 = grad4(j1.z, ip);
  vec4 p4 = grad4(j1.w, ip);

  vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
  p0 *= norm.x;
  p1 *= norm.y;
  p2 *= norm.z;
  p3 *= norm.w;
  p4 *= taylorInvSqrt(dot(p4,p4));


  vec3 m0 = max(0.6 - vec3(dot(x0,x0), dot(x1,x1), dot(x2,x2)), 0.0);
  vec2 m1 = max(0.6 - vec2(dot(x3,x3), dot(x4,x4)            ), 0.0);
  m0 = m0 * m0;
  m1 = m1 * m1;
  return clamp(49.0 * ( dot(m0*m0, vec3( dot( p0, x0 ), dot( p1, x1 ), dot( p2, x2 )))
               + dot(m1*m1, vec2( dot( p3, x3 ), dot( p4, x4 ) ) ) ) , -1.0f, 1.0f);

  }

void main() {
    // components: edge blending, internal colouring, edge highlighting.

    // edge colours
    const vec4 edge_normal = vec4(0.05f, 0.7f, 0.1f, 1.0f);
    const vec4 edge_highlight = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    // edge distance
    float edist = clamp(pow(max(cos(v_tex.x*2*pi), 0), 2.0f), 0.0f, 1.0f);

    const float highlight_speed = 1.0f;
    const float highlight_interval = 250.0f;
    float highlight_z = -mod(g_time / highlight_speed, highlight_interval);
    float abs_p = -mod(-v_position.z, highlight_interval);
    float d = mod(abs(abs_p - highlight_z), highlight_interval);
    d = min(d/8.0f, pi);
    float highlight_mix = cos(d);

    vec4 edge = mix(edge_normal, edge_highlight, highlight_mix);

    const float internal_speed = 1000.0f;
    float ivalue = snoise(vec4(v_position.xyz, g_time / internal_speed));

    const vec4 pos_internal = vec4(0.1f, 0.0f, 0.9f, 1.0f);
    const vec4 neg_internal = vec4(0.9f, 0.1f, 0.1f, 1.0f);

    vec4 internal;
    if(ivalue > 0) internal = ivalue * pos_internal;
    else internal = -ivalue * neg_internal;

    float id = distance(-g_time / 100.0f, v_position.z);
    id = min(id, pi);
    id = cos(id);

    float idvalue = abs(snoise(vec4(v_position.xyz,
        g_time / internal_speed + 0.1f)));

    //internal += id * vec4(idvalue, idvalue, idvalue, 0.0f);

    fragColour = mix(internal, edge, edist);
    fragColour.a = 1.0f;

    /*vec4 highlight = mix(normal_highlight, active_highlight, highlight_mix);
    fragColour = mix(vec4(0.05f, 0.05f, 0.1f, 1.0f), highlight, trans);
    
    // yellow centre line
    fragColour = mix(
        fragColour,
        vec4(1.0f, 1.0f, 0.0f, 1.0f),
        cos(min(pi, distance(v_tex.x, 0.5f)*20.0f)));*/
}
