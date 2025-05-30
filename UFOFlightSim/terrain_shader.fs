#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D terrainTexture; // Added this uniform for the terrain texture
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
// uniform vec3 objectColor; // We will use the texture color instead

void main()
{
    // Sample the terrain texture to get its color
    vec4 texColor = texture(terrainTexture, TexCoord);

    // Ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.4;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine lighting components and multiply by the texture color
    vec3 result = (ambient + diffuse + specular) * texColor.rgb; // Use texColor.rgb here
    FragColor = vec4(result, 1.0);
}
