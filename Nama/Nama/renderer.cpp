#include "renderer.h"

Renderer::Renderer()
{
	m_meshes = new vector<Mesh*>();
	m_activeCamera = NULL;
	cout << "Renderer have been initialized." << endl;
}

Renderer::~Renderer()
{
}

void Renderer::Render()
{

	if( m_activeCamera == NULL )
		cout << "No camera is found!" << endl;

	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );
	glEnable( GL_ALPHA_TEST );
	glAlphaFunc ( GL_GREATER, 0 ) ;

	glEnable( GL_TEXTURE_2D );

	glClearColor( 0, 0, 0, 0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45, 1.33, 1, 1000 );



	//glOrtho(0, 800, 0, 600, -100, 100 );

	//gluLookAt( -10, 10, -10, 0, 0, 0, 0, 1, 0 );
	//glTranslatef(0,0,10);
	//glRotatef(180, 0,1,0);

  	glMatrixMode( GL_MODELVIEW );

	//glTranslatef(0,0,-10);
	//glLoadIdentity();
	//glTranslatef( -400, -300, -800 );

	Transform cameraTransform = *m_activeCamera->m_gameObject->GetTransform();
	cameraTransform.Rotate( 180, 1 );
	Matrix4 view = cameraTransform.m_transformationMatrix.GetInverse();
	glLoadMatrixf( view.GetGLMatrix() );

	for( int i = 0; i < m_meshes->size(); i++ )
	{
		if( m_meshes->at( i )->IsEnabled() )
		{
			Mesh* m = m_meshes->at( i );
			Transform* t = m->GetGameObject()->GetTransform();
			Vector3 p = t->m_position;
			Vector3 r = t->m_rotation;
			Vector3 s = t->m_scale;

			Material* mat = m_meshes->at( i )->m_material;
			Texture *tex = mat->m_texture;

			if( tex )
				glBindTexture( GL_TEXTURE_2D, tex->m_id );

			glPushMatrix();

			glTranslatef( p.x, p.y, p.z );
			glScalef( s.x, s.y, 1 );
			glRotatef( r.z, 0, 0, 1  );

			if( !tex )
				glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			else
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			// HACK

			glLineWidth( 2 );

			float ux1 = 0;
			float ux2 = 1;

			float uy1 = 0;
			float uy2 = 1;

			if( tex  && m->m_activeUVAnimationClip )
			{
				if( m->m_isPlaying )
					m->m_animationTime += Game::GetInstance()->GetDeltaTime() * m->m_animationSpeed;

				if( m->m_animationTime > 1 )
				{
					if( m->m_activeUVAnimationClip->mode == 0)
						m->m_animationTime = 0;
					else
					{
						m->m_animationTime = 0.9999; // HACKKKKKKKK , exact value 1 overflows as expected. [0,1) kinda thing
					}
				}


				int totalframeCount = m->m_activeUVAnimationClip->m_endFrame - m->m_activeUVAnimationClip->m_startFrame + 1;
				int frameNo = m->m_animationTime * totalframeCount + m->m_activeUVAnimationClip->m_startFrame;
			


				int hor = frameNo % m->m_horizontalTileCount;
				int ver = frameNo / m->m_horizontalTileCount;

				float verStep = 1.0 / m->m_verticalTileCount;
				float horStep = 1.0 / m->m_horizontalTileCount;

				ux1 = horStep * hor;
				ux2 = horStep + ux1;

				uy1 = verStep * ver;
				uy2 = verStep + uy1;

				// cout << uy2 << endl;
			}

			glColor4f( mat->m_diffuseColor.x, mat->m_diffuseColor.y, mat->m_diffuseColor.z, 1 );
			glBegin( GL_QUADS );
			glTexCoord2f(ux1, uy1); glVertex3f( -0.5, -0.5, 0 );
			glTexCoord2f(ux2, uy1); glVertex3f( 0.5 , -0.5, 0 );
			glTexCoord2f(ux2, uy2); glVertex3f( 0.5, + 0.5, 0 );
			glTexCoord2f(ux1, uy2); glVertex3f( -0.5, + 0.5, 0 );
			glEnd();

			 // DEBUG STUFF
			glTranslatef(0,0,1);
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

			glBindTexture( GL_TEXTURE_2D, 0 );

			glColor4f( 0, 0.8, 0.2, 1 );

			glBegin( GL_LINE_LOOP );

			//for( int i = 0; i < 36; ++i )
				//glVertex3f( cos( (float)i*10*0.0174532925)*0.25, sin((float)i*10*0.0174532925)*0.25, 0 );

			//glVertex3f( -0.5, -0.5, 0 );
			//glVertex3f( 0.5 , -0.5, 0 );
			//glVertex3f( 0.5, + 0.5, 0 );
			//glVertex3f( -0.5, + 0.5, 0 );
			glEnd();

			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			// DEBUG STUFF ENDS

			glPopMatrix();
		}
	}
}

void Renderer::RegisterComponent( Component* component )
{
	if( dynamic_cast<Mesh*>( component ) )
		m_meshes->push_back( dynamic_cast<Mesh*>( component ) );
	else if( dynamic_cast<Camera*>( component ) )
		m_activeCamera = dynamic_cast<Camera*>( component );
}

void Renderer::UnregisterComponent( Component* component )
{
	for( int i = 0; i < m_meshes->size(); i++ )
	{
		if( m_meshes->at( i ) == component )
		{
			m_meshes->erase( m_meshes->begin() + i );
			break;
		}
	}
}

Renderer* Renderer::GetInstance()
{
	if( renderer == NULL )
		renderer = new Renderer();

	return renderer;
}

Renderer* Renderer::renderer = NULL;