function raptor.OnInit()
	print("oninit " .. this.GameObject:GetID());
end

function raptor.OnEnable()
	print("onenabled " .. this.GameObject:GetID());
end

function raptor.Update(dt)
	go = this.GameObject;
	transform = go:GetTransform();
	transform:RotateX(dt);
	transform:RotateZ(dt*2);
end

function raptor.OnDisable()
	print("ondisabled " .. this.GameObject:GetID());
end

function raptor.OnDestroy()
	print("ondestroy " .. this.GameObject:GetID());
end
