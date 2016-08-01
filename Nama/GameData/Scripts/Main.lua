require "GameData\\Scripts\\Vector2"

texturesFolder = "GameData\\Textures\\"

function Key( keyString )
	return string.byte( keyString )
end

function setPos( e )
	e.t:setPosition( e.pos.x, e.pos.y, 0 )
end

function move( e )
	e.pos = e.pos + e.vel:scale( Game:GetInstance():GetDeltaTime() )
	if e.rot then
		e.rot = e.rot + Game:GetInstance():GetDeltaTime() * 1000
		e.t:setRotation( 0, 0, e.rot )
	end

	setPos( e )
end

-- Creating Border

e_border = GameObject:Create()
e_border:GetTransform():setPosition( 400, 300, -1 )
e_border:GetTransform():setScale( 400, 553, 0 )
e_border:GetMesh():SetMaterialTexture( texturesFolder .. "notepad.tga" )
e_border:GetMesh():SetMaterialColor( 1, 1, 1, 1 )

-- Creating Player
e_player = GameObject:Create()
player = {
r = e_player,
t = e_player:GetTransform(),
m = e_player:GetMesh(),
pos = Vector2:new( 420, 300 ),
vel = Vector2:new( 100, 0 ),
fireStep = 0.125,
lastFired = 1 }

playerFSM =
{
	ready = function()
		if Input:GetKey( Key("L") ) or Input:GetMouseButton( 0 ) then
			player.lastFired = 0
			spawnBullet( player.pos )
			return playerFSM.reloading
		else
			return playerFSM.ready
		end
	end,

	reloading = function()
		player.lastFired = player.lastFired + Game:GetInstance():GetDeltaTime()
		if player.lastFired > player.fireStep then
			return playerFSM.ready
		else
			return playerFSM.reloading
		end
	end
}

player.action = playerFSM.ready

player.t:setScale( 40, 10, 1 )
player.m:SetMaterialColor( 0, 1, 0, 1 )
e_player:AddCollider( 40, 10, 3 )
setPos( player )


-- Creating Bullets
bullets = {}

function spawnBullet( pos )
	e_bullet = GameObject:Create()
	--Game:PrintMessage( e_bullet:GetID() )
	bullet = { r = e_bullet, t = e_bullet:GetTransform(), m = e_bullet:GetMesh(), pos = Vector2:new( 0, 0 ), vel = Vector2:new( 0, 500 ) }
	bullet.pos.x = pos.x
	bullet.pos.y = pos.y
	bullet.t:setScale( 5, 5, 1 )
	e_bullet:AddCollider( 5, 5, 1 )
	setPos( bullet )
	bullets[ "" .. e_bullet:GetID() ] = bullet
end

-- Creating Bonus
bonuses = {}

function spawnBonus( pos )
	e_bonus = GameObject:Create()
	bonus = { r = e_bonus, t = e_bonus:GetTransform(), m = e_bonus:GetMesh(), pos = Vector2:new( 0, 0 ), vel = Vector2:new( 0, -50 ), rot = 0, rotVel = 1000,
			  doBonus = function() player.pos.y = 200 + math.random(100) end }
	bonus.pos.x = pos.x
	bonus.pos.y = pos.y
	bonus.t:setScale( 5, 5, 1 )
	e_bonus:AddCollider( 5, 5, 4 )
	setPos( bonus )
	bonuses[ "" .. e_bonus:GetID() ] = bonus
end


-- Creating Bricks, shdould hold these data in a table called brickInfo
bricks = {}

left = 250
top = 575
horCount = 10
verCount = 5
horStep = ( ( 400 - left ) * 2 ) / ( horCount - 1 )
verStep = 20

for i = 1, horCount do
	for j = 1, verCount do
		e_brick = GameObject:Create()
		brick = { r = e_brick, t = e_brick:GetTransform(), m = e_brick:GetMesh(),
		pos = Vector2:new( left + horStep * ( i - 1 ), top - verStep * ( j - 1 ) ),
		vel = Vector2:new( 0, -10 ) }
		brick.t:setScale( 25, 10, 1 )
		--brick.m:SetMaterialTexture( texturesFolder .. "brick.tga" )
		setPos( brick )
		e_brick:AddCollider( 25, 10, 2 )
		bricks[ "" .. e_brick:GetID() ] = brick
	end
end

--Physics:EnableCollisionLayers( "PlayerBall", 1, 2 )
Physics:EnableCollisionLayers( "OnBulletBrick", 1, 2 )
Physics:EnableCollisionLayers( "OnPlayerBonus", 3, 4 )



function OnUpdate()

	player.lastFired = player.lastFired + Game:GetInstance():GetDeltaTime()

	if Input:GetKey( Key("A") ) then
		player.vel.x = -100
	elseif Input:GetKey( Key("D") ) then
		player.vel.x = 100
	else
		player.vel.x = 0
	end

	-- if Input:GetKey( Key("L") ) and player.lastFired > player.fireStep then
		-- player.lastFired = 0
		-- spawnBullet( player.pos )
	-- end

	player.action = player.action()

	move( player )

	for k, v in pairs( bonuses ) do
		move( v )
	end

	for k, v in pairs( bricks ) do
		move( v )
	end

	for k, v in pairs( bullets ) do
		move( v )
		if v.pos.y > 575 then
			GameObject:Destroy( v.r )
			bullets[k] = nil
		end
	end
end

function OnPlayerBonus( ID, otherID )
	bonuses[ "" .. otherID ].doBonus()
	GameObject:Destroy( bonuses[ "" .. otherID ].r )
	bonuses[ "" .. otherID ] = nil
end

function OnBulletBrick( ID, otherID )
	GameObject:Destroy( bullets[ "" .. ID ].r )
	bullets[ "" .. ID ] = nil

	if math.random( 10 ) > 8 then
		spawnBonus( bricks[ "" .. otherID ].pos )
	end

	GameObject:Destroy( bricks[ "" .. otherID ].r )
	bricks[ "" .. otherID ] = nil

	if next( bricks ) == nil then
		Game:GetInstance():LoadScene( "Main.lua" )
	end
end

