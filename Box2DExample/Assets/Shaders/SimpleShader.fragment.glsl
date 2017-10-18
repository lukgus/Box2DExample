#version 400

layout ( location = 0 ) out vec4 out_Colour;

in vec4 ex_Position;
in vec4 ex_PositionWorld;
in vec4 ex_Normal;
in vec4 ex_UV_x2;

uniform vec3 colour;
struct LightDesc
{
	vec3 position;
// vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float attenConst;
	float attenLinear;
	float attenQuad;
};

uniform LightDesc MyLight;

struct MaterialDesc
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform MaterialDesc MyMaterial;

uniform vec3 eye;

vec3 ADSLightModel( in vec3 Normal, 
					in vec3 Position, 
                    in int LightIndex );

void main(void)
{
	vec3 LightContribution = ADSLightModel(ex_Normal.xyz, ex_PositionWorld.xyz, 0);
	out_Colour = vec4(colour * LightContribution, 1.0f);
	return;
}

vec3 ADSLightModel( in vec3 Normal, 
					in vec3 Position, 
                    in int LightIndex )
{
	// normal, light, view, and light reflection vectors
	vec3 norm = 	normalize( Normal );
	vec3 lightv = 	normalize( MyLight.position - Position);
	vec3 viewv = 	normalize( eye - Position );
	vec3 refl = 	-(reflect( lightv, norm ));

	// ambient light computation
	vec3 ambient = MyLight.ambient // MyLightAmbient
					* MyMaterial.ambient;
	
	// diffuse light computation
	vec3 diffuse = max(0.0f, dot(lightv, norm))
                   * MyLight.diffuse // myLightDiffuse;
				   * MyMaterial.diffuse;
				   
	// Optionally you can add a diffuse attenuation term at this point
	//float dist = distance( ex_Position, sunLight.position );	
	float dist = distance( Position, MyLight.position );	
	float atten = 1.0f /( MyLight.attenConst + 
	                      MyLight.attenLinear * dist +
						  MyLight.attenQuad * dist * dist );
						  
	diffuse *= atten;
	
	// specular light computation
	vec3 specular = vec3( 0.0f, 0.0f, 0.0f );	
	if( dot(lightv, norm) > 0.0f )
	{
		specular = pow( max(0.0f, dot(viewv,refl)), MyMaterial.shininess)
					* MyLight.specular // myLightSpecular;
					 * MyMaterial.specular;
		specular *= atten;
	}
	
	return clamp( ambient + diffuse + specular, 0.0f, 1.0f );
}
