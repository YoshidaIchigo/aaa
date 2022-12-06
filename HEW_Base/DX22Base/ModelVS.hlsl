struct VS_IN {
	float3 pos:POSITION;
	float2 uv:TEXCOORD;
};
struct VS_OUT {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD;
};
cbuffer WVP:register(b0){
	float4x4 world;//ワールド変換行列
	float4x4 view;//ビュー行列
	float4x4 proj;//プロジェクション行列
};

VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	return vout;
}