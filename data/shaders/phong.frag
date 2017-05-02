#version 140

#extension GL_ARB_explicit_attrib_location : require

in vec4 v_position;
in vec4 v_normal;
out vec4 fragColour;

struct material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 specularPower;
    vec3 specularScale;
};

uniform material u_material;

struct light {
    vec3 position;
    vec3 falloff;
    vec3 colour;
    float ambientCoefficient;
    float diffuseCoefficient;
    float specularCoefficient;
};

uniform light lights[8];
uniform int lightCount; // number of lights in use

uniform vec3 u_cameraPos;

void main() {
    vec3 normal = normalize(v_normal).xyz;
    vec3 toCamera = normalize(u_cameraPos - v_position.xyz);

    vec3 ace = vec3(0.0f,0.0f,0.0f);
    vec3 dce = vec3(0.0f,0.0f,0.0f);
    vec3 sce = vec3(0.0f,0.0f,0.0f);

    for(int i = 0; i < lightCount; i ++) {
        ace += lights[i].colour * lights[i].ambientCoefficient*2;
        vec3 toLight = normalize(lights[i].position - v_position.xyz);
        float normal_coefficient = max(0.0f, dot(v_normal.xyz, toLight));
        dce += normal_coefficient * lights[i].colour * lights[i].diffuseCoefficient*2;
        
        float spec_coefficient = pow(
            max(0.0f, dot(toCamera, normalize(reflect(-toLight, v_normal.xyz)))),
            //max(0.0f, dot(toCamera, normal.xyz)),
            u_material.specularPower.x);
        sce += spec_coefficient * lights[i].colour * lights[i].specularCoefficient;
    }

    // clamp coefficients
    ace = clamp(ace, vec3(0.0f,0.0f,0.0f), vec3(1.0f,1.0f,1.0f));
    dce = clamp(dce, vec3(0.0f,0.0f,0.0f), vec3(1.0f,1.0f,1.0f));
    sce = clamp(sce, vec3(0.0f,0.0f,0.0f), vec3(1.0f,1.0f,1.0f));

    fragColour = vec4(
        clamp(ace*u_material.ambient + dce*u_material.diffuse + sce*u_material.specular, vec3(0.0,0.0,0.0), vec3(1.0,1.0,1.0)),
        1.0f
    );
}
