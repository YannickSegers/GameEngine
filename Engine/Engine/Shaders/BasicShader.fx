//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

cbuffer cbWorldViewProjection : register( b0 )
{
	matrix m_World : World;
    matrix m_View : View;
    matrix m_Projection :Projection;
};

RasterizerState DisableCulling { CullMode = NONE; };

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( input.Pos, m_World );
    output.Pos = mul( output.Pos, m_View );
    output.Pos = mul( output.Pos, m_Projection );
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input) : SV_Target
{
    return float4( 0.7f, 0.2f, 0.2f, 1.0f );
}

// Default Technique
technique10 DefaultTechnique {
	pass p0 {
		SetRasterizerState(DisableCulling);	
		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetPixelShader(CompileShader(ps_4_0, PS()));
	}
}



