Vector2 = {}

Vector2_mt = {
__index = Vector2,
__add = function( a, b ) return Vector2:new( a.x + b.x, a.y + b.y ) end,
__sub = function( a, b ) return Vector2:new( a.x - b.x, a.y - b.y ) end,
__tostring = function( a ) return "( " .. a.x .. ", " .. a.y .." )"  end }

function Vector2:new(x,y)
   return setmetatable( {x=x, y=y}, Vector2_mt )
end

function Vector2:mag()
   return math.sqrt(self:dot(self))
end

function Vector2:dot(v)
   return self.x * v.x + self.y * v.y
end

function Vector2:scale(s)
   return Vector2:new( self.x * s, self.y * s )
end
