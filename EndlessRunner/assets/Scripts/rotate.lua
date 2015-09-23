
function rotate.OnInit()
	
end

function rotate.OnEnable()
	
end

function rotate.Update(dt)

	local go = this.GameObject;
	
	local transform = go:GetTransform();
	transform:RotateY(dt);
	
end

function rotate.OnDisable()
	
end

function rotate.OnDestroy()
	
end
