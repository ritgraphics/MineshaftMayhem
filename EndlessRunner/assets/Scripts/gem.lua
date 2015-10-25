function gem.OnInit()
	
end

function gem.OnEnable()
    this.player = Scene.FindObjectWithName("minecart1");
end

function gem.Update(dt)

	
	local go = this.GameObject;
	
	local transform = go:GetTransform();

    local distance = transform.WorldPosition - this.player:GetTransform().WorldPosition;
    local distanceSqrd = distance:Z() * distance:Z() + distance:X() * distance:X();

    if distanceSqrd <= 16.0 then
        go:Delete();
        go = nil;
    end

end

function gem.OnDisable()
	
end

function gem.OnDestroy()
	
end
