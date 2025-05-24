#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float visibility;

//ufo top: 0, ufo bottom is 1
uniform int type;

void main()
{
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x, TexCoord.y)), 0.2) * vec4(ourColor, 1.0);

    if (type == 0){

        //cyan
        FragColor = vec4(0.25f, 0.93f, 0.95f, 1.0f);


    } else if (type == 1){
        //metallic gray

        FragColor = vec4(0.21f,0.21f,0.21f, 1.0f);
            
        
    } else if (type == 2){

        FragColor = vec4(0.2f, 0.3f, 0.3f, 1.0f);


    } else {

        FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x, TexCoord.y)), visibility);

    }
    

    //FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);

}