#include "GeometryMesh.h"
#include "Engine.h"
#include "RenderData.h"
#include "Camera.h"


GeometryMesh::GeometryMesh()
	:m_pGeometryTriangles(0)
	//,m_pCBWorldViewProjection(0)
{
	//Initialize();
	//m_pCBWorldViewProjection = new CBWorldViewProjection();
	
}

GeometryMesh::~GeometryMesh()
{
	//D3DD11_DELETE_AND_CLEAN(m_pGeometryTriangles);
	//D3DD11_DELETE_AND_CLEAN(m_pCBWorldViewProjection);
}


void GeometryMesh::Initialize()
{
	XMMATRIX identity = XMMatrixTranspose(XMMatrixIdentity());
	XMStoreFloat4x4(&m_World,identity);
	CreateGeometry();
	InitializeBuffers();

	// Initialize the projection matrix
	//XMMATRIX projection = XMMatrixPerspectiveFovLH( XM_PIDIV4, ENGINE->GetDevice()->GetWidth() / (FLOAT)ENGINE->GetDevice()->GetHeight(), 0.01f, 100.0f ); 
	
    /*CBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = XMMatrixTranspose( projection );*/
	/*CBWorldViewProjection cBWorldViewProjection;
	cBWorldViewProjection.mProjection = XMMatrixTranspose( projection );*/
    //ENGINE->GetDevice()->GetImmediateContext()->UpdateSubresource( m_GeometryBuffers.m_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0 );
	

	 // Initialize the view matrix
	//XMMATRIX view = XMMatrixLookAtLH( EYEVECTOR, ATVECTOR, UPVECTOR );
    /*CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = XMMatrixTranspose( view );*/
	//cBWorldViewProjection.mView = XMMatrixTranspose( view );
	//ENGINE->GetDevice()->GetImmediateContext()->UpdateSubresource( m_GeometryBuffers.m_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0 );

	//ENGINE->GetDevice()->GetImmediateContext()->UpdateSubresource( m_GeometryBuffers.m_pCBWorldViewProjection, 0, NULL, &cBWorldViewProjection, 0, 0 );
}

void GeometryMesh::Update()
{
	//Calculate World Matrix
	XMMATRIX world = XMMatrixRotationRollPitchYaw( 0.0f, 0.0f, 0.0f ); //pitch, yaw, roll

	world.m[3][0] = 0.0f; //xpos
	world.m[3][1] = 0.0f; //ypos
	world.m[3][2] = 0.0f; //zpos
	world.m[3][3] = 1.0f;

	world = XMMatrixTranspose(world);
	XMStoreFloat4x4(&m_World,world);
	/*CBChangesEveryFrame cb;
	cb.mWorld = XMMatrixTranspose( world );*/
	
}

void GeometryMesh::Render(const RenderData* pRenderData)
{
	//// Set View
	//ENGINE->GetDevice()->GetImmediateContext()->VSSetConstantBuffers( 0, 1, &m_GeometryBuffers.m_pCBNeverChanges );

	//// Set Projection
	//ENGINE->GetDevice()->GetImmediateContext()->VSSetConstantBuffers( 1, 1, &m_GeometryBuffers.m_pCBChangeOnResize );

	CBWorldViewProjection cBWorldViewProjection;
	cBWorldViewProjection.mWorld = XMMatrixTranspose( XMLoadFloat4x4(&m_World));
	//XMMATRIX projection = XMMatrixPerspectiveFovLH( XM_PIDIV4, ENGINE->GetDevice()->GetWidth() / (FLOAT)ENGINE->GetDevice()->GetHeight(), 0.01f, 100.0f ); 
	XMFLOAT4X4 projection =  pRenderData->GetCamera()->GetProjection();
	cBWorldViewProjection.mProjection = XMMatrixTranspose(XMLoadFloat4x4(&projection));
	
	//XMMATRIX view = XMMatrixLookAtLH( EYEVECTOR, ATVECTOR, UPVECTOR );
	XMFLOAT4X4 view =  pRenderData->GetCamera()->GetView();
	cBWorldViewProjection.mView = XMMatrixTranspose(XMLoadFloat4x4(&view));
	//ENGINE->GetDevice()->GetImmediateContext()->UpdateSubresource( m_GeometryBuffers.m_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0 );
	ENGINE->GetDevice()->GetImmediateContext()->UpdateSubresource( m_GeometryBuffers.m_pCBWorldViewProjection, 0, NULL, &cBWorldViewProjection, 0, 0 );

	//set World, View, Projection
	ENGINE->GetDevice()->GetImmediateContext()->VSSetConstantBuffers( 0, 1, &m_GeometryBuffers.m_pCBWorldViewProjection);
	// Set inputlayout
	ENGINE->GetDevice()->GetImmediateContext()->IASetInputLayout(ENGINE->GetShaderManager()->GetInputLayout(_T("InputLayout")) );
	// Set vertex buffer
    UINT stride = sizeof( m_pGeometryTriangles->GetVertices().at(0) );
    UINT offset = 0;
	ENGINE->GetDevice()->GetImmediateContext()->IASetVertexBuffers( 0, 1, &m_GeometryBuffers.m_pVertexBuffer, &stride, &offset );

	// Set index buffer
    //Engine::GetSingleton()->GetImmediateContext()->IASetIndexBuffer( m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	ENGINE->GetDevice()->GetImmediateContext()->IASetIndexBuffer( m_GeometryBuffers.m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );

    // Set primitive topology
    ENGINE->GetDevice()->GetImmediateContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	ENGINE->GetDevice()->GetImmediateContext()->VSSetShader( ENGINE->GetShaderManager()->GetVertexShader(_T("VertexShader")), NULL, 0 );

	//ENGINE->GetDevice()->GetImmediateContext()->VSSetConstantBuffers( 2, 1, &m_GeometryBuffers.m_pCBChangesEveryFrame );

	ENGINE->GetDevice()->GetImmediateContext()->PSSetShader( ENGINE->GetShaderManager()->GetPixelShader(_T("PixelShader")), NULL, 0 );
	//ENGINE->GetDevice()->GetImmediateContext()->PSSetConstantBuffers( 2, 1, &m_GeometryBuffers.m_pCBChangesEveryFrame );
	ENGINE->GetDevice()->GetImmediateContext()->PSSetConstantBuffers( 0, 1, &m_GeometryBuffers.m_pCBWorldViewProjection);

	ENGINE->GetDevice()->GetImmediateContext()->DrawIndexed( m_GeometryBuffers.m_NumIndices, 0, 0 );

	
}

