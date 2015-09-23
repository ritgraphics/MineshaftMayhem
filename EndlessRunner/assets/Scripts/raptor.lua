function raptor.OnInit()
	--print("oninit " .. this.GameObject:GetName() .. " ID: " .. this.GameObject:GetID());
end

function raptor.OnEnable()
	--print("onenabled " .. this.GameObject:GetName());
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

	if Input.KeyPress(IKEY.LEFT) then
		local p = Prefab.Load("cube.pfb");
		local g = p:CreateObject();
		
		p:MarkStore();
		p:MarkDelete();
		g:Delete();

		FileManager.PrintOpen();
	end

	

	transform:TranslateY(this.yVelocity * dt)
	
end

function raptor.OnDisable()
	--print("ondisabled " .. this.GameObject:GetName());
end

function raptor.OnDestroy()
	--print("ondestroy " .. this.GameObject:GetName() .. " ID: " .. this.GameObject:GetID());
end
