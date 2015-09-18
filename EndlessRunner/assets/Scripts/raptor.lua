

function raptor.Update(dt)
	go = this.GameObject;
	transform = go:GetTransform();
	transform:RotateX(dt);
end