void GeometryMesh::InitializeBuffers()
{
	HRESULT hr = S_OK;

	if(m_pGeometryTriangles == 0)
	{
		assert("The geometryTrianlges are empty, therefore the buffers could not be created.");
	}
	////////////////////////
	// Create Vertex buffer
	////////////////////////
	UINT numVertices = m_pGeometryTriangles->GetVertices().size();

	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( m_pGeometryTriangles->GetVertices().at(0) ) * numVertices;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory( &InitData, sizeof(InitData) );
	InitData.pSysMem = m_pGeometryTriangles->GetVertices().data();
	hr = ENGINE->GetDevice()->Get3DDevice()->CreateBuffer( &bd, &InitData, &m_GeometryBuffers.m_pVertexBuffer);
	D3DD11_SET_DEGUG_NAME(m_GeometryBuffers.m_pVertexBuffer,"m_pVertexBuffer");
	if( FAILED( hr ) )
	{
		assert("error setting up Vertex buffer");
	}

	////////////////////////
	// Create index buffer
	////////////////////////
	m_GeometryBuffers.m_NumIndices = m_pGeometryTriangles->GetIndices().size();
	D3D11_BUFFER_DESC bdIndices;
	ZeroMemory( &bdIndices, sizeof(bdIndices) );
	bdIndices.Usage = D3D11_USAGE_DEFAULT;
	bdIndices.ByteWidth = sizeof( int ) * m_GeometryBuffers.m_NumIndices;
	bdIndices.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bdIndices.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitIndexData;
	ZeroMemory( &InitIndexData, sizeof(InitIndexData) );
	InitIndexData.pSysMem = m_pGeometryTriangles->GetIndices().data();
	hr = ENGINE->GetDevice()->Get3DDevice()->CreateBuffer( &bdIndices, &InitIndexData, &m_GeometryBuffers.m_pIndexBuffer);
	D3DD11_SET_DEGUG_NAME(m_GeometryBuffers.m_pIndexBuffer,"m_pIndexBuffer");
	if( FAILED( hr ) )
	{
		assert("error setting up Indexbuffer");
	}

	////
	// Create Constant buffers
	///

#if 0
	//Changes Every Frame

    ZeroMemory( &bd, sizeof(bd) );
    // Create the constant buffers
    // initialize memory on target for the specific rendering infos
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CBChangesEveryFrame);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = ENGINE->GetDevice()->Get3DDevice()->CreateBuffer( &bd, NULL, &m_GeometryBuffers.m_pCBChangesEveryFrame );
	D3DD11_SET_DEGUG_NAME(m_GeometryBuffers.m_pCBChangesEveryFrame,"m_pAppElementCBChangesEveryFrame");
	if( FAILED( hr ) )
	{
		assert("error setting up buffer");
	}

	//Never Changes
	//Initialize the Camera Variables
    ZeroMemory( &bd, sizeof(bd) );
	 // Create the constant buffers
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(CBNeverChanges);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = ENGINE->GetDevice()->Get3DDevice()->CreateBuffer( &bd, NULL, &m_GeometryBuffers.m_pCBNeverChanges );
	D3DD11_SET_DEGUG_NAME(m_GeometryBuffers.m_pCBNeverChanges,"m_pCBNeverChanges");
   if( FAILED( hr ) )
	{
		assert("error setting up buffer");
	}

	//ChangesOnResize
    bd.ByteWidth = sizeof(CBChangeOnResize);
    hr = ENGINE->GetDevice()->Get3DDevice()->CreateBuffer( &bd, NULL, &m_GeometryBuffers.m_pCBChangeOnResize );
	D3DD11_SET_DEGUG_NAME(m_GeometryBuffers.m_pCBChangeOnResize,"m_pCBChangeOnResize");
   if( FAILED( hr ) )
	{
		assert("error setting up buffer");
	}
#else
	 ZeroMemory( &bd, sizeof(bd) );
    // Create the constant buffers
    // initialize memory on target for the specific rendering infos
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CBWorldViewProjection);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = ENGINE->GetDevice()->Get3DDevice()->CreateBuffer( &bd, NULL, &m_GeometryBuffers.m_pCBWorldViewProjection );
	D3DD11_SET_DEGUG_NAME(m_GeometryBuffers.m_pCBWorldViewProjection,"m_pAppElementCBWorldViewProjection");
	if( FAILED( hr ) )
	{
		assert("error setting up buffer");
	}
#endif
}
