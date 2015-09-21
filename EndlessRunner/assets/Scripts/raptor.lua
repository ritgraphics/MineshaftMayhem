function raptor.OnInit()
	print("oninit " .. this.GameObject:GetName());
	
	print("GameObject: " .. this.GameObject:GetName() .. " ID: " .. this.GameObject:GetID())
	
end

function raptor.OnEnable()
	print("onenabled " .. this.GameObject:GetName());
	this.yVelocity = 0;

	this.spawnOffsetX = 0;
end

function raptor.Update(dt)



	local go = this.GameObject;
	
	local transform = go:GetTransform();
	transform:RotateY(dt);
	
	if transform.Position:Y() > 0.0 then
		this.yVelocity = this.yVelocity - (dt * 9.8);
	else
		this.yVelocity = 0;
	end
	

	if Input.SingleKeyPress(IKEY.SPACE) then
		this.yVelocity = this.yVelocity + 10.0;
	end

	if Input.SingleKeyPress(IKEY.LEFT) then
		local p = SpawnPrefab("cube.pfb")
		local t = p:GetTransform();
		local z = t.Position:Z()
		local y = t.Position:Y()
		t.Position = Vector3(this.spawnOffsetX, y, z)
		this.spawnOffsetX = this.spawnOffsetX + 50;
		local size = this.GameObject:GetTransform().Scale:X() * .5;
		t.Scale = Vector3(size, size, size);
	end

	transform:TranslateY(this.yVelocity * dt)
	
end

function raptor.OnDisable()
	print("ondisabled " .. this.GameObject:GetName());
end

function raptor.OnDestroy()
	print("ondestroy " .. this.GameObject:GetName());

	print("GameObject: " .. this.GameObject:GetName() .. " ID: " .. this.GameObject:GetID())
end
