require "GameData\\Scripts\\Vector2"
require "GameData\\Scripts\\Entity"

texturesFolder = "GameData\\Textures\\"

function Key( keyString )
	return string.byte( keyString )
end

camera = GameObject:Create()
camera:AddCamera()

camera:GetTransform():setPosition(200,200,400)
camera:GetTransform():setRotation(0,180,0)

soldier = Entity:new( GameObject:Create() )
soldier.m:SetMaterialTexture( texturesFolder .. "soldier.tga" )
soldier.m:SetUVAnimation( 4,6 )
soldier.m:CreateUVAnimationClip( "Walk", 0, 20, 0 )
soldier.m:SetUVAnimationClip( "Walk" )
soldier.m:SetUVAnimationSpeed( 2 )
soldier.m:StartUVAnimation()

ch = Entity:new( GameObject:Create() )
ch.m:SetMaterialTexture( texturesFolder .. "crosshair.tga" )
ch.m:SetMaterialColor( 0.5, 1, 1, 1 )
ch.t:setScale( 20, 20, 1 )

grass = Entity:new( GameObject:Create() )
grass.m:SetMaterialTexture( texturesFolder .. "grass.tga" )
grass.t:setPosition( 400, 300, -5 )
grass.t:setScale( 800, 600, 1 )

bullet = Bullet:new( GameObject:Create() )
bullet.speed = 0


function OnUpdate( deltaTime )

	if Input:GetMouseButton( 1 ) then
		soldier.m:StartUVAnimation()
		soldier:move( deltaTime )
	else
		soldier.m:StopUVAnimation()
	end

	bullet.pos = soldier.pos
	bullet:move( deltaTime )

	mousePos = Input:GetMousePosition()
	mousePos = Vector2:new( mousePos.x, mousePos.y )
	soldier:lookAt( mousePos )

	ch.t:setPosition( mousePos.x, mousePos.y, 1 )

end
