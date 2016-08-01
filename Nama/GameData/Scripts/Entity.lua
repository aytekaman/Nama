require "GameData\\Scripts\\Vector2"

Entity = {}
Entity_mt = { __index = Entity }

function Entity:new( ref, pos, rot )
	ref:GetTransform():setScale(50,50,1)
   e = setmetatable(
   { r = ref,
	t = ref:GetTransform(),
	m = ref:GetMesh(),
	pos = pos or Vector2:new( 400, 300 ),
	rot = rot or 0,
	speed = 150 },
	Entity_mt )
	--e:move( 0 )
	return e
end

function Entity:move( deltaTime )
	self.pos = self.pos + Vector2:new( self.speed  * math.cos(math.rad (self.rot)) * deltaTime, self.speed * math.sin(math.rad (self.rot))* deltaTime)
	self.t:setPosition( self.pos.x, self.pos.y, 10 )
end

Bullet = {}

function Bullet:new( ref )
	b = Entity:new( ref )
	b.update = function () Game:GetInstance():PrintMessage( "yaaaaay" ) end
	return b
end

function Entity:lookAt( target )
	dif = ( target - self.pos )
	rot = math.deg( math.atan2( dif.y, dif.x ) )

	if rot < 0 then
		rot = 360 + rot
	end

	--Game:GetInstance():PrintMessage( self.rot )

	if rot - self.rot > 180 then
		rot = rot - 360
	elseif self.rot - rot > 180 then
		rot = rot + 360
	end

	self.rot = rot * 0.05 + self.rot * 0.95

	self.rot = self.rot % 360

--~ 	if self.rot  > 360 then
--~ 		self.rot = self.rot - 360
--~ 	elseif self.rot < 0 then
--~ 		self.rot = self.rot + 360
--~ 	end

	self.t:setRotation( 0, 0, self.rot )
end
